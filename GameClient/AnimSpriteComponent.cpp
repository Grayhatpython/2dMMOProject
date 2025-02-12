#include "pch.h"
#include "AnimSpriteComponent.h"
#include "Manager.h"
#include "TimeManager.h"

AnimSpriteComponent::AnimSpriteComponent(int32 drawOrder)
	: SpriteComponent(ComponentType::AnimSprite, drawOrder)
{

}

void AnimSpriteComponent::Update()
{
	SpriteComponent::Update();

	if (_animTexture.size() > 0)
	{
		_currentFrame += _animFPS * Manager::GetTimeManager()->GetDeltaTime();

		while (_currentFrame >= _animTexture.size())
			_currentFrame -= _animTexture.size();

		// Set the current texture
		SetTexture(_animTexture[static_cast<int>(_currentFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<std::shared_ptr<Texture>>& textures)
{
	_animTexture = textures;
	if (_animTexture.size() > 0)
	{
		_currentFrame = 0.0f;
		SetTexture(_animTexture[0]);
	}
}
