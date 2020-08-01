#pragma once
#include "SDL.h"


#include <iostream>
#include <vector>

class Sprite 
{
protected:
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	int m_x, m_y, m_angle;
public:
	Sprite();
	Sprite(SDL_Rect s, SDL_Rect d);
	SDL_Rect* GetSrcP();
	SDL_Rect* GetDstP();
	double GetAngle();
};

class AnimatedSprite : public Sprite
{
protected:
	int m_iSprite,
		m_iSpriteMax,
		m_iFrame,
		m_iFrameMax;
public:
	AnimatedSprite(int a, int fm, int sm, SDL_Rect s, SDL_Rect d);
	void Animate();
};

class Player : public AnimatedSprite
{
public: 
	Player(SDL_Rect s, SDL_Rect d);
};