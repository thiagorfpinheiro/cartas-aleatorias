// Interface web do Cartas Aleatórias.
// Toda a lógica de sorteio e os nomes das cartas vêm do núcleo C++ (Core/CartasCore),
// compilado para WebAssembly em cartas.js / cartas.wasm.

import criarModulo from './cartas.js';

const LIMITE_HISTORICO = 30;
const TEXTO_BOTAO = { carta: 'Gerar carta', naipe: 'Gerar carta', numero: 'Gerar número' };

const el = {
  modos: document.querySelectorAll('.modos button'),
  naipesGrupo: document.querySelector('.naipes'),
  naipes: document.querySelectorAll('.naipes button'),
  carta: document.querySelector('.carta'),
  descricao: document.querySelector('.descricao'),
  historico: document.querySelector('.historico'),
  lista: document.querySelector('.historico-lista'),
  limpar: document.querySelector('.limpar'),
  gerar: document.querySelector('.gerar'),
};

const M = await criarModulo();
const gerador = new M.Gerador();

const estado = {
  modo: ler('modo', 'carta'),
  naipe: ler('naipe', 'Espadas'),
  animando: false,
};
if (!TEXTO_BOTAO[estado.modo]) estado.modo = 'carta';
if (!M.Naipe[estado.naipe]) estado.naipe = 'Espadas';

function ler(chave, padrao) {
  try { return localStorage.getItem('cartas.' + chave) ?? padrao; } catch { return padrao; }
}

function salvar(chave, valor) {
  try { localStorage.setItem('cartas.' + chave, valor); } catch { /* armazenamento indisponível */ }
}

function sortear() {
  if (estado.modo === 'numero') {
    const numero = gerador.gerarNumero();
    return { tipo: 'numero', numero, descricao: `Número ${numero}` };
  }
  const carta = estado.modo === 'naipe'
    ? gerador.gerarCartaDoNaipe(M.Naipe[estado.naipe])
    : gerador.gerarCarta();
  return {
    tipo: 'carta',
    valor: M.simboloDoValor(carta.valor),
    naipe: M.simboloDoNaipe(carta.naipe),
    vermelha: M.ehVermelho(carta.naipe),
    figura: carta.valor >= 11,
    descricao: M.descricao(carta),
  };
}

function criar(tag, classe, texto) {
  const no = document.createElement(tag);
  if (classe) no.className = classe;
  if (texto !== undefined) no.textContent = texto;
  return no;
}

function desenharFace(r) {
  const face = criar('div', 'carta-conteudo');
  face.setAttribute('aria-hidden', 'true');

  if (r.tipo === 'numero') {
    const centro = criar('div', 'centro');
    centro.append(criar('span', 'numero-valor', r.numero), criar('span', 'numero-legenda', 'de 52'));
    face.append(centro);
    return face;
  }

  if (r.vermelha) face.classList.add('vermelha');
  for (const posicao of ['cima', 'baixo']) {
    const canto = criar('div', `canto ${posicao}`);
    canto.append(criar('span', 'canto-valor', r.valor), criar('span', 'canto-naipe', r.naipe));
    face.append(canto);
  }
  const centro = criar('div', 'centro');
  if (r.figura) {
    face.append(criar('div', 'figura-moldura'));
    centro.append(criar('span', 'figura-valor', r.valor), criar('span', 'figura-naipe', r.naipe));
  } else {
    centro.append(criar('span', 'centro-naipe', r.naipe));
  }
  face.append(centro);
  return face;
}

function adicionarAoHistorico(r) {
  const item = criar('li', 'mini');
  item.setAttribute('aria-label', r.descricao);
  if (r.tipo === 'numero') {
    item.classList.add('numero');
    item.append(criar('span', 'mini-valor', r.numero));
  } else {
    if (r.vermelha) item.classList.add('vermelha');
    item.append(criar('span', 'mini-valor', r.valor), criar('span', 'mini-naipe', r.naipe));
  }
  el.lista.prepend(item);
  while (el.lista.children.length > LIMITE_HISTORICO) el.lista.lastElementChild.remove();
  el.lista.scrollLeft = 0;
  el.historico.hidden = false;
}

function mostrar(r) {
  el.carta.replaceChildren(desenharFace(r));
  el.carta.setAttribute('aria-label', r.descricao);
  el.descricao.textContent = r.descricao;
}

const semAnimacao = matchMedia('(prefers-reduced-motion: reduce)');

function esperar(ms) {
  return new Promise((resolver) => setTimeout(resolver, ms));
}

// Vira a carta até a metade, troca o conteúdo e termina de virar.
async function gerar() {
  if (estado.animando) return;
  estado.animando = true;
  navigator.vibrate?.(12);
  const resultado = sortear();
  adicionarAoHistorico(resultado);

  if (semAnimacao.matches) {
    mostrar(resultado);
  } else {
    el.carta.classList.add('virando');
    await esperar(150);
    mostrar(resultado);
    el.carta.classList.replace('virando', 'voltando');
    el.carta.getBoundingClientRect();
    el.carta.classList.replace('voltando', 'chegando');
    await esperar(190);
    el.carta.classList.remove('chegando');
  }
  estado.animando = false;
}

function atualizarModo() {
  for (const botao of el.modos) {
    botao.setAttribute('aria-checked', String(botao.dataset.modo === estado.modo));
  }
  for (const botao of el.naipes) {
    botao.setAttribute('aria-checked', String(botao.dataset.naipe === estado.naipe));
  }
  el.naipesGrupo.hidden = estado.modo !== 'naipe';
  el.gerar.textContent = TEXTO_BOTAO[estado.modo];
}

for (const botao of el.modos) {
  botao.addEventListener('click', () => {
    estado.modo = botao.dataset.modo;
    salvar('modo', estado.modo);
    atualizarModo();
  });
}

for (const botao of el.naipes) {
  botao.addEventListener('click', () => {
    estado.naipe = botao.dataset.naipe;
    salvar('naipe', estado.naipe);
    atualizarModo();
  });
}

el.carta.addEventListener('click', gerar);
el.gerar.addEventListener('click', gerar);
el.limpar.addEventListener('click', () => {
  el.lista.replaceChildren();
  el.historico.hidden = true;
});

// Espaço gera uma carta quando o foco não está num botão.
document.addEventListener('keydown', (evento) => {
  if (evento.code === 'Space' && !(evento.target instanceof HTMLButtonElement)) {
    evento.preventDefault();
    gerar();
  }
});

atualizarModo();
el.gerar.disabled = false;

if ('serviceWorker' in navigator) {
  navigator.serviceWorker.register('./sw.js').catch(() => {});
}
