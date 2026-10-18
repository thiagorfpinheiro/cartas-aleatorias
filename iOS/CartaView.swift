import SwiftUI

private let vermelhoCarta = Color(red: 0.78, green: 0.09, blue: 0.16)
private let pretoCarta = Color(red: 0.10, green: 0.10, blue: 0.12)

/// Carta grande no centro da tela: verso, face de carta ou número.
struct CartaView: View {
    let resultado: Resultado?

    var body: some View {
        GeometryReader { geo in
            let largura = geo.size.width
            ZStack {
                switch resultado {
                case nil:
                    VersoCarta()
                case .carta(let carta):
                    FaceCarta(carta: carta, largura: largura)
                case .numero(let numero):
                    FaceNumero(numero: numero, largura: largura)
                }
            }
            .frame(width: largura, height: geo.size.height)
            .clipShape(RoundedRectangle(cornerRadius: largura * 0.07, style: .continuous))
            .shadow(color: .black.opacity(0.35), radius: 18, y: 10)
        }
        .aspectRatio(2.5 / 3.5, contentMode: .fit)
        .accessibilityElement(children: .ignore)
        .accessibilityLabel(resultado?.descricao ?? "Carta virada. Toque para gerar.")
    }
}

private struct FaceCarta: View {
    let carta: Carta
    let largura: CGFloat

    private var cor: Color { carta.naipe.vermelho ? vermelhoCarta : pretoCarta }

    var body: some View {
        ZStack {
            Color.white

            if carta.ehFigura {
                RoundedRectangle(cornerRadius: largura * 0.04, style: .continuous)
                    .strokeBorder(cor.opacity(0.25), lineWidth: 2)
                    .padding(largura * 0.17)
                VStack(spacing: 0) {
                    Text(carta.simboloValor)
                        .font(.system(size: largura * 0.42, weight: .bold, design: .serif))
                    Text(carta.naipe.simbolo)
                        .font(.system(size: largura * 0.22))
                }
            } else {
                Text(carta.naipe.simbolo)
                    .font(.system(size: largura * 0.48))
            }

            VStack {
                HStack {
                    Canto(carta: carta, largura: largura)
                    Spacer()
                }
                Spacer()
                HStack {
                    Spacer()
                    Canto(carta: carta, largura: largura)
                        .rotationEffect(.degrees(180))
                }
            }
            .padding(largura * 0.06)
        }
        .foregroundStyle(cor)
    }
}

private struct Canto: View {
    let carta: Carta
    let largura: CGFloat

    var body: some View {
        VStack(spacing: -largura * 0.01) {
            Text(carta.simboloValor)
                .font(.system(size: largura * 0.13, weight: .bold, design: .serif))
            Text(carta.naipe.simbolo)
                .font(.system(size: largura * 0.09))
        }
        .fixedSize()
    }
}

private struct FaceNumero: View {
    let numero: Int32
    let largura: CGFloat

    var body: some View {
        ZStack {
            Color.white
            VStack(spacing: largura * 0.02) {
                Text("\(numero)")
                    .font(.system(size: largura * 0.5, weight: .bold, design: .rounded))
                    .monospacedDigit()
                    .foregroundStyle(pretoCarta)
                Text("de 52")
                    .font(.system(size: largura * 0.07, weight: .medium, design: .rounded))
                    .foregroundStyle(pretoCarta.opacity(0.5))
            }
        }
    }
}

private struct VersoCarta: View {
    var body: some View {
        ZStack {
            LinearGradient(
                colors: [Color(red: 0.55, green: 0.08, blue: 0.14), Color(red: 0.35, green: 0.04, blue: 0.09)],
                startPoint: .topLeading, endPoint: .bottomTrailing
            )
            Canvas { contexto, tamanho in
                let passo: CGFloat = 16
                var caminho = Path()
                var x: CGFloat = -tamanho.height
                while x < tamanho.width {
                    caminho.move(to: CGPoint(x: x, y: 0))
                    caminho.addLine(to: CGPoint(x: x + tamanho.height, y: tamanho.height))
                    caminho.move(to: CGPoint(x: x + tamanho.height, y: 0))
                    caminho.addLine(to: CGPoint(x: x, y: tamanho.height))
                    x += passo
                }
                contexto.stroke(caminho, with: .color(.white.opacity(0.12)), lineWidth: 1)
            }
            RoundedRectangle(cornerRadius: 12, style: .continuous)
                .strokeBorder(.white.opacity(0.7), lineWidth: 3)
                .padding(12)
            VStack(spacing: 6) {
                Text("♠ ♥")
                Text("♣ ♦")
            }
            .font(.system(size: 34))
            .foregroundStyle(.white.opacity(0.85))
        }
    }
}

/// Carta pequena usada no histórico.
struct MiniCartaView: View {
    let resultado: Resultado

    var body: some View {
        Group {
            switch resultado {
            case .carta(let carta):
                VStack(spacing: -2) {
                    Text(carta.simboloValor).font(.system(size: 17, weight: .bold, design: .serif))
                    Text(carta.naipe.simbolo).font(.system(size: 15))
                }
                .foregroundStyle(carta.naipe.vermelho ? vermelhoCarta : pretoCarta)
            case .numero(let numero):
                Text("\(numero)")
                    .font(.system(size: 18, weight: .bold, design: .rounded))
                    .foregroundStyle(pretoCarta)
            }
        }
        .frame(width: 40, height: 56)
        .background(.white, in: RoundedRectangle(cornerRadius: 6, style: .continuous))
        .accessibilityLabel(resultado.descricao)
    }
}
