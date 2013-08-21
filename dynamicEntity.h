#ifndef DYNAMICENTITY_H
#define DYAMICENTITY_H

#include "Drawable.h"
const int scale = 30;

class dynamicEntity : public Drawable {
public:
	dynamicEntity(std::string, int, int);
	void setb2Object(b2World* world, 
					std::vector<b2Vec2> shape, 
					int verticecount,
					float friction,
					float density,
					bool rot);
protected:
	b2Body* body;
};

#endif DYNAMICENTITY_H;