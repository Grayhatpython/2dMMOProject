#include "pch.h"
#include "Asteroid.h"

Asteroid::Asteroid()
	: Actor(L"Asteroid")
{

}

void Asteroid::OnCollision(std::shared_ptr<Actor> other)
{
	SetState(ActorState::Dead);
}
