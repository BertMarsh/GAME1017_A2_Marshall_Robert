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
		if (m_iFrame++ == m_iFrameMax)
		{
			m_iFrame = 0;
			if (m_iSprite++ == m_iSpriteMax)
			{
				m_iSprite = m_iSpriteMax;
			}
		}
		m_rSrc.x = m_rSrc.w * m_iSprite;
	}
};

class Player : public AnimatedSprite
{
public:
	Player(SDL_Rect s, SDL_Rect d)
		: AnimatedSprite(90, 8, 4, s, d) {}
//	void Update();
//	void Render();
//	void Stop();
//	void StopX();
//	void StopY();
//	void SetAccelX(double a);
//	void SetAccelY(double a);
//	bool isGrounded();
//	void SetGrounded(bool g);
//	double GetVelX();
//	double GetVelY();
//	void SetX(float y);
//	void SetY(float y);
//private:
//	bool m_grounded;
//	double m_accelX,
//		m_accelY,
//		m_velX,
//		m_maxVelX,
//		m_velY,
//		m_maxVelY,
//		m_drag,
//		m_grav;
};

