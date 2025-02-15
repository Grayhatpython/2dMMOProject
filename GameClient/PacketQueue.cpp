#include "pch.h"
#include "PacketQueue.h"
#include "ServerSession.h"

void PacketQueue::Push(ServerSessionRef serverSession, BYTE* buffer, int32 len)
{
	if (serverSession == nullptr || serverSession->IsConnected() == false)
		return;

	auto packetMessage = ObjectPool<PacketMessage>::MakeShared(buffer, len);

	{
		WRITE_LOCK;

		auto findIter = _packetQueue.find(serverSession);
		if (findIter == _packetQueue.end())
		{
			Queue<PacketMessageRef> packetQueue;
			_packetQueue.insert({ serverSession, packetQueue });
		}

		_packetQueue[serverSession].push(packetMessage);
	}
}

void PacketQueue::PopAll(ServerSessionRef serverSession, Vector<std::shared_ptr<PacketMessage>>& packetMessages)
{
	if (serverSession == nullptr || serverSession->IsConnected() == false)
		return;

	{
		WRITE_LOCK;

		auto findIter = _packetQueue.find(serverSession);
		if (findIter != _packetQueue.end())
		{
			while (findIter->second.empty() == false)
			{
				auto& packetMessage = findIter->second.front();
				packetMessages.push_back(packetMessage);
				findIter->second.pop();
			}
		}
	}
}

void PacketQueue::Clear()
{
	//	TODO
	_packetQueue.clear();
}
