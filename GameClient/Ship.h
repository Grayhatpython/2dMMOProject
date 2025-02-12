#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship();

public:
	void			UpdateActor() override;
	virtual void	ActorInput() override;

private:
	float	_laserCooldown{ 0.25f };
};