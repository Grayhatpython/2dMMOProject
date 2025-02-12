#pragma once
#include "SpriteComponent.h"

class Texture;
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(int32 drawOrder = 100);
	void Update() override;

public:
	void	SetAnimTextures(const std::vector<std::shared_ptr<Texture>>& textures);

	float	GetAnimFPS() const { return _animFPS; }
	void	SetAnimFPS(float fps) { _animFPS = fps; }

private:
	std::vector<std::shared_ptr<Texture>>	_animTexture;
	float									_currentFrame{ 0.0f };
	float									_animFPS{ 24.0f };
};
