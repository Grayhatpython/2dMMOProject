#include "pch.h"
#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent()
	: MoveComponent(ComponentType::Nav)
{
}

void NavComponent::Update()
{
	auto owner = GetOwner();
	auto nextNode = _nextNode.lock();
	if (nextNode)
	{
		// If we're at the next node, advance along path
		Vector2 diff = owner->GetPosition() - nextNode->GetPosition();
		if (Math::NearZero(diff.Length(), 2.0f))
		{
			nextNode = nextNode->GetParent();
			TurnTo(nextNode->GetPosition());
		}
	}

	MoveComponent::Update();
}

void NavComponent::StartPath(std::shared_ptr<Tile> start)
{
	_nextNode = start->GetParent();
	TurnTo(_nextNode.lock()->GetPosition());
}

void NavComponent::TurnTo(const Vector2& pos)
{
	auto owner = GetOwner();
	// Vector from me to pos
	Vector2 dir = pos - owner->GetPosition();
	// New angle is just atan2 of this dir vector
	// (Negate y because +y is down on screen)
	float angle = Math::Atan2(-dir.y, dir.x);
	owner->SetRotation(angle);
}
