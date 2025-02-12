#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	friend class Grid;

	Tile();

public:
	void					SetTileState(TileState state);
	TileState				GetTileState() const { return _tileState; }
	void					ToggleSelect();
	std::shared_ptr<Tile>	GetParent() const { return _parent.lock(); }

	void					UpdateTexture();

private:
	// For pathfinding
	std::vector<std::weak_ptr<Tile>>	_adjacent;
	std::weak_ptr<Tile>					_parent;

	float f{ 0.0f };
	float g{ 0.0f };
	float h{ 0.0f };

	bool _openSet = false;
	bool _closedSet = false;
	bool _blocked = false;

	TileState				_tileState = TileState::Default;
	bool					_selected = false;
};
