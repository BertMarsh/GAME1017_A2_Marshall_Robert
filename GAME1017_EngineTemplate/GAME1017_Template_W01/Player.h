#pragma once
#include "Sprite.h"

#define GRAVITY 5.0
#define JUMPSTR 50.0

class Player : public Sprite
{
private:
	
private:
	bool m_grounded;
	double m_accelX,
		m_accelY,
		m_VelX,
		m_MaxVelX,
		m_VelY,
		m_MaxVelY,
		m_drag,
		m_grav;
public:
	Player(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t);
	void Update(bool sX, bool sY);
	void Stop();
	void StopX();
	void StopY();
	void SetAccelY(double a);
	void SetAccelX(double a);
	bool isGrounded();
	void SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void SetX(float y);
	void SetY(float y);



};