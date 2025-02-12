#include "pch.h"
#include "RenderManager.h"
#include "SpriteComponent.h"
#include "Manager.h"
#include "Scene.h"
#include "Actor.h"
#include "UIScreen.h"
#include "Grid.h"
#include "Tile.h"
#include "PlayScene.h"

#include "FollowActor.h"
#include "FollowCameraComponent.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{
	::SDL_StopTextInput();
	::TTF_Quit();
	::IMG_Quit();
	if (_renderer)
	{
		::SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}
	if (_window)
	{
		::SDL_DestroyWindow(_window);
		_window = nullptr;
	}
	::SDL_Quit();
}

bool RenderManager::Initialize(int32 screenWidth, int32 screenHeight)
{
	if (::SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		::SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow("GameClient", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		::SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		::SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (::IMG_Init(IMG_INIT_PNG) == 0)
	{
		::SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (::TTF_Init() != 0)
	{
		::SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	::SDL_StartTextInput();
	::SDL_RenderClear(_renderer);

	return true;
}

void RenderManager::SetBackBufferColor(const SDL_Color& color)
{
	::SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
	::SDL_RenderClear(_renderer);
}

void RenderManager::Present()
{
	::SDL_RenderPresent(_renderer);
}

void RenderManager::Render()
{
	SDL_SetRenderDrawColor(_renderer, 192, 192, 192, 255);
	SDL_RenderClear(_renderer);

	// Draw all sprite components
	//for (auto& sprite : _sprites)
	//{
	//	if(sprite->GetOwner())
	//		sprite->Render();
	//}

	const auto& currentScene = Manager::GetSceneManager()->GetCurrentScene();
	auto sceneType = currentScene->GetSceneType();
	if (sceneType == SceneType::Play)
	{
		auto playScene = currentScene->GetPlayScene();
		ASSERT_CRASH(playScene);

		const auto& grid = playScene->GetGrid();
		ASSERT_CRASH(grid);

		const auto& tiles = grid->GetTiles();

		const auto& camera = Manager::GetSceneManager()->GetCurrentScene()->GetCamera();

		auto fcc = camera->GetFollowCameraComponent();
		const Vector2& cameraOffset = fcc->GetCameraOffset();

		uint32 width = grid->GetTileSize();
		uint32 height = grid->GetTileSize();

		uint32 startXIndex = static_cast<uint32>(cameraOffset.x / width);
		uint32 startYIndex = static_cast<uint32>(cameraOffset.y / height);

		uint32 rows = _screenHeight / height + 2;
		uint32 columns = _screenWidth / width + 1;

		for (uint32 row = 0; row < rows; row++)
		{
			for (uint32 column = 0; column < columns; column++)
			{
				uint32 calYIndex = row + startYIndex;
				uint32 calXIndex = column + startXIndex;

				if (calYIndex >= grid->GetNumRows())
					calYIndex = grid->GetNumRows() - 1;

				if (calXIndex >= grid->GetNumCols())
					calXIndex = grid->GetNumCols() - 1;

				auto sprite = tiles[calYIndex][calXIndex]->GetSpriteComponent();
				if (sprite)
					sprite->Render();
			}
		}
	}

	const auto& actors = Manager::GetSceneManager()->GetCurrentScene()->GetActors();
	for (const auto& actor : actors)
	{
		auto sc = actor->GetSpriteComponent();
		if (actor->GetState() == ActorState::Active && sc)
			sc->Render();
	}

	const auto& uis = Manager::GetSceneManager()->GetCurrentScene()->GetUis();
	for (const auto& ui : uis)
	{
		if (ui->GetState() == UIState::Active)
			ui->Render();
	}

	SDL_RenderPresent(_renderer);
}

void RenderManager::Clear()
{
	//_sprites.clear();
}

//void RenderManager::AddSprite(std::shared_ptr<SpriteComponent> sprite)
//{
//	// Find the insertion point in the sorted vector
//	// (The first element with a higher draw order than me)
//	int myDrawOrder = sprite->GetDrawOrder();
//	auto iter = _sprites.begin();
//	for (; iter != _sprites.end(); ++iter)
//	{
//		if (myDrawOrder < (*iter)->GetDrawOrder())
//			break;
//	}
//
//	// Inserts element before position of iterator
//	_sprites.insert(iter, sprite);
//}
//
//void RenderManager::RemoveSprite(std::shared_ptr<SpriteComponent> sprite)
//{
//	// (We can't swap because it ruins ordering)
//	auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
//	_sprites.erase(iter);
//}
