#ifndef PLAYER_H
#define PLAYER_H

#include "dynamicEntity.h"
#include "AnimationObject.h"

class Player : public dynamicEntity {
public:
	Player(int, int);
	void update(sf::Event&, float);
	void draw(sf::RenderWindow&);
private:
	AnimationObject anim;
};

#endif PLAYER_H