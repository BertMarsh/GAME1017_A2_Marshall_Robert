#pragma once
#include <SDL.h>

#include "Sprite.h"

#include <vector>


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
	Sprite BgArray[2];
public:
	GameState();
	void Enter();
	void Update();
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

class StateManager
{
private:
	std::vector<State*> m_vStates;
public:
	StateManager();
	~StateManager();
	void Update();
	void Render();
	void ChangeState(State* pState);//Normal state change
	void PushState(State* pState);//GameState to PauseState
	void PopState();//PauseState to GameState
	void Clean();
	std::vector<State*>& GetStates();
};