#include "State.h"
#include "Engine.h"


#include <iostream>

//Base
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume(){}

//TitleState
TitleState::TitleState() {}
void TitleState::Enter()
{
	std::cout << "Welcome to the game! \n" << "Entering TitleState" << std::endl;
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_G))
		Engine::Instance().GetStateManager().ChangeState(new GameState());
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 128, 45, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting Title." << std::endl;
}

//GameState
GameState::GameState() {}

void GameState::Enter()
{
	std::cout << "Entering Game." << std::endl;
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_T))
		Engine::Instance().GetStateManager().ChangeState(new TitleState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		Engine::Instance().GetStateManager().ChangeState(new PauseState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_E))
		Engine::Instance().GetStateManager().ChangeState(new EndState());
}

void GameState::Render()
{
	std::cout << "Rendering Game." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	if (dynamic_cast<GameState*>(Engine::Instance().GetStateManager().GetStates().back()))
		State::Render();
}

void GameState::Resume()
{

}

void GameState::Exit()
{
	std::cout << "Exiting Game." << std::endl;
}

//PauseState
PauseState::PauseState() {}

void PauseState::Enter()
{
	std::cout << "Pausing Game" << std::endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		Engine::Instance().GetStateManager().PopState();
}

void PauseState::Render()
{
	Engine::Instance().GetStateManager().GetStates().front()->Render();
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 128, 0, 128, 128);
	SDL_Rect pRect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &pRect);
	State::Render();
}

void PauseState::Exit()
{
	std::cout << "Returning to Game" << std::endl;
}

//EndState
EndState::EndState()
{
	
}

void EndState::Enter()
{
}

void EndState::Update()
{
if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
		Engine::Instance().GetStateManager().ChangeState(new TitleState());
}
void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 128, 128, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void EndState::Exit()
{
	std::cout << "Restarting" << std::endl;
}

//StateManager
StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::Update()
{
	if (!m_vStates.empty())
		m_vStates.back()->Update();

}

void StateManager::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render();
}

void StateManager::ChangeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	pState->Enter();
	m_vStates.push_back(pState);
}

void StateManager::PushState(State* pState)
{
	pState->Enter();
	m_vStates.push_back(pState);
}

void StateManager::PopState()//Pause to Game
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void StateManager::Clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates() { return m_vStates; }