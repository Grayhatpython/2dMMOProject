#include "pch.h"
#include "NetworkManager.h"
#include "ServerInstance.h"
#include "ServerPacketHandler.h"
#include "PacketQueue.h"

void NetworkManager::Initialize()
{
	ServerPacketHandler::Initialize();

	_gameServer = std::make_shared<ServerInstance>();
	_packetQueue = std::make_shared<PacketQueue>();
}

void NetworkManager::Update()
{
	if (_gameServer)
		_gameServer->Update();
}

void NetworkManager::Send(SendBufferRef sendBuffer, ServerType serverType)
{
	if (_gameServer && serverType == ServerType::GameServer)
		_gameServer->Send(sendBuffer);
}

void NetworkManager::Clear()
{
	if (_gameServer)
		_gameServer->Disconnect();

	_gameServer = nullptr;
	_packetQueue = nullptr;
}
