#include "pch.h"
#include "Ship.h"
#include <SDL/SDL.h>
#include "Manager.h"
#include "TimeManager.h"
#include "Laser.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "BoxComponent.h"

Ship::Ship()
	: Actor(L"Ship")
{
}

void Ship::UpdateActor()
{
	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	_laserCooldown -= deltaTime;
}

void Ship::ActorInput()
{
	const auto& state = Manager::GetInputManager()->GetState();

	if (_laserCooldown <= 0.0f && state.keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		// Create a laser and set its position/rotation to mine
		std::shared_ptr<Laser> laser = std::make_shared<Laser>();
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();
		laser->AddComponent(sc);

		sc->SetTexture("../Common/Assets/Laser.png");

		std::shared_ptr<MoveComponent> mc = std::make_shared<MoveComponent>();
		mc->SetForwardSpeed(800.0f);
		laser->AddComponent(mc);

		std::shared_ptr<CircleComponent> cc = std::make_shared<CircleComponent>();
		cc->SetRadius(11.0f);
		laser->AddComponent(cc);

		std::shared_ptr<BoxComponent> bc = std::make_shared<BoxComponent>();
		laser->AddComponent(bc);

		bc->SetCollisionLayer(CollisionLayer::Laser);
		bc->SetCollisionMask(static_cast<int32>(CollisionLayer::Asteroid));

		Manager::GetSceneManager()->GetCurrentScene()->AddActor(laser);

		// Reset laser cooldown (quarter second)
		_laserCooldown = 0.25f;
	}
}
