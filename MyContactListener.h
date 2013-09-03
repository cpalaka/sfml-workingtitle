#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D\Box2D.h>
#include "Player.h"

class MyContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

};

#endif MYCONTACTLISTENER_H
