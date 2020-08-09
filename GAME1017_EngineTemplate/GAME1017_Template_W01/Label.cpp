#include <cstring>

#include "Label.h"
#include "Engine.h"
#include "FontManager.h"

Label::Label(std::string key, const float x, const float y, const char* str, const SDL_Color col)
	:m_TColour(col)
{
	m_font = FontManager::GetFont(key);
	SetPos(x, y);
	SetText(str);
}

Label::~Label()
{
	SDL_DestroyTexture(m_pText);
}

void Label::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), m_pText, 0, &m_TextRect);
}

void Label::SetText(const char* str)
{
	strcpy_s(m_string, 256, str);
	SDL_Surface* fontsurf = TTF_RenderText_Solid(m_font, m_string, m_TColour);
	SDL_DestroyTexture(m_pText);
	m_pText = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), fontsurf);
	m_TextRect = { m_TextRect.x, m_TextRect.y, (float)fontsurf->w , (float)fontsurf->h };
	SDL_FreeSurface(fontsurf);
}

void Label::SetPos(const float x, const float y)
{
	m_TextRect = { x, y, m_TextRect.w, m_TextRect.h };
}

void Label::SetColor(const SDL_Color& col)
{
	m_TColour = col;
	SetText(m_string);
}

void Label::UseFont(std::string key)
{
	SetText(m_string);
}
