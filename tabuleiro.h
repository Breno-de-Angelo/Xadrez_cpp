#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Tabuleiro {
	char tabuleiro[8][8];
	pair<int, int> rei_branco;
	pair<int, int> rei_preto;
	bool roque_branco;
	bool roque_preto;
	bool roque_grande_branco;
	bool roque_grande_preto;
	vector < pair<pair<int, int>, pair<int, int>>> listaLances;
public:
	Tabuleiro();
	~Tabuleiro();
	void set_peca(pair<int, int>, char);
	char get_peca(pair<int, int>);
	void set_rei(pair<int, int>, bool);
	pair<int, int> get_rei(bool);
	bool testarRoque(pair<pair<int, int>, pair<int, int>>);
	bool testarRoqueInverso(pair<pair<int, int>, pair<int, int>>);
	pair<pair<int, int>, pair<int, int>> getLance(int);
	void atualizar(pair<pair<int, int>, pair<int, int>>);
	void atualizarLista(pair<pair<int, int>, pair<int, int>>);
	void imprimir();
	bool movimentoCompativel(pair<pair<int, int>, pair<int, int>>);
	bool caminhoValido(pair<pair<int, int>, pair<int, int>>);
	bool validarMovimento(pair<pair<int, int>, pair<int, int>>, bool);
	void voltarLance(pair<pair<int, int>, pair<int, int>>);
	bool xeque(bool);
	bool validarLance(pair<pair<int, int>, pair<int, int>>, bool);
	bool roque(bool);
	bool roque_grande(bool);
	void roque_inverso(bool);
	void roque_grande_inverso(bool);
	void atualizarParametros(pair<pair<int, int>, pair<int, int>>, bool);
};