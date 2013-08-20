#include "staticEntity.h"

staticEntity::staticEntity(std::string s, int _x, int _y)
{
	setTexture(s);//inherited drawable function
	setPosition(_x, _y);
}