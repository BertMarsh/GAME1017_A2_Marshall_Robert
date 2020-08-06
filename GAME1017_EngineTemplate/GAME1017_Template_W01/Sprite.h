#pragma once
#include "SDL.h"


#include <iostream>
#include <vector>


class Sprite 
{
protected:
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	double m_angle;
public:
	Sprite() {}
	Sprite(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t) 
		:m_rSrc(s), m_rDst(d), m_pRend(r), m_pText(t), m_angle(0.0) {}
	virtual void Render() { SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE); }
	SDL_Rect* GetSrcP() { return &m_rSrc; }
	SDL_FRect* GetDstP() { return &m_rDst; }
	double GetAngle() { return m_angle; }
	void SetAngle(double a) { m_angle = a; }
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
	AnimatedSprite(int a, int fm, int sm, SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t)
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
		m_rSrc.x = m_rSrc.w * m_iSprite;
	}
};

