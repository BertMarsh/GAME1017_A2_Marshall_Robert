#pragma once
#include <SDL.h>

#include "Sprite.h"

class Button : public Sprite
{
public: 
	int Update();
	void Render();
protected:
	Button(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t);
	enum state { STATE_UP, STATE_DOWN, STATE_OVER } m_state;
	bool MouseCollision();
	virtual void Execute() = 0;
};

class PlayButton :public Button
{
private:
	void Execute();
public:
	PlayButton(SDL_Rect src, SDL_Rect dst, SDL_Renderer* r, SDL_Texture* t);
};

class RestartButton :public Button
{

};