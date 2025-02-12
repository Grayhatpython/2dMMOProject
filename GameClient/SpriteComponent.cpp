#include "pch.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Manager.h"
#include "Texture.h"
#include "Scene.h"
#include "FollowActor.h"
#include "FollowCameraComponent.h"


SpriteComponent::SpriteComponent(int32 drawOrder)
	: Component(ComponentType::Sprite), _drawOrder(drawOrder)
{
}

SpriteComponent::SpriteComponent(ComponentType type, int32 drawOrder)
	: Component(type), _drawOrder(drawOrder)
{
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Render()
{
	if (_texture)
	{
		auto owner = GetOwner();
		//	TODO
		ASSERT_CRASH(owner);

		SDL_Rect r;

		auto width = _texture->GetTextureWidth();
		auto height = _texture->GetTextureHeight();
		auto scale = owner->GetScale();

		r.w = static_cast<int32>(width * scale);
		r.h = static_cast<int32>(height * scale);

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

		r.x = static_cast<int32>(screenPosition.x - r.w / 2);
		r.y = static_cast<int32>(screenPosition.y - r.h / 2);

		auto renderer = Manager::GetRenderManager()->GetRenderer();
		::SDL_RenderCopyEx(renderer,
			_texture->_sdlTexture,
			nullptr,
			&r,
			-Math::ToDegrees(owner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	auto texture = Manager::GetAssetManager()->GetTexture(filename);
	ASSERT_CRASH(texture);

	SetTexture(texture);
}
