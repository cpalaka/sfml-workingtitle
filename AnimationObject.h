#include <SFML\Graphics.hpp>
#include <map>


#include "Animation.h"

#ifndef ANIMATIONOBJECT_H
#define ANIMATIONOBJECT_H

class AnimationObject {
public:
	AnimationObject();
	void addAnimation(sf::Texture&, std::string, int no_of_frames, int animtype);
	void update(double);
	void setCurrentAnim(std::string);
	void draw(sf::RenderWindow&);
	void setFPS(std::string, int);//default fps is 12
	void setFreeze(std::string, int); //freeze animation at framenumberv
	std::string getCurrentAnim();

	float xpos;
	float ypos;
private:
	std::map<std::string, Animation*> animlist;
	std::string currentAnim;
	int anim_count;
};
#endif ANIMATIONOBJECT_H