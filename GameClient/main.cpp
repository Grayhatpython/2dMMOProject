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

	/*
	//_CrtSetBreakAlloc(128725023);
	std::this_thread::sleep_for(1000ms);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::wcout.imbue(std::locale("korean"));

	ServerPacketHandler::Initialize();

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession >, // TODO : SessionManager µî
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}


	GThreadManager->Join();

	google::protobuf::ShutdownProtobufLibrary();
	*/

	GSendBufferManager->Close();

	GCoreGlobal->Clear();
	delete GCoreGlobal;
	GCoreGlobal = nullptr;

	google::protobuf::ShutdownProtobufLibrary();

	system("pause");
	return 0;
}