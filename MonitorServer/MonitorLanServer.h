#pragma once
#include "LanServer.h"
#include "ServerInfo.h"
#include "MonitorNetServer.h"
#include "MonitorDbThread.h"
class MonitorLanServer : public Monitorable, public LanServer
{
public:
	MonitorLanServer();
	BOOL Start();
	virtual BOOL OnConnectionRequest(const SOCKADDR_IN* pSockAddrIn) override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	virtual void OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown() override; // ��� ��Ŀ�����带 �����Ű������ �������ϵ��� �����ϸ��, DB�����忡 ���� Ÿ�Ӿƿ� PQCS�� ��ǥ��
	virtual void OnResourceCleanAtShutDown() ;

	// Monitorable Override
	virtual void OnMonitor() override;

	ServerInfo* pSIArr_ = nullptr;
	MonitorNetServer* pNetServer = nullptr;
	LONG loginServerNum_ = 0;
	MonitorDbThread* pDbThread_ = nullptr;
	DBRequestTimer* pDbRequestTimer_ = nullptr;
	MonitoringUpdate* pConsoleMonitor_ = nullptr;
};
