#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "Drawable.h"

class staticEntity : public Drawable {
public:
	staticEntity(std::string);
protected:
	b2Body* body;
};

#endif STATICENTITY_H