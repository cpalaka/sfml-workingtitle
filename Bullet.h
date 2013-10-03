#ifndef BULLET_H
#define BULLET_H

#include "Player.h"

class Bullet : public dynamicEntity {
public:
	Bullet(int, int, float, sf::Vector2i);
	void extraBodySettings();
	void update(double);
private:
	float angle;
	sf::Vector2i mousepos;
	static int bulletcount;
};

#endif BULLET_H