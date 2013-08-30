#include "Player.h"

Player::Player(int _x, int _y) :
	dynamicEntity("resources/graphics/Stage1/box.png", _x, _y),
	onGround(false)
{
	dir[0] = false;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;

	
	anim.xpos = _x - 20;
	anim.ypos = _y - 30;
	//set all player animations
	//sf::Texture walkright;
	walkright.loadFromFile("resources/graphics/Player/player_run_right.png");
	anim.addAnimation(walkright, "walkright", 5, 0);

	//sf::Texture walkleft;
	walkleft.loadFromFile("resources/graphics/Player/player_run_right.png");
	anim.addAnimation(walkleft, "walkleft", 5, 0);

	anim.setCurrentAnim("walkright");
}

void Player::update(sf::Event& evt, float delta)
{
	anim.update(delta);

	//handle movement
	if(evt.type == sf::Event::KeyPressed)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::W:
			dir[0] = true;
			break;
		case sf::Keyboard::S:
			dir[1] = true;
			break;
		case sf::Keyboard::A:
			dir[2] = true;
			break;
		case sf::Keyboard::D:
			dir[3] = true;
			break;
		}
	}

	if(evt.type == sf::Event::KeyReleased)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::W:
			dir[0] = false;
			break;
		case sf::Keyboard::S:
			dir[1] = false;
			break;
		case sf::Keyboard::A:
			dir[2] = false;
			break;
		case sf::Keyboard::D:
			dir[3] = false;
			break;
		}
	}

	//if(dir[4] && 
	//std::cout<<dir[0]<<" "<<dir[1]<<" "<<dir[2]<<" "<<dir[3]<<" "<<std::endl;
	//handle shooting
	if(evt.type == sf::Event::MouseButtonPressed)
	{
	}

	
	anim.xpos = body->GetWorldCenter().x*scale - 20;
	anim.ypos = body->GetWorldCenter().y*scale - 30;

}

void Player::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount, float friction, float density, bool rot)
{
	b2BodyDef bd;
	bd.position.Set((anim.xpos + 20)/scale, (anim.ypos + 30)/scale);
	bd.type = b2_dynamicBody;
	bd.fixedRotation = rot;
	

	body = world->CreateBody(&bd);

	b2Vec2* arr = new b2Vec2[verticecount];
	auto itr = shape.begin();
	int i = 0;
	for(itr; itr != shape.end(); ++itr)
	{
		arr[i].Set((*itr).x, (*itr).y);
		++i;
	}

	b2PolygonShape pshape;
	//pshape.SetAsBox(100.f/(2*scale), 100.f/(2*scale));
	pshape.Set(arr, verticecount);

	b2FixtureDef fd;
	fd.shape = &pshape;
	fd.density = density;
	fd.friction = friction;
	body->CreateFixture(&fd);
}

void Player::draw(sf::RenderWindow& window)
{
	anim.draw(window);
}