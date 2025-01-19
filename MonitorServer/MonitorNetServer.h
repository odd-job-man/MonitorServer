#pragma once
#include <unordered_set>
#include "NetServer.h"

class MonitorNetServer : public NetServer
{
public:
	MonitorNetServer(const WCHAR* pIP, const USHORT port, const DWORD IocpWorkerThreadNum, const DWORD CuncurrentThreadNum,
		const BOOL bZeroCopy, const LONG maxSession, const LONG maxUser, const BYTE packetCode, const BYTE packetFixedKey, const BOOL bActivateTimeOut, const LONG userTimeOut, const DWORD timeOutCheckInterval);
	MonitorNetServer();
	BOOL Start();
	virtual BOOL OnConnectionRequest(const SOCKADDR_IN* pSockAddrIn) override;
	virtual void* OnAccept(ULONGLONG id) override;
	virtual void OnRelease(ULONGLONG id) override;
	virtual void OnRecv(ULONGLONG id, Packet* pPacket) override;
	virtual void OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket) override;
	virtual void OnPost(void* order) override;
	virtual void OnLastTaskBeforeAllWorkerThreadEndBeforeShutDown() override; // �Ϲ������� DB�����忡���� PQCS�� �� ����Ұ��̴�
	virtual void OnResourceCleanAtShutDown() override;
	void SendToAllClient(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp);

	SRWLOCK uMapLock;
	std::unordered_set<ULONGLONG> uMap;
	void OnRelease_IMPL(ULONGLONG id);
	LONG monitorClientNum_ = 0;
};
