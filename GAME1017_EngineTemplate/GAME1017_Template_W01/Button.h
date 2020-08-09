#pragma once
#include <SDL.h>

#include "Sprite.h"

class Button : public Sprite
{
public:
	int Update();
	void Render();
protected:
	Button(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
	enum state { STATE_UP, STATE_DOWN, STATE_OVER } m_state;
	bool MouseCollision();
	virtual void Execute() = 0;
};

class PlayButton :public Button
{
private:
	Sprite* m_PlayB;
private:
	void Execute();
public:
	PlayButton(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
};

class RestartButton :public Button
{
private:
	Sprite* m_pMenuB;

private:
	void Execute();
public:
	RestartButton(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
};

class ResumeButton :public Button
{
private:
	Sprite* m_pResumeB;
private:
	void Execute();
public:
	ResumeButton(SDL_Rect src, SDL_FRect dst, SDL_Renderer* r, SDL_Texture* t);
};