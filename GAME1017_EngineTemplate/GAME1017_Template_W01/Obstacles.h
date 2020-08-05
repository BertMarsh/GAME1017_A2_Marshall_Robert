#pragma once
#include <SDL.h>
#include <vector>

#include "Sprite.h"

class Obstacles : public Sprite
{
private:
	int m_Obstacles;
	SDL_Texture* ObsText;
public:
	Obstacles(SDL_Rect s, SDL_Rect d) :Sprite(s, d) {}
	void Spawn();
	void Update();
};