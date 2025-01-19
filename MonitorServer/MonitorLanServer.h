#pragma once
#include "LanServer.h"
#include "MonitorNetServer.h"
#include "MonitorDbThread.h"
class MonitorLanServer : public Monitorable, public LanServer
{
public:
	MonitorLanServer();
	BOOL Start(MonitorNetServer* pNetServer);
	virtual BOOL OnConnectionRequest(const WCHAR* pIP, const USHORT port) override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	virtual void OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown() override; // 모든 워커스레드를 종료시키기전에 쏴야할일들을 정의하면됨, DB스레드에 대한 타임아웃 PQCS가 대표적
	virtual void OnResourceCleanAtShutDown();

	// Monitorable Override
	virtual void OnMonitor() override;

	MonitorNetServer* pNetServer_ = nullptr;
	LONG loginServerNum_ = 0;
	MonitorDbThread* pDbThread_ = nullptr;
	DBRequestTimer* pDbRequestTimer_ = nullptr;
	MonitoringUpdate* pConsoleMonitor_ = nullptr;
	LanServerTimeOut* pLanTimeOut_ = nullptr;
};
