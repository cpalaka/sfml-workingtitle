#ifndef PLAYER_H
#define PLAYER_H

#include "dynamicEntity.h"
#include "AnimationObject.h"
#include <math.h>

#define PI 3.14159265

class Player : public dynamicEntity {
public:
	Player(int, int);
	float update(sf::Event&, float);
	void draw(sf::RenderWindow&);
	void setb2Object(b2World*, std::vector<b2Vec2>, int, float, float, bool, uint16, uint16);
	void setSensor(b2World*, uint16 categoryBits, uint16 maskBits);
	void setCurrentWindow(sf::RenderWindow*);
	sf::Sprite armspr;
	AnimationObject anim;
	bool onGround;
private:
	sf::Texture walkleft, walkright;
	sf::Texture armtext;
	b2Fixture* sensor;
	bool isJumping;
	sf::RenderWindow* currentWindow;
	bool holdclick;
	bool dir[4];//up down left right
	float mouseangle;
};

#endif PLAYER_H