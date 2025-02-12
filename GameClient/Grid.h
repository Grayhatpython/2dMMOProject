#pragma once
#include "Actor.h"

class Tile;
class Grid : public Actor
{
public:
	Grid();
	virtual ~Grid();

	virtual void Initialize() override;
	virtual void UpdateActor() override;

	void ProcessClick(int x, int y);
	bool FindPath(std::shared_ptr<Tile> start, std::shared_ptr<Tile> goal);

	void BuildTower();

public:
	std::shared_ptr<Tile> GetStartTile();
	std::shared_ptr<Tile> GetEndTile();

	const std::vector<std::vector<std::shared_ptr<Tile>>>& GetTiles() { return _tiles; }
	
	const float GetTileSize() const { return _tileSize; }
	const uint32 GetNumRows() const { return _numRows; }
	const uint32 GetNumCols() const { return _numCols; }

private:
	void SelectTile(uint32 row, uint32  col);
	void UpdatePathTiles(std::shared_ptr<Tile> start);

	std::shared_ptr<Tile> _selectedTile;
	std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;

	float _nextEnemy{ 0.0f };

	const uint32 _numRows = 25;
	const uint32 _numCols = 25;
	const float _tileSize = 64.0f;
	const float _enemyTime = 1.5f;
};
