// Expõe o núcleo C++ (Core/CartasCore.hpp) ao JavaScript via WebAssembly.
// Toda a lógica de sorteio e os nomes das cartas vêm do C++.

#include <emscripten/bind.h>

#include "CartasCore.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(cartas_core) {
    enum_<cartas::Naipe>("Naipe")
        .value("Espadas", cartas::Naipe::Espadas)
        .value("Copas", cartas::Naipe::Copas)
        .value("Paus", cartas::Naipe::Paus)
        .value("Ouros", cartas::Naipe::Ouros);

    value_object<cartas::Carta>("Carta")
        .field("valor", &cartas::Carta::valor)
        .field("naipe", &cartas::Carta::naipe);

    class_<cartas::Gerador>("Gerador")
        .constructor<>()
        .function("gerarCarta", &cartas::Gerador::gerarCarta)
        .function("gerarCartaDoNaipe", &cartas::Gerador::gerarCartaDoNaipe)
        .function("gerarNumero", &cartas::Gerador::gerarNumero);

    function("nomeDoNaipe", &cartas::nomeDoNaipe);
    function("nomeDoValor", &cartas::nomeDoValor);
    function("descricao", &cartas::descricao);
    function("simboloDoValor", &cartas::simboloDoValor);
    function("simboloDoNaipe", &cartas::simboloDoNaipe);
    function("ehVermelho", &cartas::ehVermelho);
}
