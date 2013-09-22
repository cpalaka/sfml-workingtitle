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
	//and player arm
	walkright.loadFromFile("resources/graphics/Player/player_run_right.png");
	anim.addAnimation(walkright, "walkright", 5, 0);

	walkleft.loadFromFile("resources/graphics/Player/player_run_left.png");
	anim.addAnimation(walkleft, "walkleft", 5, 0);

	armtext.loadFromFile("resources/graphics/Player/arm.png");
	armspr.setTexture(armtext);
	armspr.setOrigin(5.f, 5.f);
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
		case sf::Keyboard::W:
			dir[0] = true;
			break;
		case sf::Keyboard::S:
			dir[1] = true;
			break;
		case sf::Keyboard::A:
			dir[2] = true;
			if((s = anim.getCurrentAnim()) != "walkleft")
				anim.setCurrentAnim("walkleft");
			break;
		case sf::Keyboard::D:
			dir[3] = true;
			if((s = anim.getCurrentAnim()) != "walkright")
				anim.setCurrentAnim("walkright");
			break;
		}
	}
	
	if(evt.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousepos = sf::Mouse::getPosition(*currentWindow);
		sf::Vector2i armcntr(330, 222);

		float height = armcntr.y - mousepos.y;
		float width = armcntr.x - mousepos.x;
		if(height<0) height = -height;
		if(width<0) width = -width;

		float angle = atan(height/width)*180/PI;
		if(mousepos.y > armcntr.y && mousepos.x > armcntr.x) armspr.setRotation(angle);
		if(mousepos.y < armcntr.y && mousepos.x > armcntr.x) armspr.setRotation(360-angle);
		if(mousepos.y < armcntr.y && mousepos.x < armcntr.x) armspr.setRotation(180+angle);
		if(mousepos.y > armcntr.y && mousepos.x < armcntr.x) armspr.setRotation(180-angle);
		std::cout<<"armcenter: ("<<armcntr.x<<", "<<armcntr.y<<" mousepos: ("<<mousepos.x<<", "<<mousepos.y<<std::endl;
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

	if(onGround && isJumping) isJumping = false;

	//press right
	if(dir[3] && !dir[0] && onGround) body->SetLinearVelocity(b2Vec2(7.f, 0));
	//press left
	if(dir[2] && !dir[0] && onGround) body->SetLinearVelocity(b2Vec2(-7.f, 0));
	//press up
	if(dir[0] && onGround && !isJumping)
	{
		body->ApplyLinearImpulse(b2Vec2(0.f, -0.6f), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));
		if(body->GetContactList() == NULL) onGround = false;isJumping = true;
	}
	//press up and left/right
	if((dir[3] && dir[0] && onGround && !isJumping) ||  
		(dir[2] && dir[0] && onGround && !isJumping) )
	{
		body->ApplyLinearImpulse(b2Vec2(0.f, -0.6f), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));
		if(body->GetContactList() == NULL) onGround = false;isJumping = true;
	}

	b2Vec2 vel = body->GetLinearVelocity();

	if(dir[3] && !onGround) if(vel.x < 4.f) body->ApplyLinearImpulse(b2Vec2(.1, 0), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));
	if(dir[2] && !onGround) if(vel.x > -4.f) body->ApplyLinearImpulse(b2Vec2(-.1, 0), b2Vec2(body->GetWorldCenter().x, body->GetWorldCenter().y));

	//handle shooting
	//if(onGround) std::cout<<"onGround"<<std::endl;
	//if(!onGround) std::cout<<"inAir"<<std::endl;

	anim.xpos = body->GetWorldCenter().x*scale - 20;
	anim.ypos = body->GetWorldCenter().y*scale - 30;

	armspr.setPosition(anim.xpos+25, anim.ypos+22);
}

void Player::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount, float friction, float density, bool rot, uint16 categoryBits, uint16 maskBits)
{
	b2BodyDef bd;
	//this is the reason we overrode the derived function, so that we get x y coordinates
	//from animationobject and not Drawable 
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
	pshape.SetAsBox(39.f/(2*scale), 5.f/(2*scale), b2Vec2(0, 30.f/scale), 0);

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
	window.draw(armspr);
}


void Player::setCurrentWindow(sf::RenderWindow* window)
{
	currentWindow = window;
}