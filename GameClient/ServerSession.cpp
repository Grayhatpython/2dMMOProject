#include "pch.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"

ServerSession::~ServerSession()
{
	cout << "~ServerSession" << endl;
}

void  ServerSession::OnConnected()
{
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	auto session = GetPacketSessionRef();
	ServerPacketHandler::PacketProcessing(session, buffer, len);
}

void  ServerSession::OnSend(int32 len)
{
	//cout << "OnSend Len = " << len << endl;
}


void  ServerSession::OnDisconnected()
{
}