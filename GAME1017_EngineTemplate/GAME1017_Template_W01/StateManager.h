#pragma once
#include "States.h"

#include <vector>

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