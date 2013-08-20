#include "Level.h"

Level::Level()
{
	ltype = Menu;
	b2world = new b2World(gravity);
}

void Level::setLevel(leveltype l)
{
	ltype = l;
	switch(ltype)
	{
	case Menu:
		//load/set bg sprite and buttons
		bgtexture.loadFromFile("resources\graphics\menubg.png");
		break;
	case Stage1:
		//load all staticobjects (platforms)
		//load all dynamicobjects to be used (guns)
		//create enemies
		//create player

		break;
	}
}

void draw(sf::RenderWindow& window)
{

}
