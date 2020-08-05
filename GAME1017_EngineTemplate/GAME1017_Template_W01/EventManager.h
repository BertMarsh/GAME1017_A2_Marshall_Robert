#pragma once
#include <SDL.h>

class EventManager 
{
public:
	static void Init();
	static void HandleEvents();
	static bool KeyHeld(const SDL_Scancode c);
	static bool KeyPressed(const SDL_Scancode c);
	static bool KeyReleased(const SDL_Scancode c);
	static int LastKeyDown();
	static int LastKeyUp();
	static bool MouseHeld(const int b);
	static bool MousePressed(const int b);
	static bool MouseReleased(const int b);
	static SDL_Point& GetMousePos();
	static void Quit();
private:
	//KeyBoard
	static const Uint8* s_KeysCurr;
	static Uint8* s_KeysLast;
	static int s_NumKeys;
	//Mouse
	static int s_LastKeyDown;
	static int s_LastKeyUp;
	static SDL_Point s_MousePos;
	static Uint32 s_MouseCurr;
	static Uint32 s_MouseLast;
private:
	EventManager() {}

};