#include "Level.h"

Level::Level()
{
	b2world = new b2World(gravity);
	player = NULL;
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
		
		ground->setb2Object(b2world, v, 4, platform, playr|playerSensor);
		sentitylist.push_back(ground);
		
		//load all dynamicobjects to be used (guns etc)
		

		//create enemies
		//create player
		player = new Player(100, 100);
		std::vector<b2Vec2> v2;//player shape
		v2.push_back(b2Vec2(15.f/scale,30.f/scale));
		v2.push_back(b2Vec2(-15.f/scale,30.f/scale));
		v2.push_back(b2Vec2(-15.f/scale,-30.f/scale));
		v2.push_back(b2Vec2(15.f/scale,-30.f/scale));

		player->setb2Object(b2world, v2, 4, 1.5f, 3.0f, true, playr, platform);

		player->setSensor(b2world,playerSensor, platform|enemy);
		b2world->SetContactListener(&myContactListener);
		break;
	}
}

void Level::update(double delta, sf::Event& evt, sf::View& v)
{

	if(ltype == Menu)
	{
		//if spacebar is pressed in menu, start game
		if(evt.type == sf::Event::KeyPressed)
			if(evt.key.code == sf::Keyboard::Space)
				setLevel(Stage1);
	} else {
		//step an iteration of box2d world
		b2world->Step(delta/1000, 8, 3);

		//set view
		//remember to change from first dynamic entity to the player position
		
		v.setCenter(player->anim.xpos+20, player->anim.ypos+30);

		//iterate through dentity list and update
		auto itr = dentitylist.begin();
		for(itr; itr != dentitylist.end(); ++itr)
		{
			(*itr)->update(delta);
		}
	
		//update player
		player->Player::update(evt, delta);

		//update enemies
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
		player->Player::draw(window);
	}
}
