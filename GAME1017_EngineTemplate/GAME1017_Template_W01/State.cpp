#include "State.h"
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"
#include "Obstacles.h"
#include "StateManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "Label.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#define BGSCROLL 1
#define MGSCROLL 2
#define FGSCROLL 3
#define PSPEED 7
//#define JUMPSTR 10.0
//#define GRAVITY 10.0

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
	m_BText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/StartButton.png");
	m_PlayB = { {0,0,372,195}, {315,400,372,195}, m_tRend, m_tText};
	m_pPLabel = new Label("Robert Marshall", 200, 300, "Consolas", { 140, 40, 0, 255 });
	m_pPLabel = new Label("101287661", 220, 300, "Consolas", { 140, 40, 0, 255 });
	m_pPLabel = new Label("Gil Dobrovinsky", 240, 300, "Consolas", { 140, 40, 0, 255 });
	m_pPLabel = new Label("101304972", 260, 300, "Consolas", { 140, 40, 0, 255 });
	m_pPLabel = new Label("Press 'G' to start.", 350, 300, "Consolas", { 140, 40, 0, 255 });
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_G))
		Engine::Instance().GetStateManager().ChangeState(new GameState());
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 149, 50, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), m_BText, m_PlayB.GetSrcP(), m_PlayB.GetDstP());
	State::Render();
	m_pPLabel->Render();
}	



void TitleState::Exit()
{
	std::cout << "Exiting Title." << std::endl;
}

//GameState
GameState::GameState()  {}

void GameState::Enter()
{
	std::cout << "Entering Game." << std::endl;
	//All Sprites
	//Background
	m_pBGText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Background.png");
	BgArray[0] = { {0,0,1024,768}, {0,0,1024,768}, m_pRend, m_pText};
	BgArray[1] = { {0,0,1024,768}, {1024,0,1024,768},  m_pRend, m_pText };
	//Midground
	m_pFGText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Platform.png");
	FgArray[0] = { {0,0,1024,257}, {0,600,1024,257},  m_pRend, m_pText };
	FgArray[1] = { {0,0,1024,257}, {1024,600,1024,257},  m_pRend, m_pText };
	//Foreground
	m_pPText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Pillars.png");
	PArray[0] = { {0,0,525,511}, {0,0,550,600}, m_pRend, m_pText };
	PArray[1] = { {0,0,525,511}, {275,0,550,600}, m_pRend, m_pText };
	PArray[2] = { {0,0,525,511}, {550,0,550,600}, m_pRend, m_pText };
	PArray[3] = { {0,0,525,511}, {825,0,550,600}, m_pRend, m_pText };
	PArray[4] = { {0,0,525,511}, {1100,0,550,600}, m_pRend, m_pText };
	//Player Running
	m_pSprText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Player.png");
	m_pPlayer = new Player({ 0,0,128,128 }, { 500.0f,475.0f,128.0f,128.0f }, m_pRend, m_pText);
	
	
	//Obstacles
	m_pOText = IMG_LoadTexture(Engine::Instance().GetRenderer(), "../Assets/Obstacles.png");
	m_pObstacles = new Obstacles({0, 132, 130, 130}, {500, 400, 130, 130}, m_pRend, m_pText);
	//Platforms
	m_pPlatforms[0] = new SDL_FRect({ -100.0f, 700.0f,1224.0f,100.0f });
}

