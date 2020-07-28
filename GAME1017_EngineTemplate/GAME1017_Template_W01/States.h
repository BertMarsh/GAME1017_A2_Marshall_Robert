#pragma once


class State
{
protected:
	State() {}
public:
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Resume();
	virtual void Exit();
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