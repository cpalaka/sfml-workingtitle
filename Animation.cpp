#include "Animation.h"

Animation::Animation(sf::Texture& txt, int n, int type) :
	currentframe(1),
	animfps(12),
	freezeframe(false)
{
	timecount = 0;
	spriteimg.setTexture(txt);
	atype = type;

	no_of_frames = n;

	sf::FloatRect imgrect = spriteimg.getGlobalBounds();
	int t_width = imgrect.width;
	int f_height = imgrect.height;
	int f_width = t_width/no_of_frames;

	sf::Sprite temp = spriteimg;
	for(int i=0; i<no_of_frames;++i)
	{
		sf::IntRect r(i*f_width, 0, f_width, f_height);
		temp.setTextureRect(r);
		frames.push_back(temp);
	}
}

void Animation::update(double t)
{
	if(!freezeframe)
	{
		//add delta time to timecount
		timecount += t;
	
		//according to animfps, change frames in animation
		if(timecount > 1000/animfps)
		{
			if(++currentframe >= no_of_frames)
			{
				//check if animation is loop type or single
				if(atype == 0){ currentframe = 0;}
				else if(atype == 1){ currentframe = no_of_frames - 1; freezeframe = true;}
			}
			//reset timecount
			timecount = 0;
		}
	}
}

void Animation::draw(sf::RenderWindow& window, int x, int y)
{
		frames.at(currentframe).setPosition(x, y);
		window.draw(frames.at(currentframe));
}

void Animation::reset()
{
	currentframe = 0;
	freezeframe = 0;
}

void Animation::setFPS(int fps)
{
	animfps = fps;
}

void Animation::setFreeze(int frame)
{
	freezeframe = true;
	if(currentframe < no_of_frames) currentframe = frame-1;
	else currentframe = 0;
}