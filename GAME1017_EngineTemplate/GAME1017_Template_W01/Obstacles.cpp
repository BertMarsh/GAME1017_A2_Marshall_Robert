#include <ctime>
#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Obstacles.h"
#include "Engine.h"

Obstacles::Obstacles(SDL_Rect src, SDL_Rect dst, SDL_Renderer* r, SDL_Texture* t) 
	:Sprite (src, dst, r, t) {}

void Obstacles::Update()
{
}
