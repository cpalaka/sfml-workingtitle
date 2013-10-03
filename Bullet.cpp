#include "Bullet.h"

Bullet::Bullet(int _x, int _y, float _angle, sf::Vector2i _mousepos) :
	dynamicEntity("resources/graphics/Items/bullet.png", _x, _y)
{
	angle = _angle;
	sprite.setRotation(angle);
	mousepos = _mousepos;
	bulletcount++;
}

void Bullet::extraBodySettings()
{
	body->SetFixedRotation(true);
	body->SetTransform(b2Vec2(x/30, y/30), angle*(b2_pi/180));
	body->SetBullet(true);
	body->SetGravityScale(0.f);

	body->SetUserData((void*)++bulletcount);
	b2Fixture* f = body->GetFixtureList();
	f->SetUserData((void*)"bullet");
}

void Bullet::update(double t)
{
	float x = body->GetPosition().x;
	float y = body->GetPosition().y;

	sf::IntRect rect = sprite.getTextureRect();
	setPosition(x*scale, y*scale);
	//std::cout<<"("<<mousepos.x<<","<<mousepos.y<<")"<<std::endl;
	
	body->ApplyForceToCenter(b2Vec2((mousepos.x-330)/2,(mousepos.y-222)/2));
}

int Bullet::bulletcount = 0;