#pragma once
#include "LanServer.h"
#include "MonitorNetServer.h"
#include "MonitorDbThread.h"
class MonitorLanServer : public Monitorable, public LanServer
{
public:
	MonitorLanServer(const WCHAR* pIP, const USHORT port, const DWORD IocpWorkerThreadNum, const DWORD CuncurrentThreadNum, const BOOL bZeroCopy,
		const LONG maxSession, const BOOL bActivateTimeOut, const LONG userTimeOut, const DWORD timeOutCheckInterval, const DWORD DBWriteInterval, const  DWORD DBWriteTimeOut);
	MonitorLanServer();
	BOOL Start(MonitorNetServer* pNetServer);
	virtual BOOL OnConnectionRequest(const WCHAR* pIP, const USHORT port) override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	virtual void OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown() override; // ��� ��Ŀ�����带 �����Ű������ �������ϵ��� �����ϸ��, DB�����忡 ���� Ÿ�Ӿƿ� PQCS�� ��ǥ��
	virtual void OnResourceCleanAtShutDown();

	// Monitorable Override
	virtual void OnMonitor() override;

	MonitorNetServer* pNetServer_ = nullptr;
	LONG loginServerNum_ = 0;
	MonitorDbThread* pDbThread_ = nullptr;
	DBRequestTimer* pDbRequestTimer_ = nullptr;
	MonitoringUpdate* pConsoleMonitor_ = nullptr;
};
