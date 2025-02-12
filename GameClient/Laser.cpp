#include "pch.h"
#include "Laser.h"
#include "Manager.h"
#include "CircleComponent.h"
#include "PlayScene.h"
#include "Asteroid.h"
#include "BoxComponent.h"

Laser::Laser()
	: Actor(L"Laser")
{

}

void Laser::UpdateActor()
{
	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	_deathTime -= deltaTime;

	if (_deathTime <= 0.0f)
		SetState(ActorState::Dead);
}

void Laser::OnCollision(std::shared_ptr<Actor> other)
{
	SetState(ActorState::Dead);
}
