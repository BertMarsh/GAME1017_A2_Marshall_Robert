#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include<SDL_ttf.h>

class FontManager
{
public:
	static void RegisterFont(const char* path, const std::string key, const int size);
	static void SetSize(const char* path, const std::string key, const int size);
	static TTF_Font* GetFont(const std::string key);
	static void Quit();
private:
	static std::map<std::string, TTF_Font*> s_fonts;
private:
	FontManager(){}
};

