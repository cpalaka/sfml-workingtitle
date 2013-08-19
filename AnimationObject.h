#include <SFML\Graphics.hpp>
#include <map>


#include "Animation.h"

#ifndef ANIMATIONOBJECT_H
#define ANIMATIONOBJECT_H

class AnimationObject {
public:
	AnimationObject();
	void addAnimation(sf::Texture&, std::string, int, int);
	void update(double);
	void setCurrentAnim(std::string);
	void draw(sf::RenderWindow&);
	void setFPS(std::string, int);//default fps is 12
	void setFreeze(std::string, int); //freeze animation at framenumberv
	std::string getCurrentAnim();

	int xpos;
	int ypos;
	int position;//0 right, 1 left
	bool isActive;
	bool isJumping;
private:
	std::map<std::string, Animation*> animlist;
	std::string currentAnim;
	int anim_count;
};
#endif ANIMATIONOBJECT_H