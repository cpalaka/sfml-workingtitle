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
			Player* player = static_cast<Player*>(fixA->GetBody()->GetUserData());
			player->onGround = true;
		}
		if(fixB->IsSensor())
		{
			Player* player = static_cast<Player*>(fixB->GetBody()->GetUserData());
			player->onGround = true;
		}

		if(fixA->GetUserData() == "bullet")
		{
			//levelinstance->removeBullet((int)fixA->GetBody()->GetUserData());
		}

		if(fixB->GetUserData() == "bullet")
		{
		
			//levelinstance->removeBullet((int)fixB->GetBody()->GetUserData());
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

		void* bodyUserData; 
		
		if(fixA->IsSensor())
		{
			Player* player = static_cast<Player*>(fixA->GetUserData());
			player->onGround = false;
			std::cout<<"INAIR(contactlistener)"<<std::endl;
		}
		if(fixA->IsSensor())
		{
			Player* player = static_cast<Player*>(fixB->GetUserData());
			player->onGround = false;
			std::cout<<"INAIR(contactlistener)"<<std::endl;
		}
		
	}
}

/*void MyContactListener::SetLevel(Level* level)
{
	levelinstance = level;
}
*/