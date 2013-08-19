#include "Drawable.h"

Drawable::Drawable()
{
}

void Drawable::setTexture(std::string s)
{
	texture.loadFromFile(s);
	sprite.setTexture(texture);
}

void Drawable::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Drawable::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
	sprite.setPosition(x, y);
}