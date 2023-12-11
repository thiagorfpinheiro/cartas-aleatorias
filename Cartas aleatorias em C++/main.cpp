#include <iostream>
#include <locale>
#include <stdlib.h>  //Para pausar tela, limpar tela, etc
#include <cstdlib>  //Para utilizar fun��o rand()
#include <ctime>   //Para utilizar fun��o time()
#include <string>

using namespace std;

void mostrar_menu();
void receber_opcao();
void gerar_numero();
void gerar_carta();
void gerar_naipe();
void gerar_espadas();
void gerar_copas();
void gerar_paus();
void gerar_ouros();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    mostrar_menu();
    return 0;
}

void mostrar_menu()
{
    cout << "----------------------------------------------------------" << endl;
    cout << "|  PROGRAMA AUXILIADOR DE TRUQUES COM CARTAS DE BARALHO  |" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "|                ESCOLHA UMA OP��O ABAIXO                |" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "[1] Gerar Carta Aleat�ria (Qualquer Naipe)" << endl;
    cout << "[2] Gerar Carta Aleat�ria de Naipe Espec�fico" << endl;
    cout << "[3] Gerar N�mero Aleat�rio (Entre 1 e 52)" << endl;
    cout << "[4] Sair do Programa" << endl;
    receber_opcao();
}

void receber_opcao()
{
    int opcao;
    cout << "\nOp��o escolhida: ";
    cin >> opcao;
    switch(opcao)
    {
        case 1:
            gerar_carta();
            break;
        case 2:
            gerar_naipe();
            break;
        case 3:
            gerar_numero();
            break;
        case 4:
            exit (EXIT_SUCCESS);
            break;
        default:
            cout << "\nValor inv�lido!\n" << endl;
            system("pause");
            system("cls");
            mostrar_menu();
    }
}

void gerar_carta()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

    char resposta = 's';

    while (resposta == 's' || resposta == 'S'){
        int valor = (1+rand()%13);
        int naipe = (1+rand()%4);
        string nome_naipe;

        if (naipe == 1){
            nome_naipe = "Espadas";
        } else if (naipe == 2){
            nome_naipe = "Copas";
        } else if (naipe == 3){
            nome_naipe = "Paus";
        } else {
            nome_naipe = "Ouros";
        }

        if (valor == 1){
            cout << "\nCarta Gerada: �s de " << nome_naipe << endl;
        } else if (valor == 11){
            cout << "\nCarta Gerada: Valete de " << nome_naipe << endl;
        } else if (valor == 12){
            cout << "\nCarta Gerada: Dama de " << nome_naipe << endl;
        } else if (valor == 13){
            cout << "\nCarta Gerada: Rei de " << nome_naipe << endl;
        } else {
            cout << "\nCarta Gerada: " << valor << " de " << nome_naipe <<endl;
        }
        cout << "\nDeseja gerar outra carta? [s/n] ";\
        cin >> resposta;
    }
    system("cls");
    mostrar_menu();
}

void gerar_naipe()
{
    int opcao;

    cout << "\nDe qual naipe voc� deseja gerar uma carta?";
    cout << "\n[1] Espadas";
    cout << "\n[2] Copas";
    cout << "\n[3] Paus";
    cout << "\n[4] Ouros" << endl;
    cout << "\nOp��o escolhida: ";
    cin >> opcao;

    char resposta = 's';

    switch(opcao)
    {
        case 1:
            while (resposta == 's' || resposta == 'S'){
            gerar_espadas();
            cout << "\nDeseja gerar outra carta? [s/n] ";
            cin >> resposta;
            cout << "\n";
            }
            system("cls");
            mostrar_menu();
            break;
        case 2:
            while (resposta == 's' || resposta == 'S'){
            gerar_copas();
            cout << "\nDeseja gerar outra carta? [s/n] ";
            cin >> resposta;
            cout << "\n";
            }
            system("cls");
            mostrar_menu();
            break;
        case 3:
            while (resposta == 's' || resposta == 'S'){
            gerar_paus();
            cout << "\nDeseja gerar outra carta? [s/n] ";
            cin >> resposta;
            cout << "\n";
            }
            system("cls");
            mostrar_menu();
            break;
        case 4:
            while (resposta == 's' || resposta == 'S'){
            gerar_ouros();
            cout << "\nDeseja gerar outra carta? [s/n] ";
            cin >> resposta;
            cout << "\n";
            }
            system("cls");
            mostrar_menu();
            break;
        default:
            cout << "\nValor Inv�lido!" << endl;
            gerar_naipe();
    }
}

void gerar_espadas()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

        int valor = (1+rand()%13);

        if (valor == 1){
            cout << "\nCarta Gerada: �s de Espadas" << endl;
        } else if (valor == 11){
            cout << "\nCarta Gerada: Valete de Espadas" << endl;
        } else if (valor == 12){
            cout << "\nCarta Gerada: Dama de Espadas" << endl;
        } else if (valor == 13){
            cout << "\nCarta Gerada: Rei de Espadas" << endl;
        } else {
            cout << "\nCarta Gerada: " << valor << " de Espadas" <<endl;
        }
}

void gerar_copas()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

        int valor = (1+rand()%13);

        if (valor == 1){
            cout << "\nCarta Gerada: �s de Copas" << endl;
        } else if (valor == 11){
            cout << "\nCarta Gerada: Valete de Copas" << endl;
        } else if (valor == 12){
            cout << "\nCarta Gerada: Dama de Copas" << endl;
        } else if (valor == 13){
            cout << "\nCarta Gerada: Rei de Copas" << endl;
        } else {
            cout << "\nCarta Gerada: " << valor << " de Copas" <<endl;
        }
}

void gerar_paus()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

        int valor = (1+rand()%13);

        if (valor == 1){
            cout << "\nCarta Gerada: �s de Paus" << endl;
        } else if (valor == 11){
            cout << "\nCarta Gerada: Valete de Paus" << endl;
        } else if (valor == 12){
            cout << "\nCarta Gerada: Dama de Paus" << endl;
        } else if (valor == 13){
            cout << "\nCarta Gerada: Rei de Paus" << endl;
        } else {
            cout << "\nCarta Gerada: " << valor << " de Paus" <<endl;
        }
}

void gerar_ouros()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

        int valor = (1+rand()%13);

        if (valor == 1){
            cout << "\nCarta Gerada: �s de Ouros" << endl;
        } else if (valor == 11){
            cout << "\nCarta Gerada: Valete de Ouros" << endl;
        } else if (valor == 12){
            cout << "\nCarta Gerada: Dama de Ouros" << endl;
        } else if (valor == 13){
            cout << "\nCarta Gerada: Rei de Ouros" << endl;
        } else {
            cout << "\nCarta Gerada: " << valor << " de Ouros" <<endl;
        }
}

void gerar_numero()
{
    //Forma encontrada para gerar uma semente aleat�ria para a fun��o rand()
    unsigned seed = time(0);
    srand(seed);

    char resposta = 's';

    while (resposta == 's' || resposta == 'S'){
        cout << "\nN�mero aleat�rio entre 1 e 50: " << 1+rand()%52 << endl;
        cout << "\nDeseja gerar outro n�mero? [s/n] ";\
        cin >> resposta;
    }

    system("cls");
    mostrar_menu();
}

