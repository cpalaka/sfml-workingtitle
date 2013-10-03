#include "Level.h"

Level::Level(MyContactListener* listener) :
	allowBullet(false),
	bullettime(0.0)
{
	b2world = new b2World(gravity);
	b2world->SetContactListener(&(*listener));
	player = NULL;


	pixelatedfont.loadFromFile("resources/fonts/Pixelated.ttf");
	sampletext.setFont(pixelatedfont);
	sampletext.setColor(sf::Color::Black);
	sampletext.setCharacterSize(14);
	sampletext.setPosition(1, 1);
	sampletext.setString("Hello, world!");
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
		
		ground->setb2Object(b2world, v, 4, platform, playr|playerSensor|bullet);
		sentitylist.push_back(ground);
		
		staticEntity* box = new staticEntity("resources/graphics/Stage1/box.png", 637.f, 265.f);
		std::vector<b2Vec2> v3;
		v3.push_back(b2Vec2(50.f/scale, 50.f/scale));
		v3.push_back(b2Vec2(-50.f/scale, 50.f/scale));
		v3.push_back(b2Vec2(-50.f/scale, -50.f/scale));
		v3.push_back(b2Vec2(50.f/scale, -50.f/scale));

		box->setb2Object(b2world, v3, 4, platform, playr|playerSensor|bullet);
		sentitylist.push_back(box);
		
		//load all dynamicobjects to be used (guns etc)
		

		//create enemies
		//create player
		player = new Player(100, 100);
		std::vector<b2Vec2> v2;//player shape
		v2.push_back(b2Vec2(15.f/scale,30.f/scale));
		v2.push_back(b2Vec2(-15.f/scale,30.f/scale));
		v2.push_back(b2Vec2(-15.f/scale,-30.f/scale));
		v2.push_back(b2Vec2(15.f/scale,-30.f/scale));

		player->setb2Object(b2world, v2, 4, 1.5f, 3.0f, true, playr, platform|bullet);

		player->setSensor(b2world,playerSensor, platform|enemy);
		player->setCurrentWindow(currentWindow);

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
		
		v.setCenter(player->anim.xpos+25, player->anim.ypos+30);

		//iterate through dentity list and update
		auto itr = dentitylist.begin();
		for(itr; itr != dentitylist.end(); ++itr)
		{
			(*itr)->update(delta);
		}
		//std::cout<<bulletlist.size()<<std::endl;
		auto bitr = bulletlist.begin();
		for(bitr; bitr != bulletlist.end(); ++bitr)
		{
			(*bitr)->update(delta);
		}
		//update player and get angle of player to mouse
		float angle = player->Player::update(evt, delta);


		//mouse has been clicked, angle is returned
		//so create new bullet
		//but only if the time since last bullet fired has been >0.6 second
		bullettime += delta;
		if(bullettime < 500.f)
		{
			if(allowBullet) allowBullet = false;
		} else { 
			allowBullet = true;
		}

		if(angle != -1 && allowBullet) 
		{
			allowBullet = false;
			bullettime = 0.f;
			
			sf::Vector2i mousepos = sf::Mouse::getPosition(*currentWindow);

			//create new instance of bullet and save it

			//***use parametric form of linear equation to solve the x,y coordinates of the initial bullet locations
			float k = 0.2;
			int x = (mousepos.x - player->body->GetWorldCenter().x*30)*k + player->body->GetWorldCenter().x*30;
			int y = (mousepos.y - player->body->GetWorldCenter().y*30)*k + player->body->GetWorldCenter().y*30;
			Bullet* bulletinstance = new Bullet(x-40,y , angle, mousepos);
			//***define the shape
			std::vector<b2Vec2> bulletshape;
			bulletshape.push_back(b2Vec2(3.f/scale, 2.f/scale));
			bulletshape.push_back(b2Vec2(-3.f/scale,2.f/scale));
			bulletshape.push_back(b2Vec2(-3.f/scale, -2.f/scale));
			bulletshape.push_back(b2Vec2(3.f/scale, -2.f/scale));
			bulletinstance->setb2Object(b2world, bulletshape, 4, 0.f, 1.f, true, bullet, platform|enemy);  
			bulletinstance->extraBodySettings();
			//***add instance of bullet to bulletlist
			bulletlist.push_back(bulletinstance);
		}
		//std::cout<<player->anim.xpos+25<<" "<<player->anim.ypos+22<<std::endl;
		//update enemies
		sampletext.setPosition(player->anim.xpos - 50, player->anim.ypos - 20);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	if(ltype == Menu)
	{
		window.draw(bgsprite);
	} else {

		window.draw(sampletext);
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

		auto bitr = bulletlist.begin();
		for(bitr; bitr != bulletlist.end(); ++bitr)
		{
			(*bitr)->draw(window);
		}
		player->Player::draw(window);
	}
}

void Level::setCurrentWindow(sf::RenderWindow* window)
{
	currentWindow = window;
}

void Level::removeBullet(int bulletno)
{
	auto bitr = bulletlist.begin();
	for(bitr; bitr != bulletlist.end(); ++bitr)
	{
		if((int)(*bitr)->body->GetUserData() == bulletno)
		{
			Bullet* temp = (*bitr);
			bulletlist.erase(bitr++);
			delete &temp;
		}
	}
}