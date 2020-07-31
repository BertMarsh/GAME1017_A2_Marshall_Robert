#pragma once
#include "State.h"

#include <vector>

class StateManager
{
public:
public:
	static void Update();
	static void Render();
	static void ChangeState(State* pState);//Normal state change
	static void PushState(State* pState);//GameState to PauseState
	static void PopState();//PauseState to GameState
	static void Clean();
	static std::vector<State*>& GetStates();
private:
	StateManager(); 
};
	static std::vector<State*> m_vStates;

//typedef STM; 