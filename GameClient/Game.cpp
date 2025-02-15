#include "pch.h"
#include "Game.h"
#include "Manager.h"
#include "TimeManager.h"
#include "PlayScene.h"
#include "TitleScene.h"

Game::Game()
{

}

bool Game::Initialize()
{
	Manager::GetInstance()->Initialize();
	Manager::GetRenderManager()->Initialize(1280, 720);

	std::shared_ptr<TitleScene> scene = std::make_shared<TitleScene>();
	Manager::GetSceneManager()->SetCurrentScene(scene);

	return true;
}

void Game::Run()
{
	while (true)
	{
		auto gameState = Manager::GetSceneManager()->GetCurrentScene()->GetState();

		if (gameState == GameState::Quit)
			break;

		ProcessInput();
		Update();
		Redner();
	}
}

void Game::ProcessInput()
{
	Manager::GetSceneManager()->ProcessInput();
}

void Game::Update()
{
	Manager::GetNetworkManager()->Update();
	Manager::GetTimeManager()->Update();
	Manager::GetSceneManager()->Update();
	Manager::GetPhysicsManager()->Update();
}

void Game::Redner()
{
	Manager::GetRenderManager()->Render();
}

void Game::Shutdown()
{
	Manager::GetInstance()->Clear();

	GSendBufferManager->Close();

	GCoreGlobal->Clear();
	delete GCoreGlobal;
	GCoreGlobal = nullptr;

	google::protobuf::ShutdownProtobufLibrary();
}

