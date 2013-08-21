#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Enemy.h"
#include "staticEntity.h"

enum leveltype {Menu, Stage1 };
const b2Vec2 gravity(0.0f, 9.8f);


class Level {
public:
	Level();
	void draw(sf::RenderWindow& window);
	void setLevel(leveltype l);
	void update(double);
	void checkInput(sf::Event);
private:
	leveltype ltype;
	sf::Texture bgtexture;
	sf::Sprite bgsprite;

	std::vector<staticEntity*> sentitylist;
	std::vector<Enemy*> enemylist;
	Player* player;
	b2World* b2world;
};

#endif LEVEL_H