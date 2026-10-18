import SwiftUI

struct ContentView: View {
    @State private var sorteio = Sorteio()
    @State private var exibido: Resultado?
    @State private var rotacao: Double = 0
    @State private var animando = false
    @State private var toques = 0

    var body: some View {
        ZStack {
            FundoMesa()

            VStack(spacing: 18) {
                cabecalho
                seletorDeModo
                if sorteio.modo == .naipe {
                    seletorDeNaipe
                        .transition(.move(edge: .top).combined(with: .opacity))
                }

                Spacer(minLength: 0)

                CartaView(resultado: exibido)
                    .rotation3DEffect(.degrees(rotacao), axis: (x: 0, y: 1, z: 0), perspective: 0.5)
                    .padding(.horizontal, 40)
                    .onTapGesture(perform: gerar)

                Text(exibido?.descricao ?? "Toque na carta ou no botão")
                    .font(.title2.weight(.semibold))
                    .foregroundStyle(.white)
                    .contentTransition(.opacity)
                    .animation(.easeInOut(duration: 0.2), value: exibido)

                Spacer(minLength: 0)

                historico
                botaoGerar
            }
            .padding(.horizontal, 16)
            .padding(.bottom, 8)
            .animation(.snappy, value: sorteio.modo)
        }
        .sensoryFeedback(.impact(weight: .medium), trigger: toques)
    }

    private var cabecalho: some View {
        Text("Cartas Aleatórias")
            .font(.headline)
            .foregroundStyle(.white.opacity(0.8))
            .padding(.top, 8)
    }

    private var seletorDeModo: some View {
        Picker("Modo", selection: $sorteio.modo) {
            ForEach(Modo.allCases) { modo in
                Text(modo.rawValue).tag(modo)
            }
        }
        .pickerStyle(.segmented)
        .colorScheme(.dark)
    }

    private var seletorDeNaipe: some View {
        HStack(spacing: 12) {
            ForEach(Naipe.allCases) { naipe in
                let selecionado = sorteio.naipeEscolhido == naipe
                Button {
                    sorteio.naipeEscolhido = naipe
                } label: {
                    Text(naipe.simbolo)
                        .font(.system(size: 30))
                        .foregroundStyle(naipe.vermelho ? Color(red: 0.78, green: 0.09, blue: 0.16) : .black)
                        .frame(maxWidth: .infinity, minHeight: 56)
                        .background(
                            .white.opacity(selecionado ? 1 : 0.55),
                            in: RoundedRectangle(cornerRadius: 14, style: .continuous)
                        )
                        .overlay {
                            RoundedRectangle(cornerRadius: 14, style: .continuous)
                                .strokeBorder(.yellow, lineWidth: selecionado ? 3 : 0)
                        }
                        .scaleEffect(selecionado ? 1.05 : 1)
                }
                .buttonStyle(.plain)
                .accessibilityLabel(naipe.nome)
                .accessibilityAddTraits(selecionado ? .isSelected : [])
            }
        }
        .animation(.snappy, value: sorteio.naipeEscolhido)
    }

    @ViewBuilder
    private var historico: some View {
        if !sorteio.historico.isEmpty {
            VStack(alignment: .leading, spacing: 6) {
                HStack {
                    Text("Histórico")
                        .font(.footnote.weight(.semibold))
                    Spacer()
                    Button("Limpar") {
                        withAnimation { sorteio.limparHistorico() }
                    }
                    .font(.footnote)
                }
                .foregroundStyle(.white.opacity(0.8))

                ScrollView(.horizontal, showsIndicators: false) {
                    LazyHStack(spacing: 8) {
                        ForEach(sorteio.historico) { item in
                            MiniCartaView(resultado: item.resultado)
                                .transition(.scale.combined(with: .opacity))
                        }
                    }
                    .animation(.snappy, value: sorteio.historico.map(\.id))
                }
                .frame(height: 56)
            }
        }
    }

    private var botaoGerar: some View {
        Button(action: gerar) {
            Text(sorteio.modo == .numero ? "Gerar número" : "Gerar carta")
                .font(.title3.weight(.bold))
                .frame(maxWidth: .infinity, minHeight: 58)
        }
        .buttonStyle(.borderedProminent)
        .buttonBorderShape(.capsule)
        .tint(.white)
        .foregroundStyle(Color(red: 0.05, green: 0.30, blue: 0.18))
    }

    // Vira a carta até a metade, troca o conteúdo e termina de virar.
    private func gerar() {
        guard !animando else { return }
        animando = true
        toques += 1
        let novo = sorteio.sortear()

        withAnimation(.easeIn(duration: 0.14)) {
            rotacao = 90
        } completion: {
            exibido = novo
            rotacao = -90
            withAnimation(.easeOut(duration: 0.18)) {
                rotacao = 0
            } completion: {
                animando = false
            }
        }
    }
}

private struct FundoMesa: View {
    var body: some View {
        RadialGradient(
            colors: [Color(red: 0.09, green: 0.45, blue: 0.27), Color(red: 0.02, green: 0.20, blue: 0.12)],
            center: .center, startRadius: 40, endRadius: 520
        )
        .ignoresSafeArea()
    }
}

#Preview {
    ContentView()
}
