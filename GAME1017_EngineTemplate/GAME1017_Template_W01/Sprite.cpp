#include <algorithm>
#include<cmath>
#include "Sprite.h"
#include "Engine.h"

Sprite::Sprite(){}
Sprite::Sprite(SDL_Rect s, SDL_Rect d) :m_rSrc(s), m_rDst(d){}
SDL_Rect* Sprite::GetSrcP() { return &m_rSrc; }
SDL_Rect* Sprite::GetDstP() { return &m_rDst; }

AnimatedSprite::AnimatedSprite(int a, int fm, int sm, SDL_Rect s, SDL_Rect d) :
	Sprite(s, d), m_iFrameMax(fm), m_iSpriteMax(sm)
{
	m_angle = a;
	m_iSprite = m_iFrame = 0;
}

void AnimatedSprite::Animate()
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

