#include "pch.h"
#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent()
	: Component(ComponentType::Circle)
{
}

float CircleComponent::GetRadius() const
{
	auto owner = GetOwner();
	ASSERT_CRASH(owner);

	return owner->GetScale() * _radius;
}

const Vector2& CircleComponent::GetCenter() const
{
	auto owner = GetOwner();
	ASSERT_CRASH(owner);

	return owner->GetPosition();
}
