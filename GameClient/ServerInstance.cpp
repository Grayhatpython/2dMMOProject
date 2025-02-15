#include "pch.h"
#include "ServerInstance.h"
#include "ServerSession.h"
#include "Manager.h"
#include "PacketQueue.h"
#include "ServerPacketHandler.h"
#include <Service.h>
#include <ThreadManager.h>

void ServerInstance::Send(SendBufferRef sendBuffer)
{
	if (_serverSession)
		_serverSession->Send(sendBuffer);
}

void ServerInstance::Connect(const NetAddress& address, JobRef connectionCallback)
{
	_service = MakeShared<ClientService>(
		address,
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(_service);
	
	_jobQueue.Push(connectionCallback);

	ASSERT_CRASH(_service->Start());

	for (int32 i = 0; i < 2; i++)
	{
		//	Ref Count No Add
		GThreadManager->Launch([service = _service]()
			{
				//LEndTickCount = ::GetTickCount64() + PROCESS_TICK;

				//	I/O ( JobQueue Push MultiThread )
				//	Game Logic ( JobQueue Execute -> One Thread )
				if (service)
					service->GetIocpCore()->Dispatch(10);

				//	Global Reserve Jobs Push JobQueue
				//ThreadManager::DistributeReserveJobs();

				//	Game Logic
				//ThreadManager::DoGlobalJobQueueExecute();

			}, L"Worker Thread");
	}
}

void ServerInstance::Disconnect()
{
	if (_serverSession && _serverSession->IsConnected())
		_serverSession->Disconnect(L"연결 해제");

	_serverSession = nullptr;

	if(_service)
		_service->CloseService();
	
	_service = nullptr;
	_jobQueue.Clear();
}

void ServerInstance::Update()
{
	if (_serverSession == nullptr)
		return;

	ExecuteJob();

	Vector<PacketMessageRef> packetMessages;
	Manager::GetNetworkManager()->GetPacketQueue()->PopAll(_serverSession, packetMessages);

	const auto packetMessageCount = static_cast<int32>(packetMessages.size());
	for (int32 i = 0; i < packetMessageCount; i++)
	{
		auto packetSession = std::static_pointer_cast<PacketSession>(_serverSession);
		ServerPacketHandler::PacketProcessing(packetSession, packetMessages[i]->buffer, packetMessages[i]->len);
	}
}

void ServerInstance::PushJob(JobRef job)
{
	_jobQueue.Push(job);
}

void ServerInstance::ExecuteJob()
{
	Vector<JobRef> jobs;
	_jobQueue.PopAll(jobs);

	const auto jobCount = static_cast<int32>(jobs.size());
	for (int32 i = 0; i < jobCount; i++)
		jobs[i]->Execute();
}

bool ServerInstance::IsConnected()
{
	if (_serverSession == nullptr)
		return false;
	
	return _serverSession->IsConnected();
}
