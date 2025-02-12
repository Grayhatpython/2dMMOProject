#pragma once
#include "CameraComponent.h"

class FollowCameraComponent : public CameraComponent
{
public:
	FollowCameraComponent();

public:
	virtual void Update() override;

public:
	const Vector2& GetCameraOffset() { return _cameraOffset; }

private:
	Vector2 _cameraOffset = Vector2::Zero;
};
