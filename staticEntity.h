#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "Drawable.h"

class staticEntity : public Drawable {
public:
	staticEntity(std::string, int x, int y);
protected:
	b2Body* body;
};

#endif STATICENTITY_H