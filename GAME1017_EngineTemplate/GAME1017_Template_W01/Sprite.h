#pragma once
#include "SDL.h"


#include <iostream>
#include <vector>


class Sprite 
{
protected:
	SDL_Rect m_Src;
	SDL_FRect m_Dst;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	int m_x, m_y, m_angle;
public:
	Sprite() {}
	Sprite(SDL_Rect s, SDL_FRect d, SDL_Renderer * r, SDL_Texture* t) 
		:m_Src(s), m_Dst(d), m_pRend(r), m_pText(t) {}

	SDL_Rect* GetSrcP() { return &m_Src; }
	SDL_FRect* GetDstP() { return &m_Dst; }
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
	AnimatedSprite(int a, int fm, int sm, SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t)
		:Sprite(s, d, r, t), m_iFrameMax(fm), m_iSpriteMax(sm)
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
		m_Src.x = m_Src.w * m_iSprite;
	}
};

