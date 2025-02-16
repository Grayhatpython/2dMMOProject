#include "pch.h"
#include "AnimMultipleSpriteComponent.h"
#include "Manager.h"
#include "TimeManager.h"

AnimMultipleSpriteComponent::AnimMultipleSpriteComponent(int32 drawOrder)
	: SpriteComponent(ComponentType::AnimMultipleSprite, drawOrder)
{

}

void AnimMultipleSpriteComponent::Update()
{
	SpriteComponent::Update();

	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	if (_animTexture.size() > 0)
	{
		_currentFrame += _animFPS * deltaTime;

		while (_currentFrame >= _animTexture.size())
			_currentFrame -= _animTexture.size();

		// Set the current texture
		SetTexture(_animTexture[static_cast<int>(_currentFrame)]);
	}
}

void AnimMultipleSpriteComponent::SetAnimTextures(const std::vector<std::shared_ptr<Texture>>& textures)
{
	_animTexture = textures;
	if (_animTexture.size() > 0)
	{
		_currentFrame = 0.0f;
		SetTexture(_animTexture[0]);
	}
}
