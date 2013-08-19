#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>

class Drawable {
public:
	Drawable();
	void setTexture(std::string s);
	void draw(sf::RenderWindow& window);
	void setPosition(int, int);
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	int x;
	int y;
};

#endif DRAWABLE_H