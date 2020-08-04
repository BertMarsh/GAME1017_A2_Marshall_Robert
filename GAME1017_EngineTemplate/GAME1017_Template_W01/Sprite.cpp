#include "Sprite.h"
#include "Engine.h"

#include <algorithm>
#include<cmath>


Player::Player(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t) 
	: AnimatedSprite(90, 8, 4, s, d, r, t)
{
	
	
}

void Player::Update()
{
}

void Player::Render()
{
}

void Player::Stop()
{
}

void Player::StopX()
{
}

void Player::StopY()
{
}

void Player::SetAccelX(double a)
{
}

void Player::SetAccelY(double a)
{
}

bool Player::isGrounded()
{
	return false;
}

void Player::SetGrounded(bool g)
{
}

double Player::GetVelX()
{
	return 0.0;
}

double Player::GetVelY()
{
	return 0.0;
}

void Player::SetX(float y)
{
}

void Player::SetY(float y)
{
}

