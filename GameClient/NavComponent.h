#pragma once
#include "MoveComponent.h"

class Tile;
class NavComponent : public MoveComponent
{
public:
	// Lower update order to update first
	NavComponent();

public:
	void Update() override;
	void StartPath(std::shared_ptr<Tile> start);
	void TurnTo(const Vector2& pos);

private:
	std::weak_ptr<Tile>		_nextNode;
};
