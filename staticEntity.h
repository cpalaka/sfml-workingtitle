#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "Drawable.h"
#include <iostream>
const float defaultfriction = 6.f;

class staticEntity : public Drawable {
public:
	staticEntity(std::string, int x, int y);
	void setb2Object(b2World* world, 
					std::vector<b2Vec2> shape, 
					int verticecount);
					
protected:
	b2Body* body;
};

#endif STATICENTITY_H