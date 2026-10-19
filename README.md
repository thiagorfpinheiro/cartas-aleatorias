# cartas-aleatorias
 Gera **cartas de baralho** aleatórias para auxiliar treinamento de truques de mágica com baralho.


## App para iPhone

A lógica do programa original foi extraída para um núcleo C++ sem entrada/saída de console (`Core/CartasCore.hpp` e `Core/CartasCore.cpp`), usado diretamente pelo app de iOS em SwiftUI (pasta `iOS/`).

- Abra `CartasAleatorias.xcodeproj` no Xcode (16 ou mais recente), escolha um simulador de iPhone e clique em Run.
- Para instalar num iPhone de verdade, selecione sua conta em *Signing & Capabilities*.
- Testes do núcleo C++ (rodam no Mac, sem Xcode):

```bash
clang++ -std=c++20 -ICore Core/CartasCore.cpp Testes/teste_core.cpp -o /tmp/teste_core && /tmp/teste_core
```

## App web (qualquer dispositivo)

O mesmo núcleo C++ é compilado para WebAssembly com o Emscripten e roda direto no navegador (pasta `web/`). Funciona offline e pode ser instalado na tela de início ("Adicionar à Tela de Início" no Safari, "Instalar app" no Chrome).

- Compilar localmente (requer `brew install emscripten`): `sh web/build.sh`. O site fica em `web/dist`.
- Testar: `python3 -m http.server 8765 --directory web/dist` e abrir http://localhost:8765
- Publicação: o GitHub Actions (`.github/workflows/pages.yml`) compila e publica no GitHub Pages a cada mudança na `main`.
