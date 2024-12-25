#pragma once
#include <unordered_set>
#include "NetServer.h"

class MonitorNetServer : public NetServer
{
public:
	MonitorNetServer();
	BOOL Start();
	virtual BOOL OnConnectionRequest(const SOCKADDR_IN* pSockAddrIn) override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	virtual void OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown() override; // 일반적으로 DB스레드에대한 PQCS를 쏠때 사용할것이다
	virtual void OnResourceCleanAtShutDown() override;
	void SendToAllClient(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp);

	SRWLOCK uMapLock;
	std::unordered_set<ULONGLONG> uMap;
	void OnRelease_IMPL(ULONGLONG id);
	LONG monitorClientNum_ = 0;
};
