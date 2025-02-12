#pragma once
#include "Actor.h"

class FollowActor : public Actor
{
public:
	FollowActor();

public:
	void UpdateActor() override;

public:
	void							SetTarget(std::shared_ptr<Actor> target) { _target = target; }
	const std::shared_ptr<Actor>&	GetTarget() { return _target; }

private:
	std::shared_ptr<Actor>	_target;
};
