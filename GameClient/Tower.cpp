#include "pch.h"
#include "Tower.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Manager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Tower::Tower()
	: Actor(L"Tower")
{

}

void Tower::UpdateActor()
{
	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();
	Actor::UpdateActor();

	_nextAttack -= deltaTime;

	if (_nextAttack <= 0.0f)
	{
		auto e = Manager::GetSceneManager()->GetCurrentScene()->GetPlayScene()->GetNearestEnemy(GetPosition());
		if (e != nullptr)
		{
			std::cout << "tete" << std::endl;
			// Vector from me to enemy
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();
			if (dist < _attackRange)
			{
				// Rotate to face enemy
				SetRotation(Math::Atan2(-dir.y, dir.x));
				// Spawn bullet at tower position facing enemy
				std::shared_ptr<Bullet> b = std::make_shared<Bullet>();
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());

				std::shared_ptr<MoveComponent> mv = std::make_shared<MoveComponent>();
				mv->SetForwardSpeed(400.0f);
				std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();

				std::shared_ptr<CircleComponent> cc = std::make_shared<CircleComponent>();
				cc->SetRadius(5.0f);

				sc->SetTexture("../Common/Assets/Projectile.png");

				b->AddComponent(mv);
				b->AddComponent(cc);
				b->AddComponent(sc);

				//Manager::GetRenderManager()->AddSprite(sc);
				Manager::GetSceneManager()->GetCurrentScene()->AddActor(b);

			}
		}
		_nextAttack += _attackTime;
	}
}
