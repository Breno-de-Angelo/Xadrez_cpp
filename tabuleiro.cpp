#include "tabuleiro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;
enum direcao { horizontal, vertical, diagonal, cavalo, outro };
bool intToBool(int num) {
    bool resposta;
    num ? resposta = 1 : resposta = 0;
    return resposta;
}
template <typename T> T abs(T num) {
    num > 0 ? num *= 1 : num *= -1;
    return num;
}

Tabuleiro::Tabuleiro() :tabuleiro{ 't', 'c', 'b', 'd', 'r', 'b', 'c', 't', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' , ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' , 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' , 'T', 'C', 'B', 'D', 'R', 'B', 'C', 'T' },
rei_branco(make_pair(4, 7)), rei_preto(make_pair(4, 0)), roque_branco(1), roque_preto(1),
roque_grande_branco(1), roque_grande_preto(1), listaLances({}) {}

Tabuleiro::~Tabuleiro() {};

char Tabuleiro::get_peca(pair<int, int> pos){
    return this->tabuleiro[pos.second][pos.first];
}

void Tabuleiro::set_peca(pair<int, int> pos, char peca) {
    this->tabuleiro[pos.second][pos.first] = peca;
}

void Tabuleiro::set_rei(pair<int, int> posicao_final, bool cor)
{
    if (cor) rei_preto = posicao_final;
    else rei_branco = posicao_final;
}

pair<int, int> Tabuleiro::get_rei(bool cor)
{
    if (cor) {
        return rei_preto;
    }
    else return rei_branco;
}

pair<pair<int, int>, pair<int, int>> Tabuleiro::getLance(int index) {
    return this->listaLances.at(index);
}

bool Tabuleiro::testarRoque(pair<pair<int,int>,pair<int,int>> lance) {
    bool mexer_rei = 0;
    bool cor_rei = 0;
    if (lance.first == get_rei(0)) {
        mexer_rei = 1;
        cor_rei = 0;
    }
    else if (lance.first == get_rei(1)) {
        mexer_rei = 1;
        cor_rei = 1;
    }
    if (mexer_rei == 1) {
        if (lance.second.first == (lance.first.first + 2)) roque(cor_rei);
        else if (lance.second.first == (lance.first.first - 2)) roque_grande(cor_rei);
        else return 0;
        return 1;
    }
}

bool Tabuleiro::testarRoqueInverso(pair<pair<int, int>, pair<int, int>> lance) {
    bool mexer_rei = 0;
    bool cor_rei = 0;
    if (lance.second == get_rei(0)) {
        mexer_rei = 1;
        cor_rei = 0;
    }
    else if (lance.second == get_rei(1)) {
        mexer_rei = 1;
        cor_rei = 1;
    }
    if (mexer_rei == 1) {
        if (lance.second.first == (lance.first.first + 2)) roque_inverso(cor_rei);
        else if (lance.second.first == (lance.first.first - 2)) roque_grande_inverso(cor_rei);
        else return 0;
        return 1;
    }
}

void Tabuleiro::roque_inverso(bool cor) {
    if (cor) {
        set_peca(make_pair(4, 0), 'r');
        set_peca(make_pair(5, 0), ' ');
        set_peca(make_pair(6, 0), ' ');
        set_peca(make_pair(7, 0), 't');
        set_rei(make_pair(4, 0), 1);
    }
    else {
        set_peca(make_pair(4, 7), 'R');
        set_peca(make_pair(5, 7), ' ');
        set_peca(make_pair(6, 7), ' ');
        set_peca(make_pair(7, 7), 'T');
        set_rei(make_pair(4, 7), 0);
    }
    
}

void Tabuleiro::roque_grande_inverso(bool cor) {
    if (cor) {
        set_peca(make_pair(4, 0), 'r');
        set_peca(make_pair(3, 0), ' ');
        set_peca(make_pair(2, 0), ' ');
        set_peca(make_pair(1, 0), ' ');
        set_peca(make_pair(0, 0), 't');
        set_rei(make_pair(4, 0), 1);
    }
    else {
        set_peca(make_pair(4, 7), 'R');
        set_peca(make_pair(3, 7), ' ');
        set_peca(make_pair(2, 7), ' ');
        set_peca(make_pair(1, 7), ' ');
        set_peca(make_pair(0, 7), 'T');
        set_rei(make_pair(4, 7), 0);
    }
}


void Tabuleiro::atualizar(pair<pair<int, int>, pair<int, int>> lance) {
    this -> set_peca(lance.second, get_peca(lance.first));
	this -> set_peca(lance.first, ' ');
}

void Tabuleiro::atualizarLista(pair<pair<int, int>, pair<int, int>> lance) {
    this->listaLances.push_back(lance);
}

void Tabuleiro::imprimir() {
    for (int i = 0; i < 8; i++)
    {
        for (int k = 0; k < 3; k++) {
            std::cout << '\t';
            for (int j = 0; j < 8; j++)
            {
                if (k == 0 || k == 2) {
                    if ((i + j) % 2 == 0) {
                        printf("\033[100m       \033[0m");
                    }
                    else {
                        printf("\033[42m       \033[0m");
                    }
                }
                else {
                    if (islower(this->get_peca(make_pair(j, i)))) {
                        if ((i + j) % 2 == 0) {
                            printf("\033[100;30m   %c   \033[0m", this->get_peca(make_pair(j, i)));
                        }
                        else {
                            printf("\033[42;30m   %c   \033[0m", this->get_peca(make_pair(j, i)));
                        }
                    } 
                    else {
                        if ((i + j) % 2 == 0) {
                            printf("\033[100;97m   %c   \033[0m", this->get_peca(make_pair(j, i)));
                        }
                        else {
                            printf("\033[42;97m   %c   \033[0m", this->get_peca(make_pair(j, i)));
                        }
                    }
                }
            }
            if (k == 1) cout << "  " << 8 - i;
            cout << endl;
        }
    }
    std::cout << endl << '\t' <<  "   A   " << "   B   " << "   C   " << "   D   " << "   E   " << "   F   " << "   G   " << "   H   " << endl;
}

bool Tabuleiro::movimentoCompativel(pair<pair<int, int>, pair<int, int>> lance)
{
    int deltaX = lance.second.first - lance.first.first;
    int deltaY = lance.second.second - lance.first.second; 
    int direcaoMovimento = direcao{ outro };
    if (deltaX == 0) {
        if (deltaY == 0) return 0;
        direcaoMovimento = direcao{ vertical };
    }
    else if (deltaY == 0) direcaoMovimento = direcao{ horizontal };
    else {
        if (abs(deltaX) == abs(deltaY)) direcaoMovimento = direcao{ diagonal };
        if ((abs(deltaX) == 2 && abs(deltaY) == 1) || (abs(deltaX) == 1 && abs(deltaY) == 2)) direcaoMovimento = direcao{ cavalo };
    }
    if (direcaoMovimento == direcao{ outro }) return 0;
    int distancia = max(abs(deltaX), abs(deltaY));
    switch (tolower(this->get_peca(lance.first)))
    {
    case 'p':
        if ((direcaoMovimento == direcao{ vertical } || direcaoMovimento == direcao{ diagonal }) && distancia == 1) {
            if (((deltaY > 0) && intToBool(islower(this->get_peca(lance.first)))) ||
                ((deltaY < 0) && !intToBool(islower(this->get_peca(lance.first)))) )return 1;
        }
        break;
    case 'c':
        if (direcaoMovimento == direcao{ cavalo }) return 1;
            break;
    case 'b':
        if (direcaoMovimento == direcao{ diagonal }) return 1;
            break;
    case 't':
        if (direcaoMovimento == direcao{ horizontal } || direcaoMovimento == direcao{ vertical }) return 1;
            break;
    case 'd':
        if (direcaoMovimento == direcao{ diagonal } || direcaoMovimento == direcao{ horizontal } ||
            direcaoMovimento == direcao{ vertical }) return 1;
        break;
    case 'r':
        if ((direcaoMovimento == direcao{ diagonal } || direcaoMovimento == direcao{ horizontal } ||
            direcaoMovimento == direcao{ vertical }) && distancia == 1) return 1;
        break;
    }
    return 0;
}

bool Tabuleiro::caminhoValido(pair<pair<int, int>, pair<int, int>> lance) {
    int deltaX = lance.second.first - lance.first.first;
    int deltaY = lance.second.second - lance.first.second;
    int acrescimoX = 0;
    int acrescimoY = 0;
    if (deltaX != 0) acrescimoX = deltaX/abs(deltaX);
    if (deltaY != 0) acrescimoY = deltaY / abs(deltaY);
    lance.first.first += acrescimoX;
    lance.first.second += acrescimoY;
    while (lance.first != lance.second) {
        if (this->get_peca(lance.first) != ' ') return 0;
        lance.first.first += acrescimoX;
        lance.first.second += acrescimoY;
    }
    return 1;
}

bool Tabuleiro::validarMovimento(pair<pair<int, int>, pair<int, int>> lance, bool cor)
{
    if (lance.first.first < 0 || lance.first.second < 0 || lance.second.first < 0 || lance.second.second < 0 ||
        lance.first.first > 7 || lance.first.second > 7 || lance.second.first > 7 || lance.second.second > 7) return 0;
    if ((intToBool(islower(this->get_peca(lance.second))) == cor) && this->get_peca(lance.second) != ' ') return 0;
    if ((intToBool(islower(this->get_peca(lance.first))) != cor) && this->get_peca(lance.first) != ' ') return 0;
    if (!(this->movimentoCompativel(lance))) return 0;
    if (tolower(this->get_peca(lance.first)) != 'c' && tolower(this->get_peca(lance.first)) != 'r') {
        if (!this->caminhoValido(lance)) return 0;
    }
    return 1;
}

void Tabuleiro::voltarLance(pair<pair<int,int>, pair<int, int>> lance) {
    pair<int, int> temporario;
    temporario = lance.first;
    lance.first = lance.second;
    lance.second = temporario;
    this->atualizar(lance);
}

bool Tabuleiro::xeque(bool cor) {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) {
            if (validarMovimento(make_pair(make_pair(j, i), get_rei(cor)), !cor)) return 1;
        }
    }
    return 0;
}

