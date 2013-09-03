#include "staticEntity.h"

staticEntity::staticEntity(std::string s, float _x, float _y)
{
	setTexture(s);//inherited drawable function
	setPosition(_x, _y);
}

void staticEntity::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount, uint16 categoryBits, uint16 maskBits)
{
	b2BodyDef bd;
	bd.position.Set(x/scale, y/scale);
	bd.type = b2_staticBody;

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
	//pshape.SetAsBox(550.f/(2*scale), 150.f/(2*scale));
	pshape.Set(arr, verticecount);

	b2FixtureDef fd;
	fd.shape = &pshape;
	fd.density = 0;
	fd.friction = 1.f;
	fd.filter.categoryBits = categoryBits;
	fd.filter.maskBits = maskBits;
	fd.userData = (void*)2;
	body->CreateFixture(&fd);
	
	body->SetUserData(this);
}