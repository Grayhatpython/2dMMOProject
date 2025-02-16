#pragma once
#include "SpriteComponent.h"

struct AnimationClip
{
	std::wstring name;
	int32 startX = 0;
	int32 startY = 0;
	int32 width = 0;
	int32 height = 0;
	int32 frameCount = 0;
	float frameTime = 0.0f;
	bool loop = true;
};

class Texture;
class AnimSingleSpriteComponent : public SpriteComponent
{
public:
	AnimSingleSpriteComponent(int32 drawOrder = 100);
	void Update() override;

public:
	virtual void		Render() override;

public:
	void				AddAnimation(const std::wstring& name, int32 startX, int32 startY, int32 width, int32 height, int32 frameCount, float frameTime, bool loop = true);
	void				PlayAnimation(const std::wstring& name);

public:
	const AnimationClip* GetCurrentAnimClip() { return _currentClip; }

private:
	std::unordered_map<std::wstring, AnimationClip>	_animations;
	AnimationClip*									_currentClip = nullptr;

	float	_currentFrame{ 0.0f };
};
