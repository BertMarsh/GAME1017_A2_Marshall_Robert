#pragma once
#include "SDL.h"


#include <iostream>
#include <vector>


class Sprite 
{
protected:
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	int m_x,
		m_y,
		m_angle;
public:
	Sprite() {}
	Sprite(SDL_Rect s, SDL_Rect d) :m_rSrc(s), m_rDst(d) {}
	SDL_Rect* GetSrcP() { return &m_rSrc; }
	SDL_Rect* GetDstP() { return &m_rDst; }
	double GetAngle() { return m_angle; }
	
};

class AnimatedSprite : public Sprite
{
protected:
	int m_iSprite,
		m_iSpriteMax,
		m_iSpriteMin,
		m_iFrame,
		m_iFrameMax;
public:
	AnimatedSprite(int a, int fm, int sm, SDL_Rect s, SDL_Rect d)
		:Sprite(s, d), m_iFrameMax(fm), m_iSpriteMax(sm)
	{
		m_angle = a;
		m_iSprite = m_iFrame = 0;
	}
	
	void Animate()
	{
		m_iFrame++;
		if (m_iFrame == m_iFrameMax)
		{
			m_iFrame = 0;
			m_iSprite++;
			if (m_iSprite == m_iSpriteMax)
			{
				m_iSprite = 0;
			}
		}
		m_rSrc.x = m_rSrc.w * m_iSprite;
	}
};

