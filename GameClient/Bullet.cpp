#include "pch.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Manager.h"
#include "PlayScene.h"
#include "CircleComponent.h"

Bullet::Bullet()
	: Actor(L"Bullet")
{
}

void Bullet::UpdateActor()
{
	Actor::UpdateActor();

	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	_liveTime -= deltaTime;
	if (_liveTime <= 0.0f)
		// Time limit hit, die
		SetState(ActorState::Dead);
}
