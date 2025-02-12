#pragma once
#include "SDL/SDL.h"

class Ship;
class Actor;
class SpriteComponent;
class Game
{
public:
	Game();

public:
	bool Initialize();
	void Run();
	void Shutdown();

private:
	void ProcessInput();
	void Update();
	void Redner();

public:
};
