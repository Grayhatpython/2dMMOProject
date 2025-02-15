#include "pch.h"
#include "ServerSession.h"
#include "Manager.h"
#include "PacketQueue.h"
#include "ServerInstance.h"

ServerSession::~ServerSession()
{
	cout << "~ServerSession" << endl;
}

void  ServerSession::OnConnected()
{
	auto session = std::static_pointer_cast<ServerSession>(shared_from_this());

	Manager::GetNetworkManager()->GetGameServer()->SetServerSession(session);
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	auto session = std::static_pointer_cast<ServerSession>(shared_from_this());

	PacketHeader* packetHeader = reinterpret_cast<PacketHeader*>(buffer);

	const auto& packetQueue = Manager::GetNetworkManager()->GetPacketQueue();
	if (packetQueue)
		packetQueue->Push(session, buffer, len);
}

void  ServerSession::OnSend(int32 len)
{
	//cout << "OnSend Len = " << len << endl;
}


void  ServerSession::OnDisconnected()
{
}