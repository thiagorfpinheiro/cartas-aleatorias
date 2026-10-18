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
