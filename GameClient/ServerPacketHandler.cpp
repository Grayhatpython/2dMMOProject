#include "pch.h"
#include "ServerPacketHandler.h"
#include "ServerSession.h"


PacketProcessingFunction GPacketPacketProcessingFunction[UINT16_MAX];

bool Packet_Processing_Function_Undefined(std::shared_ptr<PacketSession>& session, BYTE* buffer, int32 len)
{
	return true;
}

bool S_CONNECTED_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_CONNECTED& packet)
{
	auto serverSession = static_pointer_cast<ServerSession>(session);

	return true;
}

bool S_ENTERGAME_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_ENTERGAME& packet)
{
	return true;
}

bool S_LEAVEGAME_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_LEAVEGAME& packet)
{
	return true;
}

bool S_SPAWN_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_SPAWN& packet)
{
	return true;
}

bool S_DESPAWN_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_DESPAWN& packet)
{
	return true;
}

bool S_MOVE_Packet_Processing_Function(std::shared_ptr<PacketSession>& session, Protocol::S_MOVE& packet)
{
	return true;
}