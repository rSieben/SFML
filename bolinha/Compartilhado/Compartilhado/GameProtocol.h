#pragma once
#define NC_MOVIMENTO_PERSONAGEM_REQ 1
#define NC_MOVIMENTO_PERSONAGEM_RES 2
#define TAMANHO_PACOTE 50

#define ESQUERDA 0
#define DIREITA 1
#define CIMA 2
#define BAIXO 3
#define VELOCIDADE 0.1f

struct ComandoMovimentoRequest {
	int comando = NC_MOVIMENTO_PERSONAGEM_REQ;
	bool cima;
	bool baixo;
	bool esquerda;
	bool direita;
};

struct ComandoMovimentoResponse {
	int comando = NC_MOVIMENTO_PERSONAGEM_RES;
	float x;
	float y;
};