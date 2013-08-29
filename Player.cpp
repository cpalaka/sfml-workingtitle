#include "Player.h"

Player::Player(int _x, int _y) :
	dynamicEntity(" ", _x, _y)
{
	//set all player animations
}

void Player::update(sf::Event& evt, float delta)
{
	//anim.update(delta);

	//handle movement
	if(evt.type == sf::Event::KeyPressed)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::W:
			break;
		case sf::Keyboard::S:
			break;
		case sf::Keyboard::A:
			break;
		case sf::Keyboard::D:
			break;
		}
	}

	//handle shooting
	if(evt.type == sf::Event::MouseButtonPressed)
	{
	}

}

void Player::draw(sf::RenderWindow& window)
{
	anim.draw(window);
}