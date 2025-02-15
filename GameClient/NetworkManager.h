#pragma once


class NetworkManager
{
public:
	void Initialize();
	void Update();
	void Send(SendBufferRef sendBuffer, ServerType serverType = ServerType::GameServer);

	void Clear();

public:
	const PacketQueueRef&		GetPacketQueue() { return _packetQueue; }
	const ServerInstanceRef&	GetGameServer() { return _gameServer; }

private:
	ServerInstanceRef	_gameServer;
	PacketQueueRef		_packetQueue;
};

