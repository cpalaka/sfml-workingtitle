#ifndef LEVEL_H
#define LEVEL_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Enemy.h"
#include "staticEntity.h"
#include "MyContactListener.h"
#include "Bullet.h"

enum leveltype {Menu, Stage1};
const b2Vec2 gravity(0.0f, 20.f);

const static uint16 platform = 0x0001;
const static uint16 playr =0x0002;
const static uint16 enemy =0x0004;
const static uint16 gun =0x0008;
const static uint16 bullet =0x0010;
const static uint16 playerSensor =0x0020;
const static uint16 enemySensor =0x0040;

class Level {
public:
	Level(MyContactListener* listener);
	void draw(sf::RenderWindow& window);
	void setLevel(leveltype l); 
	void update(double, sf::Event&, sf::View&);
	void setCurrentWindow(sf::RenderWindow*);
	void removeBullet(int);
	leveltype ltype;
private:
	
	sf::Texture bgtexture;
	sf::Sprite bgsprite;

	sf::Font pixelatedfont;
	sf::Text sampletext;

	std::vector<staticEntity*> sentitylist;
	std::vector<dynamicEntity*> dentitylist;
	std::vector<Bullet*> bulletlist;
	std::vector<Enemy*> enemylist;
	sf::RenderWindow* currentWindow;
	Player* player;
	b2World* b2world;
	

	//bullet control members
	bool allowBullet;
	float bullettime;
};

#endif LEVEL_H