#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Enemy.h"
#include "staticEntity.h"
#include "MyContactListener.h"

enum leveltype {Menu, Stage1};
const b2Vec2 gravity(0.0f, 9.8f);

const static uint16 platform = 0x0001;
const static uint16 playr =0x0002;
const static uint16 enemy =0x0004;
const static uint16 gun =0x0008;
const static uint16 bullet =0x0010;
const static uint16 playerSensor =0x0020;
const static uint16 enemySensor =0x0040;

class Level {
public:
	Level();
	void draw(sf::RenderWindow& window);
	void setLevel(leveltype l); 
	void update(double, sf::Event&, sf::View&);
	leveltype ltype;
private:
	
	sf::Texture bgtexture;
	sf::Sprite bgsprite;

	std::vector<staticEntity*> sentitylist;
	std::vector<dynamicEntity*> dentitylist;
	std::vector<Enemy*> enemylist;
	Player* player;
	b2World* b2world;
	MyContactListener myContactListener;
};

#endif LEVEL_H