void GameState::Update()
{
	//ChangeStates
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		Engine::Instance().GetStateManager().ChangeState(new PauseState());
	
	//Scrolling
	//Background
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
	///Player
	//if (Engine::Instance().KeyDown(SDL_SCANCODE_A) && m_pPlayer->GetDstP()->x > m_pPlayer->GetDstP()->h)
	//{
	//	m_pPlayer->GetDstP()->x -= PSPEED;
	//	m_pPlayer->Animate();
	//}
	//else if (Engine::Instance().KeyDown(SDL_SCANCODE_D) && m_pPlayer->GetDstP()->x < WIDTH / 2)
	//{
	//	m_pPlayer->GetDstP()->x += PSPEED;
	//	m_pPlayer->Animate();
	//}
	//else if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE) && m_pPlayer->GetDstP()->y > m_pPlayer->GetDstP()->h)
	//{
	//	m_pPlayer->GetDstP()->y -= JUMPSTR;
	//	m_pPlayer->Animate();
	//}
	//else if (Engine::Instance().KeyDown(SDL_SCANCODE_S) && m_pPlayer->GetDstP()->y > m_pPlayer->GetDstP()->h)
	//{
	//	m_pPlayer = new Player({ 128,128,128,128 }, { 0,0,128,128});
	//	m_pPlayer->Animate();
	//}
	//else if (Engine::Instance().KeyDown(SDL_SCANCODE_W) && m_pPlayer->GetDstP()->y > m_pPlayer->GetDstP()->h)
	//{
	//	m_pPlayer = new Player({ 0,0,128,128 }, { 25,475,128,128 });
	//}

	if (EventManager::KeyHeld(SDL_SCANCODE_D))
	{
		m_pPlayer->SetAccelX(1.0);
		m_pPlayer->Animate();
	}
	else if (EventManager::KeyHeld(SDL_SCANCODE_A))
	{
		m_pPlayer->SetAccelX(-1.0);
		m_pPlayer->Animate();
	}
	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE) && m_pPlayer->isGrounded())
	{
		m_pPlayer->SetAccelY(-JUMPSTR);
		m_pPlayer->SetGrounded(false);
		m_pPlayer->Animate();
	}

	if (m_pPlayer->GetDstP()->x < -51.0) m_pPlayer->SetX(1024.0);
	else if (m_pPlayer->GetDstP()->x > 1024.0)m_pPlayer->SetX(-50.0);
	m_pPlayer->Update();
	CheckCollision();

	//Obstacles
	//Movement
	/*for (int i = 0; i < (int)m_vObstacles.size(); i++)
	{
		m_vObstacles[i]->Update();
		if (m_vObstacles[i]->GetDstP()->x < -50)
		{
			delete m_vObstacles[i];
			m_vObstacles[i] = nullptr;
		}*/
	//}
	//Obstacle Spawns
	//if (m_iOSpawn++ == m_iOSpawnMax)
	//{
	//	//m_vObstacles.push_back(new Obstacles({ 132,130, 100, 100 }, { m_Dst.x,m_Dst.y - 28,14,14 }, -10));
	//}
}

void GameState::CheckCollision()
{ 
	for (int i = 0; i < NUMPLATFORMS; i++)
	{
		if (CollisionManager::AABBCheck(*m_pPlayer->GetDstP(), *m_pPlatforms[i]))
		{
			if (m_pPlayer->GetDstP()->y + m_pPlayer->GetDstP()->h - (float)m_pPlayer->GetVelY() <= m_pPlatforms[i]->y)
			{//Top of platform
				m_pPlayer->SetGrounded(true);
				m_pPlayer->StopY();
				m_pPlayer->SetY(m_pPlatforms[i]->y - m_pPlayer->GetDstP()->h);
			}
			else if (m_pPlayer->GetDstP()->y - (float)m_pPlayer->GetVelY() >= m_pPlatforms[i]->y + m_pPlatforms[i]->h)
			{//Bottom of platform
				m_pPlayer->StopY();
				m_pPlayer->SetY(m_pPlatforms[i]->y + m_pPlatforms[i]->h);
			}
			else if (m_pPlayer->GetDstP()->x + m_pPlayer->GetDstP()->w - m_pPlayer->GetVelX() <= m_pPlatforms[i]->x)
			{//Left
				m_pPlayer->StopX();
				m_pPlayer->SetX(m_pPlatforms[i]->x - m_pPlayer->GetDstP()->w);
			}
			else if (m_pPlayer->GetDstP()->x - (float)m_pPlayer->GetVelX() >= m_pPlatforms[i]->x + m_pPlatforms[i]->w);
			{//Right
				m_pPlayer->StopX();
				m_pPlayer->SetX(m_pPlatforms[i]->x + m_pPlatforms[i]->w);
			}
		}
	}
}

void GameState::Render()
{
	std::cout << "Rendering Game." << std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//Background
	for(int i =0;i<2;i++)
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pBGText, BgArray[i].GetSrcP(), BgArray[i].GetDstP());
	//Foreground
	for (int i = 0; i < 2; i++)
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pFGText, FgArray[i].GetSrcP(), FgArray[i].GetDstP());
	//Pillars
	for (int i = 0; i < 5; i++)
		SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pPText, PArray[i].GetSrcP(), PArray[i].GetDstP());
	//Player
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pSprText, m_pPlayer->GetSrcP(), m_pPlayer->GetDstP());
	
	
	
	//Obstacles
	/*SDL_RenderCopyExF(Engine::Instance().GetRenderer(), m_pOText, m_pObstacles->GetSrcP(), m_pObstacles->GetDstP(), m_pObstacles->GetAngle(), &m_pivot, SDL_FLIP_NONE);*/
	//Platforms
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0,0, 0, 10);
	for (int i = 0; i < NUMPLATFORMS; i++)
		SDL_RenderFillRectF(Engine::Instance().GetRenderer(), m_pPlatforms[i]);
	
	if (dynamic_cast<GameState*>(Engine::Instance().GetStateManager().GetStates().back()))
		State::Render();
}

void GameState::Resume()
{

}

void GameState::Exit()
{
	std::cout << "Exiting Game." << std::endl;
	delete m_pPlayer;
	for (int i = 0; i < NUMPLATFORMS; i++)
		delete m_pPlatforms[i];
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