bool Tabuleiro::validarLance(pair<pair<int, int>, pair<int, int>> lance, bool cor) {
    if (!validarMovimento(lance, cor)) return 0;
    this->atualizar(lance);
    if (lance.first == get_rei(cor)) set_rei(lance.second, cor);
    if (xeque(cor)) {
        voltarLance(lance);
        if (lance.second == get_rei(cor)) set_rei(lance.first, cor);
        return 0;
    }
    return 1;
}

bool Tabuleiro::roque(bool cor) {
    if (cor) {
        if (!roque_preto) return 0;
    }
    else {
        if (!roque_branco) return 0;
    }
    pair<pair<int, int>, pair<int, int>> lance1;
    pair<pair<int, int>, pair<int, int>> lance2;
    lance1 = make_pair(get_rei(cor), get_rei(cor));
    lance1.second.first++;
    if (validarLance(lance1, cor)) {
        lance2 = lance1;
        lance2.first.first++;
        lance2.second.first++;
        if (validarLance(lance2, cor)) {
            lance2.second.first++;
            set_peca(lance2.second, ' ');
            char c = 't';
            if (!cor) c = toupper(c);
            set_peca(lance2.first, c);
            return 1;
        }
        else {
            voltarLance(lance1);
            set_rei(lance1.first, cor);
            return 0;
        }
    }
    return 0;
}

