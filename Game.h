#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>
#include "Animation.h"
#include "AnimationObject.h"
#include "Level.h"
#include <chrono>

const static int windowX = 660;
const static int windowY = 450;

class Game {
public:
	Game();
	void start();
	void gameloop();
private:
	sf::RenderWindow gameWindow;
	sf::View view;
	Level* currentlevel;
	double deltatime;

};

