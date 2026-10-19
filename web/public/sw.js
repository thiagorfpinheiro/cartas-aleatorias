// Guarda os arquivos do app para ele funcionar sem internet.

const VERSAO = 'cartas-v1';
const ARQUIVOS = [
  './',
  './index.html',
  './style.css',
  './app.js',
  './cartas.js',
  './cartas.wasm',
  './manifest.webmanifest',
  './icones/icone-192.png',
  './icones/icone-512.png',
  './icones/apple-touch-icon.png',
];

self.addEventListener('install', (evento) => {
  evento.waitUntil(caches.open(VERSAO).then((cache) => cache.addAll(ARQUIVOS)));
  self.skipWaiting();
});

self.addEventListener('activate', (evento) => {
  evento.waitUntil(
    caches.keys().then((nomes) =>
      Promise.all(nomes.filter((nome) => nome !== VERSAO).map((nome) => caches.delete(nome)))
    )
  );
  self.clients.claim();
});

// Com internet, busca a versão mais nova e atualiza a cópia guardada.
// Sem internet, usa a cópia guardada.
self.addEventListener('fetch', (evento) => {
  if (evento.request.method !== 'GET') return;
  evento.respondWith(
    fetch(evento.request)
      .then((resposta) => {
        if (resposta.ok) {
          const copia = resposta.clone();
          caches.open(VERSAO).then((cache) => cache.put(evento.request, copia));
        }
        return resposta;
      })
      .catch(() => caches.match(evento.request, { ignoreSearch: true }))
  );
});
