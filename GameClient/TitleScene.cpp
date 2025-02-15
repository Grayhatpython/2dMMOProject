#include "pch.h"
#include "TitleScene.h"
#include "Manager.h"
#include "ServerInstance.h"
#include "ServerPacketHandler.h"

TitleScene::TitleScene()
	: Scene(SceneType::Title)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	//Scene::Initialize();

	_state = TitleSceneState::ConnectingToServer;

	//	UI ¼³Á¤.. ±ÍÂú;;

	//	TODO
	const auto& gameServer = Manager::GetNetworkManager()->GetGameServer();
	NetAddress netAddress(L"127.0.0.1", 7777 );
	if (gameServer)
	{
		std::weak_ptr<TitleScene> weakTitleScene = std::static_pointer_cast<TitleScene>(shared_from_this());
		auto onConnectionCallback = [weakTitleScene]()
			{
				if (auto titleScene = weakTitleScene.lock()) // °´Ã¼°¡ À¯È¿ÇÑ °æ¿ì¸¸ ½ÇÇà
				{
					const auto& gameServer = Manager::GetNetworkManager()->GetGameServer();

					if (gameServer->IsConnected())
						titleScene->OnConnected();
					else
						titleScene->OnConnectFailed();
				}
			};

		auto job = ObjectPool<Job>::MakeShared(onConnectionCallback);

		gameServer->Connect(netAddress, job);
	}
}

void TitleScene::ProcessInput()
{
	Scene::ProcessInput();
}

void TitleScene::HandleKeyPress()
{

}

void TitleScene::Update()
{
	Scene::Update();
}

void TitleScene::Clear()
{
	Scene::Clear();
}

void TitleScene::OnConnected()
{
	_state = TitleSceneState::ConnectedToServer;

	Protocol::C_TEST testPacket;
	testPacket.set_temp(1);

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(testPacket);
	Manager::GetNetworkManager()->Send(sendBuffer);
}

void TitleScene::OnConnectFailed()
{
	_state = TitleSceneState::FailedToConnectToServer;
}
