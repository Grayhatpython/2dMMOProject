#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

public:
	void UpdateActor() override;

private:

};


