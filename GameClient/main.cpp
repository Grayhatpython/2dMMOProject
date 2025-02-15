#include "pch.h"
#include <iostream>
#include "ThreadManager.h"
#include "Service.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"
#include "Game.h"

#undef main

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
	std::this_thread::sleep_for(3s);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(6610);
	std::cout.imbue(std::locale(""));
	std::wcout.imbue(std::locale(""));

	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Run();
	}

	game.Shutdown();

	system("pause");
	return 0;
}