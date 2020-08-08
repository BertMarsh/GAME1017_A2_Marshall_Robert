#pragma once
#define NUMPLATFORMS 1

#include <SDL.h>
#include <vector>

#include "Sprite.h"
#include "Player.h"
#include "Button.h"
#include "Obstacles.h"




class State
{
protected:
	State() {}
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Resume();
	virtual void Exit() = 0;
};

class TitleState : public State
{
private:
	SDL_Texture* m_BText;
	Sprite m_PlayB;
public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class GameState : public State
{
private:
	SDL_Texture* m_pBGText;
	SDL_Texture* m_pFGText;
	SDL_Texture* m_pPText;
	Sprite BgArray[2];
	Sprite FgArray[2];
	Sprite PArray[5];
	SDL_FRect* m_pPlatforms[NUMPLATFORMS];
	
	
	SDL_Texture* m_pSprText;
	Player* m_pPlayer;
	SDL_Point m_pivot;
	SDL_Renderer* m_pRend;
	SDL_Texture* m_pText;
	
	int m_iOSpawn, m_iOSpawnMax;
	std::vector<Obstacles*> m_vObstacles;
	SDL_Texture* m_pOText;
	Obstacles* m_pObstacles;
public:
	GameState();
	void Enter();
	void Update();
	void CheckCollision();
	void setGrounded(bool g);
	void Render();
	void Resume();
	void Exit();
};

class PauseState : public State
{
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class EndState : public State
{
public:
	EndState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

