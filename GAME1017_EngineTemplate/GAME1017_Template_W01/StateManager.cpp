#include "StateManager.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::Update()
{
	if (!m_vStates.empty)
		m_vStates.back()->Update();
	
}

void StateManager::Render()
{
	if (!m_vStates.empty)
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