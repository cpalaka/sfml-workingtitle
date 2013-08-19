#include "Game.h"

Game::Game()
{
	gameWindow.create(sf::VideoMode(windowX, windowY), "workingtitle");
	currentlevel = new Level();
}

void Game::start()
{
	//gameWindow.setFramerateLimit(60);
	while(gameWindow.isOpen())
	{
		gameloop();
	}
}

void Game::gameloop()
{
	gameWindow.clear(sf::Color(255,255,255));

	update();
	currentlevel->draw(gameWindow);
	
	gameWindow.display();
}

void Game::update()
{
}

void Game::render()
{
	currentlevel->draw(gameWindow);
}