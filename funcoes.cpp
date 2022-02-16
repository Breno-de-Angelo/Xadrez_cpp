#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "Tabuleiro.h"

using namespace std;
enum cor{branco, preto};

pair<pair<int, int>, pair<int, int>> converterLance(string pos_inicial, string pos_final) {
    pair<pair<int, int>, pair<int, int>> lance;
    lance.first.first = pos_inicial[0] - 'a'; 
    lance.first.second = 8 - pos_inicial[1] + '0';
    lance.second.first = pos_final[0] - 'a';
    lance.second.second = 8 - pos_final[1] + '0'; 
    return lance;
}

int jogarPartida(Tabuleiro& tabuleiro, int& numeroLances) {
    bool cor_atual = cor{ branco };
    bool lanceInvalido = 0;
    while (1) {
        system("cls");
        cout << endl << endl;
        if (lanceInvalido) cout << "Lance invalido." << endl << endl;
        else cout << endl << endl;
        lanceInvalido = 0;
        tabuleiro.imprimir();
        if (cor_atual) cout << "Pretas";
        else cout << "Brancas";
        cout << " jogam." << endl;
        cout << "Insira \"D B\" para desistir com as brancas, \"D P\" para desistir com as pretas, \"E E\" para concordar em um empate" << endl
            << "\"O O\" para fazer o roque, \"OO O\" para o grande roque, " << "ou insira sua jogada (casa_inicial casa_final): " << endl;
        string pos_inicial, pos_final;
        cin >> pos_inicial >> pos_final;
        if (pos_inicial == "D") {
            if (pos_final == "B") {
                return 0;
            }
            if (pos_final == "P") {
                return 1;
            }
        }
        if (pos_inicial == "E" && pos_final == "E") return 2;
        pair<pair<int, int>, pair<int, int>> lance;
        if (pos_inicial == "O" && pos_final == "O") {
            pair<int, int> pos_inicial_rei = tabuleiro.get_rei(cor_atual);
            if (tabuleiro.roque(cor_atual)) {
                pair<int, int> pos_final_rei = tabuleiro.get_rei(cor_atual);
                lance = make_pair(pos_inicial_rei, pos_final_rei);
                tabuleiro.atualizarLista(lance);
                numeroLances++;
            }
            else {
                lanceInvalido = 1;
                continue;
            }
        }
        else if (pos_inicial == "OO" && pos_final == "O") {
            pair<int, int> pos_inicial_rei = tabuleiro.get_rei(cor_atual);
            if (tabuleiro.roque_grande(cor_atual)) {
                pair<int, int> pos_final_rei = tabuleiro.get_rei(cor_atual);
                lance = make_pair(pos_inicial_rei, pos_final_rei);
                tabuleiro.atualizarLista(lance);
                numeroLances++;
            }
            else {
                lanceInvalido = 1;
                continue;
            }
        }
        else {
            lance = converterLance(pos_inicial, pos_final);
            if (tabuleiro.validarLance(lance, cor_atual)) {
                tabuleiro.atualizarLista(lance);
                numeroLances++;
            }
            else {
                lanceInvalido = 1;
                continue;
            }
        }
        tabuleiro.atualizarParametros(lance, cor_atual);
        cor_atual = !cor_atual;
    }
}

void salvarPartida(Tabuleiro tabuleiro, int& numeroLances) {
    cout << "Deseja salvar a partida (S/N)? ";
    char resposta;
    cin >> resposta;
    if (resposta == 'S') {
        cout << "Digite o nome do arquivo: ";
        string nome;
        cin >> nome;
        ofstream arquivo;
        arquivo.open(nome, ios::app);
        pair<pair<int, int>, pair<int, int>> lance;
        for (int i = 0; i < numeroLances; i++) {
            lance = tabuleiro.getLance(i);
            char a = 'a' + lance.first.first;
            int b = 8 - lance.first.second;
            char c = 'a' + lance.second.first;
            int d = 8 - lance.second.second;
            arquivo << a << b << ' ' << c << d << endl;
        }
        arquivo.close();
    }
}

void abrirPartida() {
    system("cls");
    cout << endl << endl;
    unique_ptr<Tabuleiro> partida(new Tabuleiro());
    cout << "Insira o nome do arquivo (exemplo.txt): ";
    string nome;
    cin >> nome;
    ifstream arquivo;
    arquivo.open(nome);
    string linha;
    pair<pair<int, int>, pair<int, int>> lance;
    string pos_inicial, pos_final;
    int numeroLances = 0;
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            pos_inicial = linha.substr(0, 2);
            pos_final = linha.substr(3, 2);
            lance = converterLance(pos_inicial, pos_final);
            partida->atualizarLista(lance);
            numeroLances++;
        }
        int caracterPressionado = 1;
        int index = -1;
        cout << endl << endl << "Pressione 'S' para sair ou use as setas para navegar." << endl << endl;
        partida->imprimir();
        while (caracterPressionado != 83) { // "S" para sair
            caracterPressionado = _getch();
            if (caracterPressionado == 0 || caracterPressionado == 224) {
                caracterPressionado = _getch();
                if (caracterPressionado == 77 && index < (numeroLances - 1)) { // seta para a direita
                    index++;
                    if (!partida->testarRoque(partida->getLance(index))) {
                        partida->atualizar(partida->getLance(index));
                    }
                    system("cls");
                    cout << endl << endl;
                    cout << "Pressione 'S' para sair ou use as setas para navegar." << endl << endl;
                    partida->imprimir();
                }
                else if (caracterPressionado == 75 && index > -1) { // seta para a esquerda
                    pair<pair<int, int>, pair<int, int>>  lance;
                    pair<int, int> temporario;
                    if (!partida->testarRoqueInverso(partida->getLance(index))) {
                        lance = partida->getLance(index);
                        temporario = lance.first;
                        lance.first = lance.second;
                        lance.second = temporario;
                        partida->atualizar(lance);
                    }
                    index--;
                    system("cls");
                    cout << endl << endl;
                    cout << "Pressione 'S' para sair ou use as setas para navegar." << endl << endl;
                    partida->imprimir();
                }
                if (index == numeroLances - 1) cout << "Fim do jogo." << endl;
            }
        }
        arquivo.close();
    }
    else {
        cout << "Nao foi possivel abrir o arquivo" << endl;
    }
}