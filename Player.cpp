#include "Player.h"

Player::Player(int _x, int _y) :
	dynamicEntity("resources/graphics/Stage1/box.png", _x, _y),
	onGround(false),
	isJumping(false)
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
	walkleft.loadFromFile("resources/graphics/Player/player_run_left.png");
	anim.addAnimation(walkleft, "walkleft", 5, 0);

	anim.setCurrentAnim("walkright");
}

void Player::update(sf::Event& evt, float delta)
{
	anim.update(delta);
	std::string s;
	//handle movement
	if(evt.type == sf::Event::KeyPressed)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::Up:
			dir[0] = true;
			break;
		case sf::Keyboard::Down:
			dir[1] = true;
			break;
		case sf::Keyboard::Left:
			dir[2] = true;
			if((s = anim.getCurrentAnim()) != "walkleft")
				anim.setCurrentAnim("walkleft");
			break;
		case sf::Keyboard::Right:
			dir[3] = true;
			if((s = anim.getCurrentAnim()) != "walkright")
				anim.setCurrentAnim("walkright");
			break;
		}
	}

	if(evt.type == sf::Event::KeyReleased)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::Up:
			dir[0] = false;
			break;
		case sf::Keyboard::Down:
			dir[1] = false;
			break;
		case sf::Keyboard::Left:
			dir[2] = false;
			break;
		case sf::Keyboard::Right:
			dir[3] = false;
			break;
		}
	}

	if(onGround && isJumping) isJumping = false;

	if(dir[3] && onGround) body->SetLinearVelocity(b2Vec2(7.f, 0));
	if(dir[2] && onGround) body->SetLinearVelocity(b2Vec2(-7.f, 0));
	if(dir[0] && onGround && !isJumping)
	{
		body->ApplyLinearImpulse(b2Vec2(0.f, -0.4f), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));
		if(body->GetContactList() == NULL) onGround = false;
		isJumping = true;

	}

	if(dir[3] && !onGround) body->ApplyLinearImpulse(b2Vec2(.1, 0), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));
	if(dir[2] && !onGround) body->ApplyLinearImpulse(b2Vec2(-.1, 0), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));

	//std::cout<<dir[0]<<" "<<dir[1]<<" "<<dir[2]<<" "<<dir[3]<<" "<<std::endl;
	//handle shooting
	if(onGround) std::cout<<"onGround"<<std::endl;
	if(!onGround) std::cout<<"inAir"<<std::endl;

	anim.xpos = body->GetWorldCenter().x*scale - 20;
	anim.ypos = body->GetWorldCenter().y*scale - 30;
	

}

void Player::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount, float friction, float density, bool rot, uint16 categoryBits, uint16 maskBits)
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
	pshape.Set(arr, verticecount);

	b2FixtureDef fd;
	fd.shape = &pshape;
	fd.density = density;
	fd.friction = friction;
	fd.userData = (void*)1;
	fd.filter.categoryBits = categoryBits;
	fd.filter.maskBits = maskBits;
	body->CreateFixture(&fd);
	body->SetUserData(this);
}

void Player::setSensor(b2World* world, uint16 categoryBits, uint16 maskBits)
{

	b2PolygonShape pshape;
	pshape.SetAsBox(39.f/(2*scale), 10.f/(2*scale), b2Vec2(0, 30.f/scale), 0);

	b2FixtureDef fd;
	fd.shape = &pshape;
	fd.density = 0.f;
	fd.filter.categoryBits = categoryBits;
	fd.filter.maskBits = maskBits;
	fd.isSensor = true;
	fd.userData = this;
	
	sensor = body->CreateFixture(&fd);
	body->SetUserData(this);
}

void Player::draw(sf::RenderWindow& window)
{
	anim.draw(window);
}
