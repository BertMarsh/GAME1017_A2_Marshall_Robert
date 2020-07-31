#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>
class TextureManager
{
public:
	static void Init();
	static void RegisterTexture(const char* path, const std::string key);
	static SDL_Texture* GetTexture(const char* path);
	static void Quit();
private:
	static std::vector<std::string, SDL_Texture*> v_Textures;
private:
	TextureManager();

};

