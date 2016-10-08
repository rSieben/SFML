#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <GameProtocol.h>

SOCKET servidorSocket;

struct Jogador {
	float x = 100.f, y = 100.f;
};

Jogador jogador;

void configurarRede() {
	int r;
	WSAData wsaData;
	r = WSAStartup(MAKEWORD(2, 2), &wsaData);
	servidorSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in e;
	e.sin_family = AF_INET;
	e.sin_port = htons(123456);
	InetPton(AF_INET, "0.0.0.0", &e.sin_addr);
	r = bind(servidorSocket, (SOCKADDR*)&e, sizeof(e));
}

int main() {

	configurarRede();
	char buffer[TAMANHO_PACOTE];
	sockaddr_in remetente;
	int remetenteTamanho = sizeof(remetente);

	int r;
	do {
		r = recvfrom(servidorSocket
						,buffer
						,TAMANHO_PACOTE
						,0
						,(SOCKADDR*)&remetente
						,&remetenteTamanho);
	
		if (r != SOCKET_ERROR)
		{
			ComandoMovimentoRequest req = *((ComandoMovimentoRequest*)buffer);

			if (req.direita)
				jogador.x += VELOCIDADE;

			if (req.esquerda)
				jogador.x -= VELOCIDADE;

			if (req.cima)
				jogador.y -= VELOCIDADE;

			if (req.baixo)
				jogador.y += VELOCIDADE;
		
			ComandoMovimentoResponse res;
			res.x = jogador.x;
			res.y = jogador.y;

			r = sendto(servidorSocket 
								, (const char*)&res
								, TAMANHO_PACOTE
								, NULL
								,(SOCKADDR*)&remetente
								,sizeof(remetente));

		}

	} while (true);

}
