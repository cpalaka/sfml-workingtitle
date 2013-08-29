#include "AnimationObject.h"

AnimationObject::AnimationObject() :
	anim_count(0)
{
	currentAnim = "";
	xpos = 0;
	ypos = 0;
}

void AnimationObject::addAnimation(sf::Texture& txt, std::string s, int no_of_frames, int animtype)
{
	Animation* anim = new Animation(txt, no_of_frames, animtype);
	animlist.insert(std::pair<std::string, Animation*>(s, anim));
	currentAnim = s;
	anim_count++;
}

void AnimationObject::update(double t)
{	
	std::map<std::string, Animation*>::iterator iter = animlist.find(currentAnim);
	(*iter).second->update(t);
}

void AnimationObject::setCurrentAnim(std::string s)
{
	//before changing the current animation, reset the previous animation
	std::map<std::string, Animation*>::iterator iter = animlist.find(currentAnim);
	(*iter).second->reset();

	currentAnim = s;
}

void AnimationObject::draw(sf::RenderWindow& window)
{
	std::map<std::string, Animation*>::iterator iter = animlist.find(currentAnim);
	(*iter).second->draw(window, xpos, ypos);
}

void AnimationObject::setFPS(std::string s, int fps)
{
	auto itr = animlist.begin();
	for(itr; itr != animlist.end(); ++itr)
	{
		if((*itr).first == s) (*itr).second->setFPS(fps);
	}
}

std::string AnimationObject::getCurrentAnim()
{
	return currentAnim;
}

void AnimationObject::setFreeze(std::string anim, int frame)
{
	auto itr = animlist.begin();
	for(itr; itr != animlist.end(); ++itr)
	{
		if((*itr).first == anim) (*itr).second->setFreeze(frame);
	}
}