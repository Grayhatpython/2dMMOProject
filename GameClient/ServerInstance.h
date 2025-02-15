#pragma once

class ServerSession;
class ServerInstance
{
public:
	void Send(SendBufferRef sendBuffer);
	void Connect(const NetAddress& address, JobRef connectionCallback);
	void Disconnect();
	void Update();

public:
	void PushJob(JobRef job);
	void ExecuteJob();

public:
	bool IsConnected();
	void SetServerSession(ServerSessionRef serverSession) { _serverSession = serverSession; }

private:

	//	어떤 서버인지.. EX) GameServer, AuthServer ...
	ServerSessionRef	_serverSession;
	//	연결 매체
	ClientServiceRef	_service;
	//	Callback 처리
	LockQueue<JobRef>	_jobQueue;
};

