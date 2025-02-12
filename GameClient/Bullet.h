#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet();
	void UpdateActor() override;

private:
	float _liveTime{ 1.0f };
};
