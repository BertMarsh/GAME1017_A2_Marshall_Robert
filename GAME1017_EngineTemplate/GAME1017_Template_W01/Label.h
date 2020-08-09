#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Label.h"

class Label
{
private:
	TTF_Font* m_font;
	SDL_Color m_TColour;
	SDL_FRect m_TextRect;
	SDL_Texture* m_pText;
	char m_string[256];
public:
	Label(std::string key, const float x, const float y, const char* str, const SDL_Color col = { 255, 255, 255, 255 });
	~Label();
	void Render();
	void SetText(const char* str);
	void SetPos(const float x, const float y);
	void SetColor(const SDL_Color& col);
	void UseFont(std::string key);
};

