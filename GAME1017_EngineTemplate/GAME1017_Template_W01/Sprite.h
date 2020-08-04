#pragma once
#include "SDL.h"


#include <iostream>
#include <vector>

#define Gravit

class Sprite 
{
protected:
	SDL_Rect m_rSrc;
	SDL_FRect m_rDst;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	double m_angle;
public:
	Sprite(SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t)
		:m_rSrc(s), m_rDst(d), m_pRend(r), m_pText(t), m_angle(0.0) {}
	virtual void Render() { SDL_RenderCopyExF(m_pRend, m_pText, GetSrcP(), GetDstP(), m_angle, 0, SDL_FLIP_NONE); }
	SDL_Rect* GetSrcP() { return &m_rSrc; }
	SDL_FRect* GetDstP() { return &m_rDst; }
	double& GetAngle() { return m_angle; }
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
	AnimatedSprite(int sstart, int smin, int smax, int mf, SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t)
		:Sprite(s, d, r, t), m_iSprite(sstart), m_iSpriteMin(smin), m_iSpriteMax(smax), m_iFrameMax(mf) {}
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
	Player(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t);
	void Update();
	void Render();
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
	bool isGrounded();
	void SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void SetX(float y);
	void SetY(float y);
private:
	bool m_grounded;
	double m_accelX,
		m_accelY,
		m_velX,
		m_maxVelX,
		m_velY,
		m_maxVelY,
		m_drag,
		m_grav;
};