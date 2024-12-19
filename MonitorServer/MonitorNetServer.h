#pragma once
#include <unordered_map>
#include "NetServer.h"

class MonitorNetServer : public NetServer
{
public:
	MonitorNetServer();
	BOOL Start();
	virtual BOOL OnConnectionRequest() override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	void SendToAllClient(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp);

	SRWLOCK uMapLock;
	std::unordered_map<ULONGLONG, NetSession*> uMap;
	void OnRelease_IMPL(ULONGLONG id);
	LONG monitorClientNum_ = 0;
};
