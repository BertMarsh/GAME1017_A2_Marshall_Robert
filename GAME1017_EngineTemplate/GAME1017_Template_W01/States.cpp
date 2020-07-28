#include "States.h"
#include "Engine.h"


#include <iostream>


void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume()
{

}

//TitleState

TitleState::TitleState() {}
void TitleState::Enter()
{

}

void TitleState::Update()
{

}

void TitleState::Render()
{

}

void TitleState::Exit()
{

}

//GameState

GameState::GameState() {}

void GameState::Enter()
{

}

void GameState::Update()
{

}

void GameState::Render()
{

}

void GameState::Resume()
{

}

void GameState::Exit()
{

}

//PauseState

PauseState::PauseState() {}

void PauseState::Enter()
{

}

void PauseState::Update()
{

}

void PauseState::Render()
{

}

void PauseState::Exit()
{

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
}

void EndState::Render()
{
}

void EndState::Exit()
{
}
