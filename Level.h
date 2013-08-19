#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Enemy.h"
#include "staticEntity.h"

enum leveltype {Menu, Stage1 };

class Level {
public:
	Level();
	void draw(sf::RenderWindow& window);
	void setLevel(leveltype l);
private:
	leveltype ltype;
	sf::Texture bgtexture;
	sf::Sprite bgsprite;

	std::vector<staticEntity*> sentitylist;
	std::vector<Enemy*> enemylist;
	Player* player;
	b2World b2world;
};

#endif LEVEL_H