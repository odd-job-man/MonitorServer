#pragma once
#include "LanServer.h"
#include "ServerInfo.h"
class MonitorLanServer : public LanServer
{
public:
	BOOL Start();
	ServerInfo* pSIArr_;
	virtual BOOL OnConnectionRequest() override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
};
