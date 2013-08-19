#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>
#include "Animation.h"
#include "AnimationObject.h"
#include "Level.h"

const static int windowX = 660;
const static int windowY = 450;

class Game {
public:
	Game();
	void start();
	void gameloop();
	void update();
	void render();
private:
	sf::RenderWindow gameWindow;
	Level* currentlevel;

};

