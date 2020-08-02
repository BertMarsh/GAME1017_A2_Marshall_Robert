#include "EventManager.h"
#include "Engine.h"

#include <iostream>
#include <cstring>


void EventManager::Init()
{
	s_keysCurr = SDL_GetKeyboardState(&s_numkeys);
	s_keysLast = new Uint8(s_numkeys);
	std::memcpy(s_keysLast, s_keysCurr, s_numkeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousepos.x, &s_mousepos.y);
	s_mouseLast = s_mouseCurr;
	std::cout << "EventM init done" << std::endl;
}

void EventManager::HandleEvents()
{
	SDL_Event event;

	std::memcpy(s_keysLast, s_keysCurr, s_numkeys);
	s_mouseLast = s_mouseCurr;
	s_LastKeyDown = s_LastKeyUp = -1;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		case SDL_KEYUP:
			s_LastKeyUp = event.key.keysym.sym;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				Engine::Instance().Running() = false;
			break;
		}
	}
	s_keysCurr = SDL_GetKeyboardState(&s_numkeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousepos.x, &s_mousepos.y);
}

bool EventManager::KeyHeld(SDL_Scancode c)
{
	if (s_keysCurr != nullptr)
	{
		if (s_keysCurr[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool EventManager::KeyPressed(SDL_Scancode c)
{
	return (s_keysCurr[c] > s_keysLast[c]);
}

bool EventManager::KeyReleased(SDL_Scancode c)
{
	return (s_keysCurr[c] < s_keysLast[c]);
}

int EventManager::LastKeyDown()
{
	return s_LastKeyDown;
}

int EventManager::LastKeyUp()
{
	return s_LastKeyUp;
}

bool EventManager::MouseHeld(const int b)
{
	if (b >= 1 && b <= 3)
		return (s_mouseCurr & SDL_BUTTON(b));
	else
		return false;
}

bool EventManager::MousePressed(const int b)
{
	return ((s_mouseCurr & SDL_BUTTON(b)) > (s_mouseLast & SDL_BUTTON(b)));
}

bool EventManager::MouseReleased(const int b)
{
	return ((s_mouseCurr & SDL_BUTTON(b)) < (s_mouseLast & SDL_BUTTON(b)));
}

SDL_Point& EventManager::GetMousePos()
{
	return s_mousepos;
}

void EventManager::Quit()
{
	delete s_keysLast;
}

const Uint8* EventManager::s_keysCurr = nullptr;
Uint8* EventManager::s_keysLast;
int EventManager::s_numkeys;

int EventManager::s_LastKeyDown;
int EventManager::s_LastKeyUp;
SDL_Point EventManager::s_mousepos = { 0,0 };
Uint32 EventManager::s_mouseCurr;
Uint32 EventManager::s_mouseLast;

