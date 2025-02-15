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

	//	� ��������.. EX) GameServer, AuthServer ...
	ServerSessionRef	_serverSession;
	//	���� ��ü
	ClientServiceRef	_service;
	//	Callback ó��
	LockQueue<JobRef>	_jobQueue;
};

