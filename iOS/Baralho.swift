// Ponte entre o núcleo C++ (Core/CartasCore.hpp) e a interface SwiftUI.
// Toda a lógica de sorteio e os nomes das cartas vêm do C++.

import CartasCore
import Foundation
import Observation

extension std.string {
    var texto: String { String(cString: __c_strUnsafe()) }
}

enum Naipe: Int32, CaseIterable, Identifiable {
    case espadas = 1, copas, paus, ouros

    var id: Int32 { rawValue }

    init(_ naipe: cartas.Naipe) {
        self = Naipe(rawValue: naipe.rawValue) ?? .espadas
    }

    var cpp: cartas.Naipe { cartas.Naipe(rawValue: rawValue)! }
    var nome: String { cartas.nomeDoNaipe(cpp).texto }
    var simbolo: String { cartas.simboloDoNaipe(cpp).texto }
    var vermelho: Bool { cartas.ehVermelho(cpp) }
}

struct Carta: Equatable {
    let valor: Int32
    let naipe: Naipe

    init(_ carta: cartas.Carta) {
        valor = carta.valor
        naipe = Naipe(carta.naipe)
    }

    private var cpp: cartas.Carta { cartas.Carta(valor: valor, naipe: naipe.cpp) }
    var descricao: String { cartas.descricao(cpp).texto }
    var simboloValor: String { cartas.simboloDoValor(valor).texto }
    var ehFigura: Bool { valor >= 11 }
}

enum Resultado: Equatable {
    case carta(Carta)
    case numero(Int32)

    var descricao: String {
        switch self {
        case .carta(let carta): carta.descricao
        case .numero(let numero): "Número \(numero)"
        }
    }
}

struct ItemHistorico: Identifiable {
    let id = UUID()
    let resultado: Resultado
}

enum Modo: String, CaseIterable, Identifiable {
    case carta = "Qualquer carta"
    case naipe = "Por naipe"
    case numero = "Número"

    var id: String { rawValue }
}

@MainActor
@Observable
final class Sorteio {
    var modo: Modo = .carta
    var naipeEscolhido: Naipe = .espadas
    private(set) var atual: Resultado?
    private(set) var historico: [ItemHistorico] = []

    @ObservationIgnored private var gerador = cartas.Gerador()

    private let limiteHistorico = 30

    @discardableResult
    func sortear() -> Resultado {
        let resultado: Resultado
        switch modo {
        case .carta:
            resultado = .carta(Carta(gerador.gerarCarta()))
        case .naipe:
            resultado = .carta(Carta(gerador.gerarCartaDoNaipe(naipeEscolhido.cpp)))
        case .numero:
            resultado = .numero(gerador.gerarNumero())
        }
        atual = resultado
        historico.insert(ItemHistorico(resultado: resultado), at: 0)
        if historico.count > limiteHistorico {
            historico.removeLast(historico.count - limiteHistorico)
        }
        return resultado
    }

    func limparHistorico() {
        historico.removeAll()
    }
}
