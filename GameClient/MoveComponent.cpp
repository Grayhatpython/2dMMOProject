#include "pch.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Manager.h"

MoveComponent::MoveComponent()
	:Component(ComponentType::Move)
{

}

MoveComponent::MoveComponent(ComponentType type)
	:Component(type)
{
}

void MoveComponent::Update()
{
	auto owner = GetOwner();
	ASSERT_CRASH(owner);

	auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	if (!Math::NearZero(_angularSpeed))
	{
		float rot = owner->GetRotation();
		rot += _angularSpeed * deltaTime;
		owner->SetRotation(rot);
	}

	if (!Math::NearZero(_forwardSpeed))
	{
		Vector2 pos = owner->GetPosition();
		pos += owner->GetForward() * _forwardSpeed * deltaTime;

		// Screen wrapping (for asteroids)
		if (pos.x < 0) { pos.x = 0.f; }
		if (pos.y < 0) { pos.y = 0.f; }
		owner->SetPosition(pos);
	}
}
