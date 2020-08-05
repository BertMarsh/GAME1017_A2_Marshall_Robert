#include <cstring>
#include <iostream>

#include "EventManager.h"
#include "Engine.h"

void EventManager::Init()
{
	s_KeysCurr = SDL_GetKeyboardState(&s_NumKeys);
	s_KeysLast = new Uint8[s_NumKeys];
	std::memcpy(s_KeysLast, s_KeysCurr, s_NumKeys);
	s_MouseCurr = SDL_GetMouseState(&s_MousePos.x, &s_MousePos.y);
	s_MouseLast = s_MouseCurr;
	std::cout << "EventManager Init done" << std::endl;
}

void EventManager::HandleEvents()
{
	SDL_Event event;

	std::memcpy(s_KeysLast, s_KeysCurr, s_NumKeys);
	s_MouseLast = s_MouseCurr;
	s_LastKeyDown = s_LastKeyUp = -1;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Engine::Instance().Running() = false;
			break;
		case SDL_KEYDOWN:
			s_LastKeyDown = event.key.keysym.sym;
			break;
		case SDL_KEYUP:
			s_LastKeyUp = event.key.keysym.sym;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				Engine::Instance().Running() = false;
			break;
		}
	}
	s_KeysCurr = SDL_GetKeyboardState(&s_NumKeys);
	s_MouseCurr = SDL_GetMouseState(&s_MousePos.x, &s_MousePos.y);
}

bool EventManager::KeyHeld(const SDL_Scancode c)
{
	if (s_KeysCurr != nullptr)
	{
		if (s_KeysCurr[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool EventManager::KeyPressed(const SDL_Scancode c)
{
	return (s_KeysCurr[c] > s_KeysLast[c]);
}

bool EventManager::KeyReleased(const SDL_Scancode c)
{
	return (s_KeysCurr[c] < s_KeysLast[c]);
}

int EventManager::LastKeyDown() { return s_LastKeyDown; }
int EventManager::LastKeyUp() { return s_LastKeyUp; }

bool EventManager::MouseHeld(const int b)
{
	if (b >= 1 && b <= 3)
		return (s_MouseCurr & SDL_BUTTON(b));
	else
		return false;
}

bool EventManager::MousePressed(const int b)
{
	return ((s_MouseCurr & SDL_BUTTON(b)) > (s_MouseLast & SDL_BUTTON(b)));
}

bool EventManager::MouseReleased(const int b)
{
	return ((s_MouseCurr & SDL_BUTTON(b)) < (s_MouseLast & SDL_BUTTON(b)));
}

SDL_Point& EventManager::GetMousePos()
{
	return s_MousePos;
}

void EventManager::Quit()
{
	delete s_KeysLast;
}

const Uint8* EventManager::s_KeysCurr = nullptr;
Uint8* EventManager::s_KeysLast;
int EventManager::s_NumKeys;

int EventManager::s_LastKeyDown;
int EventManager::s_LastKeyUp;
SDL_Point EventManager::s_MousePos = { 0,0 };
Uint32 EventManager::s_MouseCurr;
Uint32 EventManager::s_MouseLast;