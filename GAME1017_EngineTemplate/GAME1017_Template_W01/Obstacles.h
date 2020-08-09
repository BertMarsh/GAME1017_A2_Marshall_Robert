#pragma once
#include <SDL.h>
#include <vector>

#include "Sprite.h"

class Obstacles : public Sprite
{
private:
	std::vector<Obstacles*> m_vObstacles;
public:
	Obstacles(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
	void Update();
};