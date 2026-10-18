#include "CartasCore.hpp"

namespace cartas {

// O original chamava srand(time(0)) a cada carta, o que repetia a mesma carta
// quando duas eram geradas no mesmo segundo. Aqui a semente é criada uma vez só.
Gerador::Gerador() : motor(std::random_device{}()) {}

int Gerador::sortear(int minimo, int maximo)
{
    std::uniform_int_distribution<int> distribuicao(minimo, maximo);
    return distribuicao(motor);
}

Carta Gerador::gerarCarta()
{
    int valor = sortear(1, 13);
    int naipe = sortear(1, 4);
    return Carta{valor, static_cast<Naipe>(naipe)};
}

Carta Gerador::gerarCartaDoNaipe(Naipe naipe)
{
    int valor = sortear(1, 13);
    return Carta{valor, naipe};
}

int Gerador::gerarNumero()
{
    return sortear(1, 52);
}

std::string nomeDoNaipe(Naipe naipe)
{
    switch (naipe) {
        case Naipe::Espadas: return "Espadas";
        case Naipe::Copas:   return "Copas";
        case Naipe::Paus:    return "Paus";
        case Naipe::Ouros:   return "Ouros";
    }
    return "";
}

std::string nomeDoValor(int valor)
{
    if (valor == 1) {
        return "Ás";
    } else if (valor == 11) {
        return "Valete";
    } else if (valor == 12) {
        return "Dama";
    } else if (valor == 13) {
        return "Rei";
    } else {
        return std::to_string(valor);
    }
}

std::string descricao(Carta carta)
{
    return nomeDoValor(carta.valor) + " de " + nomeDoNaipe(carta.naipe);
}

std::string simboloDoValor(int valor)
{
    if (valor == 1) {
        return "A";
    } else if (valor == 11) {
        return "J";
    } else if (valor == 12) {
        return "Q";
    } else if (valor == 13) {
        return "K";
    } else {
        return std::to_string(valor);
    }
}

std::string simboloDoNaipe(Naipe naipe)
{
    switch (naipe) {
        case Naipe::Espadas: return "♠";
        case Naipe::Copas:   return "♥";
        case Naipe::Paus:    return "♣";
        case Naipe::Ouros:   return "♦";
    }
    return "";
}

bool ehVermelho(Naipe naipe)
{
    return naipe == Naipe::Copas || naipe == Naipe::Ouros;
}

} // namespace cartas
