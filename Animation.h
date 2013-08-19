#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML\Graphics.hpp>
#include <iostream>



class Animation{
public:
	Animation(sf::Texture& txt, int n, int);
	void update(double);
	void draw(sf::RenderWindow&, int, int);
	void reset();
	void setFPS(int);
	void setFreeze(int);
private:
	int atype;
	int no_of_frames;
	sf::Sprite spriteimg;
	int currentframe;
	int animfps;
	bool freezeframe;
	double timecount;
	std::vector<sf::Sprite> frames;
};
#endif ANIMATION_H