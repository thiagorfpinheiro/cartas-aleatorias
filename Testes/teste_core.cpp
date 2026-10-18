// Testes do núcleo C++. Compilar e rodar no Mac:
//   clang++ -std=c++20 -ICore Core/CartasCore.cpp Testes/teste_core.cpp -o /tmp/teste_core && /tmp/teste_core

#include "CartasCore.hpp"

#include <cstdio>
#include <set>

static int falhas = 0;

static void verificar(bool condicao, const char* mensagem)
{
    if (!condicao) {
        std::printf("FALHOU: %s\n", mensagem);
        falhas++;
    }
}

int main()
{
    using namespace cartas;

    verificar(descricao(Carta{1, Naipe::Espadas}) == "Ás de Espadas", "Ás de Espadas");
    verificar(descricao(Carta{11, Naipe::Copas}) == "Valete de Copas", "Valete de Copas");
    verificar(descricao(Carta{12, Naipe::Paus}) == "Dama de Paus", "Dama de Paus");
    verificar(descricao(Carta{13, Naipe::Ouros}) == "Rei de Ouros", "Rei de Ouros");
    verificar(descricao(Carta{7, Naipe::Copas}) == "7 de Copas", "7 de Copas");
    verificar(simboloDoValor(10) == "10" && simboloDoValor(12) == "Q", "símbolos de valor");
    verificar(ehVermelho(Naipe::Copas) && ehVermelho(Naipe::Ouros), "naipes vermelhos");
    verificar(!ehVermelho(Naipe::Espadas) && !ehVermelho(Naipe::Paus), "naipes pretos");

    Gerador gerador;
    std::set<int> valores, naipes, numeros;
    for (int i = 0; i < 20000; i++) {
        Carta carta = gerador.gerarCarta();
        verificar(carta.valor >= 1 && carta.valor <= 13, "valor entre 1 e 13");
        valores.insert(carta.valor);
        naipes.insert(static_cast<int>(carta.naipe));

        Carta copas = gerador.gerarCartaDoNaipe(Naipe::Copas);
        verificar(copas.naipe == Naipe::Copas, "naipe específico respeitado");

        int numero = gerador.gerarNumero();
        verificar(numero >= 1 && numero <= 52, "número entre 1 e 52");
        numeros.insert(numero);
    }
    verificar(valores.size() == 13, "todos os 13 valores aparecem");
    verificar(naipes.size() == 4, "todos os 4 naipes aparecem");
    verificar(numeros.size() == 52, "todos os 52 números aparecem");

    if (falhas == 0) {
        std::printf("Todos os testes passaram.\n");
    }
    return falhas == 0 ? 0 : 1;
}
