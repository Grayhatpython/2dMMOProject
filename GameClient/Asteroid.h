#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid();

public:
	virtual void OnCollision(std::shared_ptr<Actor> other) override;

};

