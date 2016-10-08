#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Jogo.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <GameProtocol.h>

#define VELOCIDADE 5.f
SOCKET meuSocket;
sockaddr_in enderecoServidor;
sf::CircleShape shape;

void ConfigurarRede() {
	int r;
	WSAData wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	meuSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in e;
	e.sin_family = AF_INET;
	InetPton(AF_INET, "0.0.0.0", &e.sin_addr);
	e.sin_port = htons(12345);

	r = bind(meuSocket, (SOCKADDR*)&e, NULL);

	enderecoServidor.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &enderecoServidor.sin_addr);
	enderecoServidor.sin_port = htons(123456);
}

void tratarMovimentacao(sf::CircleShape& shape) {
	
	bool houveMovimento = false;
	ComandoMovimentoRequest req;
	req.baixo = req.cima = req.esquerda = req.direita = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		req.direita = houveMovimento = true;
		/*auto pos = shape.getPosition();
		pos.x += VELOCIDADE;
		shape.setPosition(pos);*/
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		req.esquerda = houveMovimento = true;
		/*auto pos = shape.getPosition();
		pos.x -= VELOCIDADE;
		shape.setPosition(pos);*/
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		req.cima = houveMovimento = true;
		/*	auto pos = shape.getPosition();
		pos.y -= VELOCIDADE;
		shape.setPosition(pos);*/
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		req.baixo = houveMovimento = true;
		/*auto pos = shape.getPosition();
		pos.y += VELOCIDADE;
		shape.setPosition(pos);*/
	}

	if (houveMovimento)
		sendto(meuSocket
				, (const char*)&req
				, TAMANHO_PACOTE
				, NULL
				, (SOCKADDR*)&enderecoServidor
				, sizeof(sockaddr_in)
				);

}

void receberPacotes() {
	char buffer[TAMANHO_PACOTE];
	sockaddr_in remetente;
	int remetenteTamanho = sizeof(remetente);

	int r;
	do {
		r = recvfrom(meuSocket
			, buffer
			, TAMANHO_PACOTE
			, 0
			, (SOCKADDR*)&remetente
			, &remetenteTamanho);

		if (r != SOCKET_ERROR)
		{
			ComandoMovimentoResponse res = *((ComandoMovimentoResponse*)buffer);
			shape.setPosition(res.x, res.y);
		}

	} while (true);

}

int main()
{
	ConfigurarRede();
	
	std::thread* th = new std::thread(receberPacotes);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Ola mundo");

	shape.setRadius(40.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Cyan);

	while (window.isOpen()) {

		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		tratarMovimentacao(shape);

		window.clear();
		window.draw(shape);
		window.display();

	}
	
}