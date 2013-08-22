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

void Drawable::setPosition(float _x, float _y)
{
	//position is set in center of sprite, in pixels
	x = _x;
	y = _y;
	sf::IntRect rect = sprite.getTextureRect();
	//adjust to left top corner of sprite
	sprite.setPosition(x - rect.width/2, y - rect.height/2);
}