#include "Level.h"

Level::Level()
{
	ltype = Menu;
}

void Level::setLevel(leveltype l)
{
	ltype = l;
	switch(ltype)
	{
	case Menu:
		//load/set bg sprite and buttons

		break;
	}
}

void draw(sf::RenderWindow& window)
{

}
