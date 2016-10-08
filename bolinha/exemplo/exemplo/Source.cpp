#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jogo.h"
#include <GameProtocol.h>

#define VELOCIDADE 0.5f

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

}

int main()
{

	sf::RenderWindow window(sf::VideoMode(640, 480), "Ola mundo");

	sf::CircleShape shape;
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