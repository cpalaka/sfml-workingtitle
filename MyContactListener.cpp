#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
	const b2Filter& filterA = contact->GetFixtureA()->GetFilterData();
	const b2Filter& filterB = contact->GetFixtureB()->GetFilterData();

	bool collide = (filterA.maskBits & filterB.categoryBits) != 0 &&
				   (filterA.categoryBits & filterB.maskBits) != 0;

	if(collide)
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		if(fixA->IsSensor())
		{
			Player* player = static_cast<Player*>(fixA->GetUserData());
			player->onGround = true;
		}
		if(fixB->IsSensor())
		{
			Player* player = static_cast<Player*>(fixB->GetUserData());
			player->onGround = true;
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	const b2Filter& filterA = contact->GetFixtureA()->GetFilterData();
	const b2Filter& filterB = contact->GetFixtureB()->GetFilterData();

	bool collide = (filterA.maskBits & filterB.categoryBits) != 0 &&
				   (filterA.categoryBits & filterB.maskBits) != 0;

	if(collide)
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		if(fixA->IsSensor())
		{
			Player* player = static_cast<Player*>(fixA->GetUserData());
			player->onGround = false;
			//std::cout<<"INAIR"<<std::endl;
		}
		if(fixA->IsSensor())
		{
			Player* player = static_cast<Player*>(fixB->GetUserData());
			player->onGround = false;
			//std::cout<<"INAIR"<<std::endl;
		}
	}
}