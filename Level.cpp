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
		bgtexture.loadFromFile("resources/graphics/Menu/menubg.png");
		bgsprite.setTexture(bgtexture);
		bgsprite.setPosition(0,0);
		break;
	case Stage1:
		//load all staticobjects (platforms)
		//load all dynamicobjects to be used (guns)
		//create enemies
		//create player

		break;
	}
}

void Level::update(double delta)
{

}

void Level::checkInput(sf::Event evt)
{
	if(ltype == Menu)
	{
		//if spacebar is pressed in menu, start game
		if(evt.type == sf::Event::KeyPressed)
			if(evt.key.code == sf::Keyboard::Space)
				setLevel(Stage1);
	} else {

	}
}

void Level::draw(sf::RenderWindow& window)
{
	if(ltype == Menu)
	{
		window.draw(bgsprite);
	} else {

	}
}
