#include "pch.h"
#include "Enemy.h"
#include "Grid.h"
#include "Tile.h"
#include "Manager.h"
#include "PlayScene.h"

Enemy::Enemy()
	: Actor(L"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::UpdateActor()
{
	Actor::UpdateActor();

	// Am I near the end tile?
	Vector2 endPosition = Manager::GetSceneManager()->GetCurrentScene()->GetPlayScene()->GetGrid()->GetEndTile()->GetPosition();

	Vector2 diff = GetPosition() - endPosition;
	if (Math::NearZero(diff.Length(), 10.0f))
		SetState(ActorState::Dead);
}
