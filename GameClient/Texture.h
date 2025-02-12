#pragma once
#include <SDL/SDL.h>

class Texture
{
public:
	friend class SpriteComponent;

	~Texture();

public:
	bool Load(const std::string& fileName);
	void Clear();
	void CreateTextureFromSurface(SDL_Surface* surface);

public:

	SDL_Texture*	GetSDLTexture() const { return _sdlTexture; }
	void			SetSDLTexture(SDL_Texture* texture) { _sdlTexture = texture; }

	int32			GetTextureWidth() const { return _textureWidth; }
	void			SetTextureWidth(int32 width) { _textureWidth = width; }

	int32			GetTextureHeight() const { return _textureHeight; }
	void			SetTextureHeight(int32 height) { _textureHeight = height; }

private:
	SDL_Texture*	_sdlTexture = nullptr;
	int32			_textureWidth{ 0 };
	int32			_textureHeight{ 0 };
};

