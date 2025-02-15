#pragma once

struct PacketMessage
{
	PacketMessage()
	{

	}

	PacketMessage(BYTE* buffer, int32 len)
		: buffer(buffer), len(len)
	{

	}

	BYTE* buffer = nullptr;
	int32 len = 0;
};


class PacketQueue
{
public:
	void Push(ServerSessionRef serverSession, BYTE* buffer, int32 len);
	void PopAll(ServerSessionRef serverSession, Vector<std::shared_ptr<PacketMessage>>& packetMessages);
	void Clear();

private:
	USE_LOCK;
	HashMap<ServerSessionRef, Queue<PacketMessageRef>> _packetQueue;
};

