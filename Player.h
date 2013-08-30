#ifndef PLAYER_H
#define PLAYER_H

#include "dynamicEntity.h"
#include "AnimationObject.h"

class Player : public dynamicEntity {
public:
	Player(int, int);
	void update(sf::Event&, float);
	void draw(sf::RenderWindow&);
	void setb2Object(b2World*, std::vector<b2Vec2>, int, float, float, bool);
	AnimationObject anim;
private:
	sf::Texture walkleft, walkright;
	bool onGround;
	bool dir[4];//up down left right
};

#endif PLAYER_H