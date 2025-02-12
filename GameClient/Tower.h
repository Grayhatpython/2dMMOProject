#pragma once
#include "Actor.h"

class Tower : public Actor
{
public:
	Tower();

public:
	virtual void UpdateActor() override;

private:
	float			_nextAttack{ 2.5f };

	const float		_attackTime = 2.5f;
	const float		_attackRange = 100.0f;
};
