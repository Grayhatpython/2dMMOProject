#include "pch.h"
#include "Grid.h"
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"
#include "Manager.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "NavComponent.h"
#include "CircleComponent.h"

Grid::Grid()
	: Actor(L"Grid")
{

}

Grid::~Grid()
{

}

void Grid::Initialize()
{
	// 7 rows, 16 columns
	_tiles.resize(_numRows);
	for (size_t i = 0; i < _tiles.size(); i++)
	{
		_tiles[i].resize(_numCols);
	}

	// Create tiles
	for (uint32 i = 0; i < _numRows; i++)
	{
		for (uint32 j = 0; j < _numCols; j++)
		{
			_tiles[i][j] = std::make_shared<Tile>();
			std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();
			_tiles[i][j]->AddComponent(sc);
			_tiles[i][j]->UpdateTexture();
			//Manager::GetRenderManager()->AddSprite(sc);
			//Manager::GetSceneManager()->GetCurrentScene()->AddActor(_tiles[i][j]);
			_tiles[i][j]->SetPosition(Vector2(_tileSize / 2.0f + j * _tileSize, _tileSize / 2.0f + i * _tileSize));
		}
	}

	// Set start/end tiles
	GetStartTile()->SetTileState(TileState::Start);
	GetEndTile()->SetTileState(TileState::Base);

	// Set up adjacency lists
	for (size_t i = 0; i < _numRows; i++)
	{
		for (size_t j = 0; j < _numCols; j++)
		{
			if (i > 0)
			{
				_tiles[i][j]->_adjacent.push_back(_tiles[i - 1][j]);
			}
			if (i < _numRows - 1)
			{
				_tiles[i][j]->_adjacent.push_back(_tiles[i + 1][j]);
			}
			if (j > 0)
			{
				_tiles[i][j]->_adjacent.push_back(_tiles[i][j - 1]);
			}
			if (j < _numCols - 1)
			{
				_tiles[i][j]->_adjacent.push_back(_tiles[i][j + 1]);
			}
		}
	}

	// Find path (in reverse)
	/*FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());

	_nextEnemy = _enemyTime;*/
}

void Grid::ProcessClick(int x, int y)
{
	/*y -= static_cast<int>(_startY - _tileSize / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(_tileSize);
		y /= static_cast<int>(_tileSize);
		if (x >= 0 && x < static_cast<int>(_numCols) && y >= 0 && y < static_cast<int>(_numRows))
			SelectTile(y, x);
	}*/
}

bool Grid::FindPath(std::shared_ptr<Tile> start, std::shared_ptr<Tile> goal)
{
	for (size_t i = 0; i < _numRows; i++)
	{
		for (size_t j = 0; j < _numCols; j++)
		{
			_tiles[i][j]->g = 0.0f;
			_tiles[i][j]->_openSet = false;
			_tiles[i][j]->_closedSet = false;
		}
	}

	std::vector<std::shared_ptr<Tile>> openSet;

	// Set current node to start, and add to closed set
	auto& current = start;
	current->_closedSet = true;

	do
	{
		// Add adjacent nodes to open set
		for (auto& adjacent : current->_adjacent)
		{
			auto neighbor = adjacent.lock();
			if (neighbor->_blocked)
				continue;

			// Only check nodes that aren't in the closed set
			if (neighbor->_closedSet == false)
			{
				if (neighbor->_openSet == false)
				{
					// Not in the open set, so set parent
					neighbor->_parent = current;
					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					// g(x) is the parent's g plus cost of traversing edge
					neighbor->g = current->g + _tileSize;
					neighbor->f = neighbor->g + neighbor->h;
					openSet.push_back(neighbor);
					neighbor->_openSet = true;
				}
				else
				{
					// Compute g(x) cost if current becomes the parent
					float newG = current->g + _tileSize;
					if (newG < neighbor->g)
					{
						// Adopt this node
						neighbor->_parent = current;
						neighbor->g = newG;
						// f(x) changes because g(x) changes
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}

		// If open set is empty, all possible paths are exhausted
		if (openSet.empty())
			break;

		// Find lowest cost node in open set
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[](const std::shared_ptr<Tile>& a, const std::shared_ptr<Tile>& b) {
				return a->f < b->f;
			});

		// Set to current and move from open to closed
		current = *iter;
		openSet.erase(iter);
		current->_openSet = false;
		current->_closedSet = true;
	} while (current != goal);

	// Did we find a path?
	return (current == goal) ? true : false;
}

void Grid::BuildTower()
{
	if (_selectedTile && _selectedTile->_blocked == false)
	{
		_selectedTile->_blocked = true;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			std::shared_ptr<Tower> t = std::make_shared<Tower>();
			t->SetPosition(_selectedTile->GetPosition());

			std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();
			sc->SetTexture("../Common/Assets/Tower.png");
			t->AddComponent(sc);

			std::shared_ptr<MoveComponent> mv = std::make_shared<MoveComponent>();
			t->AddComponent(mv);

			Manager::GetSceneManager()->GetCurrentScene()->AddActor(t);
		}
		else
		{
			// This tower would block the path, so don't allow build
			_selectedTile->_blocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		UpdatePathTiles(GetStartTile());
	}
}

std::shared_ptr<Tile> Grid::GetStartTile()
{
	return _tiles[3][0];
}

std::shared_ptr<Tile> Grid::GetEndTile()
{
	return _tiles[3][15];
}

void Grid::UpdateActor()
{
	//auto deltaTime = Manager::GetTimeManager()->GetDeltaTime();

	//Actor::UpdateActor();

	//// Is it time to spawn a new enemy?
	//_nextEnemy -= deltaTime;
	//if (_nextEnemy <= 0.0f)
	//{
	//	std::shared_ptr<Enemy> e = std::make_shared<Enemy>();
	//	e->SetPosition(GetStartTile()->GetPosition());

	//	std::shared_ptr<NavComponent> nc = std::make_shared<NavComponent>();
	//	std::shared_ptr<CircleComponent> cc = std::make_shared<CircleComponent>();
	//	std::shared_ptr<SpriteComponent> sc = std::make_shared<SpriteComponent>();

	//	e->AddComponent(nc);
	//	e->AddComponent(cc);
	//	e->AddComponent(sc);

	//	nc->SetForwardSpeed(150.0f);
	//	nc->StartPath(GetStartTile());

	//	cc->SetRadius(25.0f);

	//	sc->SetTexture("../Common/Assets/Airplane.png");

	//	//Manager::GetRenderManager()->AddSprite(sc);
	//	Manager::GetSceneManager()->GetCurrentScene()->AddActor(e);

	//	_nextEnemy += _enemyTime;
	//}
}

void Grid::SelectTile(uint32 row, uint32 col)
{
	// Make sure it's a valid selection
	TileState tileState = _tiles[row][col]->GetTileState();
	if (tileState != TileState::Start && tileState != TileState::Base)
	{
		// Deselect previous one
		if (_selectedTile)
			_selectedTile->ToggleSelect();

		_selectedTile = _tiles[row][col];
		_selectedTile->ToggleSelect();
	}
}

void Grid::UpdatePathTiles(std::shared_ptr<Tile> start)
{
	// Reset all tiles to normal (except for start/end)
	for (size_t i = 0; i < _numRows; i++)
	{
		for (size_t j = 0; j < _numCols; j++)
		{
			if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
				_tiles[i][j]->SetTileState(TileState::Default);
		}
	}

	auto tile = start->_parent.lock();
	while (tile != GetEndTile())
	{
		tile->SetTileState(TileState::Path);
		tile = tile->_parent.lock();
	}
}
