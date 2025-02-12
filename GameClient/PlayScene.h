#include "Scene.h"

class Grid;
class Enemy;
class Asteroid;
class PlayScene : public Scene
{
public:
	PlayScene();
	virtual ~PlayScene();

public:
	//	TEMP
	virtual void	Initialize() override;
	virtual void	ProcessInput() override;
	virtual void	HandleKeyPress() override;
	virtual void	Update() override;
	virtual void	Clear() override;

	virtual void	OnAddActor(std::shared_ptr<Actor> actor) override;

public:
	//	TEMP
	std::shared_ptr<Enemy>							GetNearestEnemy(const Vector2& position);
	const std::vector<std::shared_ptr<Enemy>>&		GetEnemies() { return _enemies; }
	const std::vector<std::shared_ptr<Asteroid>>&	GetAsteroids() { return _asteroids; }
	const std::shared_ptr<Grid>&					GetGrid() { return _grid; }

private:
	//	TEMP
	std::shared_ptr<Grid>					_grid;
	std::vector<std::shared_ptr<Enemy>>		_enemies;
	std::vector<std::shared_ptr<Asteroid>>	_asteroids;
};
