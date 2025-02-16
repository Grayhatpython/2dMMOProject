#pragma once
#include <SDL/SDL.h>

class SpriteComponent;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();

public:
	bool Initialize(int32 screenWidth, int32 screenHeight);
	void SetBackBufferColor(const SDL_Color& color);
	void Present();

public:
	void Render();
	void Clear();

	//void AddSprite(std::shared_ptr<SpriteComponent> sprite);
	//void RemoveSprite(std::shared_ptr<SpriteComponent> sprite);

private:
	void GridRender();

public:

	SDL_Renderer*	GetRenderer() { return _renderer; }

	void			SetScreenWidth(int32 width) { _screenWidth = width; }
	void			SetScreenHeight(int32 height) { _screenHeight = height; }
	int32			GetScreenWidth() { return _screenWidth; }
	int32			GetScreenHeight() { return _screenHeight; }

	Vector2			GetScreenCenter() { return Vector2(static_cast<float>(_screenWidth / 2), static_cast<float>(_screenHeight / 2)); }
	const Vector2&	GetMapSize() { return _mapSize; }

private:
	SDL_Window*		_window = nullptr;
	SDL_Renderer*	_renderer = nullptr;
	SDL_Color		_backBufferColor{};

	int32			_screenWidth = 0;
	int32			_screenHeight = 0;

	//	TEMP
	Vector2			_mapSize{ 2560.f, 1440.f };
};
