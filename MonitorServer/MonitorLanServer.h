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
	virtual BOOL OnConnectionRequest() override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;

	// Monitorable Override
	virtual void OnMonitor() override;

	ServerInfo* pSIArr_;
	MonitorNetServer* pNetServer;
	LONG loginServerNum_ = 0;
	MonitorDbThread* pDbThread_;
	DBRequestTimer* pDbRequestTimer_;
};
