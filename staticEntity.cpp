#include "staticEntity.h"

staticEntity::staticEntity(std::string s, int _x, int _y)
{
	setTexture(s);//inherited drawable function
	setPosition(_x, _y);
}

void staticEntity::setb2Object(b2World* world, std::vector<b2Vec2> shape, int verticecount)
{
	b2BodyDef bd;
	bd.position.Set(x/scale, y/scale);
	bd.type = b2_staticBody;

	body = world->CreateBody(&bd);

	b2Vec2* arr = new b2Vec2[verticecount];

	//std::cout<<shape.at(0).x<<" "<<shape.at(0).y<<std::endl;
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
	fd.density = 0;
	fd.friction = defaultfriction;
	body->CreateFixture(&fd);

	/*
	sf::IntRect rect = sprite.getTextureRect();
	b2Vec2 center = body->GetWorldCenter();
	std::cout<<center.x*scale<<" "<<center.y*scale<<std::endl;
	std::cout<<center.x*scale - rect.width/2<<" "<<center.y*scale - rect.height/2<<std::endl;
	std::cout<<rect.left<<" "<<rect.top<<std::endl;
	*/
}