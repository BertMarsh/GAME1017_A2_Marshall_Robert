#pragma once
#include <SDL.h>
#include <vector>

#include "Sprite.h"

class Obstacles : public Sprite
{
private:
	std::vector<Obstacles*> m_Obstacles;


public:
	Obstacles(SDL_Rect s, SDL_Rect d) :Sprite(s, d) {}
	void Spawn();
	void Update();
};