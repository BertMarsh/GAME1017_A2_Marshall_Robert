#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Player.h"
#include "Engine.h"

Player::Player(SDL_Rect s, SDL_FRect d, SDL_Renderer * r, SDL_Texture* t)
	:AnimatedSprite(90, 10, 8, s,d, r, t)
{
	m_grounded = false;
	m_accelX = m_accelY = m_VelX = m_VelY = 0.0;
	m_MaxVelX = 10.0;
	m_MaxVelY = JUMPSTR;
	m_grav = GRAVITY;
	m_drag = 0.88;
}

void Player::Update()
{
	//x-Axis
	m_VelX += m_accelX;
	m_VelX *= (m_grounded ? m_drag : 1);
	m_VelX = std::min(std::max(m_VelX, -(m_MaxVelX)), (m_MaxVelX));
	m_Dst.x += (int)m_VelX;
	//Y-Axis
	m_VelY += m_accelY + m_grav;
	m_VelY = std::min(std::max(m_VelY, -(m_MaxVelY)), (m_grav*3));
	m_Dst.y += (int) m_VelY;
	m_accelX = m_accelY = 0.0;
}

void Player::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), GetDstP());

}

void Player::Stop()
{
	StopX();
	StopY();
}

void Player::StopX() { m_accelX = m_VelX = 0.0; }
void Player::StopY() { m_accelY = m_VelY = 0.0; }
void Player::SetAccelY(double a) { m_accelY = a; }
void Player::SetAccelX(double a) { m_accelX = a; }
bool Player::isGrounded() { return m_grounded; }
void Player::SetGrounded(bool g) { m_grounded = g; }
double Player::GetVelX() { return m_VelX; }
double Player::GetVelY() { return m_VelY; }
void Player::SetX(float y) { m_Dst.x = y ; }
void Player::SetY(float y){m_Dst.y = y ; }
