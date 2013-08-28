#include "Level.h"

Level::Level()
{
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
		staticEntity* ground = new staticEntity("resources/graphics/Stage1/ground.png",312.f, 350.f);
		std::vector<b2Vec2> v;
		
		v.push_back(b2Vec2(275.f/scale,75.f/scale));
	v.push_back(b2Vec2(-275.f/scale, 75.f/scale));
		v.push_back(b2Vec2(-275.f/scale, -75.f/scale));
		v.push_back(b2Vec2(275.f/scale, -75.f/scale));
		
		ground->setb2Object(b2world,v , 4);
		sentitylist.push_back(ground);
		
		//load all dynamicobjects to be used (guns etc)
		dynamicEntity* box = new dynamicEntity("resources/graphics/Stage1/box.png", 0, 100);
		std::vector<b2Vec2> v1;
		
		v1.push_back(b2Vec2(50.f/scale, 50.f/scale));
		v1.push_back(b2Vec2(-50.f/scale, 50.f/scale)); 
		v1.push_back(b2Vec2(-50.f/scale, -50.f/scale));
	v1.push_back(b2Vec2(50.f/scale, -50.f/scale));
		
		

		box->setb2Object(b2world, v1, 4, .8f, 1.0f, true);
		dentitylist.push_back(box);

		//create enemies
		//create player
		

		break;
	}
}

void Level::update(double delta)
{
	//b2world->ClearForces();
	b2world->Step(delta/1000, 8, 3);

	auto itr = dentitylist.begin();
	for(itr; itr != dentitylist.end(); ++itr)
	{
		(*itr)->update(delta);
	}
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
		auto itr = sentitylist.begin();
		for(itr; itr != sentitylist.end(); ++itr)
		{
			(*itr)->draw(window);
		}

		auto ditr = dentitylist.begin();
		for(ditr; ditr != dentitylist.end(); ++ditr)
		{
			(*ditr)->draw(window);
		}
	}
}
