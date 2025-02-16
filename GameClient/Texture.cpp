#include "pch.h"
#include "Texture.h"
#include "SDL/SDL_image.h"
#include "Manager.h"

Texture::~Texture()
{
	Clear();
}

bool Texture::Load(const std::string& fileName)
{
	SDL_Surface* surf = ::IMG_Load(fileName.c_str());
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName.c_str());
		return false;
	}

	// Create texture from surface
	auto renderer = Manager::GetRenderManager()->GetRenderer();
	::SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 128, 128));
	_sdlTexture = ::SDL_CreateTextureFromSurface(renderer, surf);

	if (_sdlTexture == nullptr)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
		return false;
	}

	::SDL_QueryTexture(_sdlTexture, nullptr, nullptr, &_textureWidth, &_textureHeight);
	::SDL_FreeSurface(surf);

	return true;		
}

void Texture::Clear()
{
	if (_sdlTexture)
		::SDL_DestroyTexture(_sdlTexture);
}

void Texture::CreateTextureFromSurface(SDL_Surface* surface)
{
	auto renderer = Manager::GetRenderManager()->GetRenderer();
	_sdlTexture = ::SDL_CreateTextureFromSurface(renderer, surface);

	if (_sdlTexture == nullptr)
	{
		::SDL_Log("Failed to convert surface to texture");
		return;
	}

	::SDL_QueryTexture(_sdlTexture, nullptr, nullptr, &_textureWidth, &_textureHeight);
}
