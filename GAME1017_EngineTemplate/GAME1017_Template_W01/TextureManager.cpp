#include "TextureManager.h"
#include "Engine.h"
#include <iostream>

//void TextureManager::Init()
//{
//	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
//		std::cout << "Image init success!" << std::endl;
//	else
//		std::cout << "Image init failed :/ : ERROR -  " << IMG_GetError() << std::endl;
//}
//
//void TextureManager::RegisterTexture(const char* path, const std::string key)
//{
//	SDL_Texture* temp = IMG_LoadTexture(Engine::Instance().GetRenderer(), path);
//	if (temp == nullptr)
//		std::cout << "Could not load texture: ERROR - " << IMG_GetError << std::endl;
//	else
//		v_Textures.emplace(key, temp);
//}
//
//SDL_Texture* TextureManager::GetTexture(const char* path) {return v_Textures }
//
//void TextureManager::Quit()
//{
//	for (auto const& i : v_Textures)
//	{
//		SDL_DestroyTexture(v_Textures)
//	}
//	v_Textures.clear();
//}
//
//std::vector<std::string, SDL_Texture*> TextureManager::v_Textures;