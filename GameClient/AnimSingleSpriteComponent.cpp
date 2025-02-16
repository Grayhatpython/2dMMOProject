#include "pch.h"
#include "AnimSingleSpriteComponent.h"
#include "Manager.h"
#include "Actor.h"
#include "Manager.h"
#include "Scene.h"
#include "Texture.h"
#include "FollowActor.h"
#include "FollowCameraComponent.h"

AnimSingleSpriteComponent::AnimSingleSpriteComponent(int32 drawOrder)
	: SpriteComponent(ComponentType::AnimSingleSprite, drawOrder)
{

}

void AnimSingleSpriteComponent::Update()
{
	SpriteComponent::Update();

    auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	auto owner = GetOwner();

	if (owner->GetState() == ActorState::Active)
	{
		_currentFrame += _currentClip->frameTime * deltaTime;

		if (_currentFrame >= _currentClip->frameCount)
		{
			if (_currentClip->loop)
				_currentFrame -= _currentClip->frameCount;
			else
				_currentFrame = _currentClip->frameCount - 1.f;
		}
	}

    //if (_currentClip)
    //{
    //    _currentFrame += _currentClip->frameTime * deltaTime;

    //    if (_currentFrame >= _currentClip->frameCount)
    //    {
    //        if (_currentClip->loop)
    //            _currentFrame = 0.0f; // 루프
    //        else
    //            _currentFrame = _currentClip->frameCount - 1; // 마지막 프레임 유지
    //    }
    //}
}

void AnimSingleSpriteComponent::Render()
{
	if (_texture)
	{
		auto owner = GetOwner();
		//	TODO
		ASSERT_CRASH(owner);

		const auto currentAnimClip = GetCurrentAnimClip();

		SDL_Rect srcRect;
		SDL_Rect dstRect;

		auto width = currentAnimClip->width;
		auto height = currentAnimClip->height;
		auto startX = currentAnimClip->startX;
		auto startY = currentAnimClip->startY;
		auto scale = owner->GetScale();

		srcRect.w = static_cast<int32>(width * scale);
		srcRect.h = static_cast<int32>(height * scale);
		srcRect.x = (startX * width) + (static_cast<int32>(_currentFrame) * width);
		srcRect.y = 2 + startY * height;

		Vector2 screenPosition = owner->GetPosition();

		//	TEMP
		const auto& camera = Manager::GetSceneManager()->GetCurrentScene()->GetCamera();

		if (camera)
		{
			auto fcc = camera->GetFollowCameraComponent();
			const Vector2& cameraOffset = fcc->GetCameraOffset();
			screenPosition -= cameraOffset;

			auto screenWidth = Manager::GetRenderManager()->GetScreenWidth();
			auto screenHeight = Manager::GetRenderManager()->GetScreenHeight();

			if (owner->GetName().compare(L"Tile") != 0)
			{
				if (screenPosition.x < 0 || screenPosition.x > screenWidth || screenPosition.y < 0 || screenPosition.y > screenHeight)
					return;
			}
		}

		dstRect.w = static_cast<int32>(width * scale);
		dstRect.h = static_cast<int32>(height * scale);
		dstRect.x = static_cast<int32>(screenPosition.x - dstRect.w / 2);
		dstRect.y = static_cast<int32>(screenPosition.y - dstRect.h / 2);

		auto renderer = Manager::GetRenderManager()->GetRenderer();
		::SDL_RenderCopyEx(renderer,
			_texture->_sdlTexture,
			&srcRect,
			&dstRect,
			-Math::ToDegrees(owner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void AnimSingleSpriteComponent::AddAnimation(const std::wstring& name, int32 startX, int32 startY, int32 width, int32 height, int32 frameCount, float frameTime, bool loop)
{
	_animations[name] = { name, startX, startY, width, height, frameCount, frameTime, loop };
}

void AnimSingleSpriteComponent::PlayAnimation(const std::wstring& name)
{
	auto findIter = _animations.find(name);
	if (findIter == _animations.end())
		return;

	_currentClip = &findIter->second;
	_currentFrame = 0.0f;
}

