#include <SDL.h>

#include "Button.h"
#include "Engine.h"
#include "EventManager.h"

Button::Button(SDL_Rect s, SDL_Rect d, SDL_Renderer* r, SDL_Texture* t)
	:Sprite(s, d, r, t), m_state(STATE_UP) {}

bool MouseCollision()
{
	const int mx = EventManager::GetMousePos().x;
	const int my = EventManager::GetMousePos().y;
	return (mx < (m_rDst.x + m_rDst.w) && mx>m_rDst.x 
		&& my<(m_rDst.y + m_rDst.h) && my > m_rDst.y);
}

int Button::Update()
{
	bool col = MouseCollision();
	switch(m_state)
	{
	case STATE_UP:
		if (col)
			m_state = STATE_OVER;
		break;
	case STATE_OVER:
		if (!col)
			m_state = STATE_UP;
		else if (col && EventManager::MousePressed(1))
			m_state = STATE_DOWN;
		break;
	case STATE_DOWN:
		if (EventManager::MouseReleased(1))
		{
			if (col)
			{
				m_state = STATE_OVER;
				Execute();
				return 1;
			}
			else m_state = STATE_UP;
		}
		break;
	}
	return 0;
}

void Button::Render(){}

PlayButton::PlayButton(SDL_Rect src, SDL_Rect dst, SDL_Renderer* r, SDL_Texture* t)
	:Button (src,dst,r,t) {}

void PlayButton::Execute()
{
	StateManager::ChangeState(new GameState);
}