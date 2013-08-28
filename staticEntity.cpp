#include "staticEntity.h"

staticEntity::staticEntity(std::string s, float _x, float _y)
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
	fd.friction = defaultfriction;
	body->CreateFixture(&fd);

	
	sf::IntRect rect = sprite.getTextureRect();
	b2Vec2 center = body->GetWorldCenter();

	b2Vec2 topleft;
	topleft.x = 2;
	topleft.y = 9.6667;
	b2Vec2 local = body->GetLocalPoint(topleft);
	//std::cout<<local.x<<" "<<local.y<<std::endl;
	
	//std::cout<<center.x<<" "<<center.y<<std::endl;
	//std::cout<<center.x - (rect.width/2)/30<<" "<<center.y - (rect.height/2)/30<<std::endl;
	//std::cout<<rect.left/30<<" "<<rect.top/30<<std::endl;
	
}