#include <iostream>
#include <stdlib.h>
#include "tabuleiro.h"
#include "funcoes.h"
#include <Windows.h>

using namespace std;

int main() {
    wstring xadrez = L"Xadrez";
    SetConsoleTitle(xadrez.c_str());
    int opcao = 0;
    while (1) {
        system("cls");
        cout << "================================" << endl;
        cout << "1) Jogar partida" << endl;
        cout << "2) Abrir uma partida" << endl;
        cout << "3) Sair" << endl;
        cout << "================================" << endl;
        cin >> opcao;
        if (opcao == 1) {
            unique_ptr<Tabuleiro> tabuleiro(new Tabuleiro());
            int numeroLances = 0;
            int resultado = jogarPartida(*tabuleiro, numeroLances);
            if (resultado == 2) {
                cout << "Empate." << endl;
            }
            else {
                if (resultado == 1) {
                    cout << "Brancas ";
                }
                else {
                    cout << "Pretas ";
                }
                cout << "venceram!" << endl;
            }
            salvarPartida(*tabuleiro, numeroLances);
        }
        if (opcao == 2) {
            abrirPartida();
        }
        if (opcao == 3) {
            break;
        }
    }
    return 0;
}