bool Tabuleiro::roque_grande(bool cor) {
    if (cor) {
        if (!roque_grande_preto) return 0;
    }
    else {
        if (!roque_grande_branco) return 0;
    }
    pair<pair<int, int>, pair<int, int>> lance1;
    pair<pair<int, int>, pair<int, int>> lance2;
    lance1 = make_pair(get_rei(cor), get_rei(cor));
    lance1.first.first -= 3;
    if (get_peca(lance1.first) != ' ') return 0;
    lance1.first.first += 3;
    lance1.second.first--;
    if (validarLance(lance1, cor)) {
        lance2 = lance1;
        lance2.first.first--;
        lance2.second.first--;
        if (validarLance(lance2, cor)) {
            lance2.second.first -= 2;
            set_peca(lance2.second, ' ');
            char c = 't';
            if (!cor) c = toupper(c);
            set_peca(lance2.first, c);
            return 1;
        }
        else {
            voltarLance(lance1);
            set_rei(lance1.first, cor);
            return 0;
        }
    }
    return 0;
}

void Tabuleiro::atualizarParametros(pair<pair<int, int>, pair<int, int>> lance, bool cor) {
    pair<int, int> rei;
    cor ? rei = rei_preto : rei = rei_branco;
    if (lance.first == rei) {
        roque_preto = 0;
        roque_grande_preto = 0;
        roque_branco = 0;
        roque_grande_branco = 0;
        return;
    }
    if (cor) {
        if (roque_preto) {
            if (lance.first == make_pair(0, 7) || lance.second == make_pair(0, 7)) roque_preto = 0;
        }
        if (roque_grande_preto) {
            if (lance.first == make_pair(0, 0) || lance.second == make_pair(0, 0)) roque_grande_preto = 0;
        }
    }
    else {
        if (roque_branco) {
            if (lance.first == make_pair(7, 7) || lance.second == make_pair(7, 7)) roque_branco = 0;
        }
        if (roque_grande_branco) {
            if (lance.first == make_pair(7, 0) || lance.second == make_pair(7, 0)) roque_grande_branco = 0;
        }
    }
}