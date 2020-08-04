#include "State.h"
#include "Engine.h"
#include "StateManager.h"


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>

#define BGSCROLL 1
#define MGSCROLL 2
#define FGSCROLL 3
#define PSPEED 7
#define JUMPSTR 10.0
#define GRAVITY 10.0

#define WIDTH 1024
#define HEIGHT 768


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
	//Background
	m_pBGText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Background.png");
	BgArray[0] = { {0,0,1024,768}, {0,0,1024,768} };
	BgArray[1] = { {0,0,1024,768}, {1024,0,1024,768} };
	//Foreground
	m_pFGText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Platform.png");
	FgArray[0] = { {0,0,1024,257}, {0,600,1024,257} };
	FgArray[1] = { {0,0,1024,257}, {1024,600,1024,257} };
	//Pilars
	m_pPText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Pillars.png");
	PArray[0] = { {0,0,525,511}, {0,0,550,600} };
	PArray[1] = { {0,0,525,511}, {275,0,550,600} };
	PArray[2] = { {0,0,525,511}, {550,0,550,600} };
	PArray[3] = { {0,0,525,511}, {825,0,550,600} };
	PArray[4] = { {0,0,525,511}, {1100,0,550,600} };
	//Player Running
	m_pSprText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Player.png");
	m_pPlayer = new Player({0,0,128,128}, {25,475,128,128});
	//Player Jumping
	//m_pPlayer = new Player({}, {});
}

void GameState::Update()
{
	////ChangeStates
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		Engine::Instance().GetStateManager().ChangeState(new PauseState());
	
	//Scrolling
	for (int i = 0; i < 2; i++)
		BgArray[i].GetDstP()->x -= BGSCROLL;
	if (BgArray[1].GetDstP()->x <= 0)
	{
		BgArray[0].GetDstP()->x = 0;
		BgArray[1].GetDstP()->x = 1024;
	}
	//Foreground
	for (int i = 0; i < 2; i++)
		FgArray[i].GetDstP()->x -= FGSCROLL;
	if (FgArray[1].GetDstP()->x <= 0)
	{
		FgArray[0].GetDstP()->x = 0;
		FgArray[1].GetDstP()->x = 1024;
	}
	//Pillars
	for (int i = 0; i < 5; i++)
		PArray[i].GetDstP()->x -= MGSCROLL;
	if (PArray[1].GetDstP()->x <= 0)
	{
		PArray[0].GetDstP()->x = 0;
		PArray[1].GetDstP()->x = 275;
		PArray[2].GetDstP()->x = 550;
		PArray[3].GetDstP()->x = 825;
		PArray[4].GetDstP()->x = 1100;
	}
	//Player
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A) && m_pPlayer->GetDstP()->x > m_pPlayer->GetDstP()->h)
	{
		m_pPlayer->GetDstP()->x -= PSPEED;
		m_pPlayer->Animate();
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_D) && m_pPlayer->GetDstP()->x < WIDTH / 2)
	{
		m_pPlayer->GetDstP()->x += PSPEED;
		m_pPlayer->Animate();
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE) && m_pPlayer->GetDstP()->y > m_pPlayer->GetDstP()->h)
	{
		m_pPlayer->GetDstP()->y -= JUMPSTR;
		m_pPlayer->Animate();
	}

}

void GameState::Render()
{
	std::cout << "Rendering Game." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	////Background
	for(int i =0;i<2;i++)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pBGText, BgArray[i].GetSrcP(), BgArray[i].GetDstP());
	//Foreground
	for (int i = 0; i < 2; i++)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pFGText, FgArray[i].GetSrcP(), FgArray[i].GetDstP());
	//Pillars
	for (int i = 0; i < 5; i++)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pPText, PArray[i].GetSrcP(), PArray[i].GetDstP());
	//Player
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pSprText, m_pPlayer->GetSrcP(), m_pPlayer->GetDstP());
	
	
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

