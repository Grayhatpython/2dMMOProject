#pragma once
#include "Actor.h"

class Laser : public Actor
{
public:
	Laser();

public:
	virtual void UpdateActor() override;
	virtual void OnCollision(std::shared_ptr<Actor> other) override;

private:
	float _deathTime{ 1.0f };
};

