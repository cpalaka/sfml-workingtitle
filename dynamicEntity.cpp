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
	for(int i = 0; i<verticecount; ++i)
	{
		arr[i] = (*itr);
	}

	b2PolygonShape pshape;
	pshape.Set(arr, verticecount);

	b2FixtureDef fd;
	fd.shape = &pshape;
	fd.density = density;
	fd.friction = friction;
	body->CreateFixture(&fd);
}