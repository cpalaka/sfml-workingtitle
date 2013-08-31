#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "Drawable.h"
#include <iostream>
const float defaultfriction = 6.f;

class staticEntity : public Drawable {
public:
	staticEntity(std::string, float x, float y);
	void setb2Object(b2World* world, 
					std::vector<b2Vec2> shape, 
					int verticecount,
					uint16 categoryBits,
					uint16 maskBits);
					
protected:
	b2Body* body;
};

#endif STATICENTITY_H