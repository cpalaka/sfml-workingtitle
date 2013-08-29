#include "dynamicEntity.h"


dynamicEntity::dynamicEntity(std::string s, int _x, int _y)
{
	setTexture(s);
	setPosition(_x, _y);
}

void dynamicEntity::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount, float friction, float density, bool rot)
{
	b2BodyDef bd;
	bd.position.Set(x/scale, y/scale);
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

void dynamicEntity::update(double t)
{
	float x = body->GetPosition().x;
	float y = body->GetPosition().y;

	sf::IntRect rect = sprite.getTextureRect();
	//std::cout<<"("<<x<<","<<y<<")"<<std::endl;
	setPosition(x*scale, y*scale);
}

void dynamicEntity::setDrawableNull()
{

}