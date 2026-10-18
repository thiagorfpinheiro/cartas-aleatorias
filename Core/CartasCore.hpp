// Núcleo do "Programa Auxiliador de Truques com Cartas de Baralho".
// Lógica extraída de "Cartas aleatorias em C++/main.cpp", sem entrada/saída
// de console, para ser usada pelo app de iOS (Swift chama este C++ direto).

#pragma once

#include <random>
#include <string>

namespace cartas {

// Mesma numeração do programa original: 1 = Espadas, 2 = Copas, 3 = Paus, 4 = Ouros
enum class Naipe : int {
    Espadas = 1,
    Copas = 2,
    Paus = 3,
    Ouros = 4
};

// valor: 1 = Ás, 2 a 10 = número, 11 = Valete, 12 = Dama, 13 = Rei
struct Carta {
    int valor;
    Naipe naipe;
};

class Gerador {
public:
    Gerador();

    // Opção [1] do menu original: carta aleatória de qualquer naipe
    Carta gerarCarta();

    // Opção [2] do menu original: carta aleatória de um naipe específico
    Carta gerarCartaDoNaipe(Naipe naipe);

    // Opção [3] do menu original: número aleatório entre 1 e 52
    int gerarNumero();

private:
    int sortear(int minimo, int maximo);

    std::mt19937 motor;
};

// "Espadas", "Copas", "Paus" ou "Ouros"
std::string nomeDoNaipe(Naipe naipe);

// "Ás", "2" ... "10", "Valete", "Dama" ou "Rei"
std::string nomeDoValor(int valor);

// Texto completo, como o programa original exibia: "Ás de Espadas", "7 de Copas"...
std::string descricao(Carta carta);

// Símbolo curto para o canto da carta: "A", "2" ... "10", "J", "Q" ou "K"
std::string simboloDoValor(int valor);

// "♠", "♥", "♣" ou "♦"
std::string simboloDoNaipe(Naipe naipe);

// Copas e Ouros são vermelhos
bool ehVermelho(Naipe naipe);

} // namespace cartas
