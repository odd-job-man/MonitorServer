#include <WinSock2.h>
#include <unordered_map>
#include "CommonProtocol.h"
#include "MonitorLanServer.h"
#include "Timer.h"

LONG LoginArr[SERVERNUM::NUM];


BOOL MonitorLanServer::Start()
{
	pSIArr_ = new ServerInfo[maxSession_];
	for (DWORD i = 0; i < IOCP_WORKER_THREAD_NUM_; ++i)
		ResumeThread(hIOCPWorkerThreadArr_[i]);

	ResumeThread(hAcceptThread_);
	Timer::Start();
	return TRUE;
}

BOOL MonitorLanServer::OnConnectionRequest()
{
	return TRUE;
}

void* MonitorLanServer::OnAccept(ULONGLONG id)
{
	return nullptr;
}

void MonitorLanServer::OnRelease(ULONGLONG id)
{
	int idx = LanSession::GET_SESSION_INDEX(id);
	ServerInfo* pSI = pSIArr_ + idx;
	InterlockedDecrement(LoginArr + pSI->num_);
}

void MonitorLanServer::OnRecv(ULONGLONG id, Packet* pPacket)
{
	WORD type;
	(*pPacket) >> type;
	switch ((en_PACKET_TYPE)type)
	{
	case en_PACKET_SS_MONITOR_LOGIN:
	{
		int serverNo;
		(*pPacket) >> serverNo;
		if (serverNo >= SERVERNUM::NUM)
		{
			LOG(L"ERROR", SYSTEM, CONSOLE, L"SERVERNUM %d, Invalid Server Login", serverNo);
			LOG(L"ERROR", SYSTEM, TEXTFILE, L"SERVERNUM %d, Invalid Server Login", serverNo);
			Disconnect(id);
			break;
		}

		if (InterlockedIncrement(LoginArr + serverNo) > 1)
		{
			InterlockedDecrement(LoginArr + serverNo);
			LOG(L"ERROR", SYSTEM, CONSOLE, L"SERVERNUM %d, Duplicated Login", serverNo);
			LOG(L"ERROR", SYSTEM, TEXTFILE, L"SERVERNUM %d, Duplicated Login", serverNo);
			Disconnect(id);
			break;
		}

		int idx = LanSession::GET_SESSION_INDEX(id);
		ServerInfo* pSI = pSIArr_ + idx;
		pSI->num_ = (SERVERNUM)serverNo;
		break;
	}
	case en_PACKET_SS_MONITOR_DATA_UPDATE:
	{
		BYTE dataType;
		int dataValue;
		int timeStamp;
		(*pPacket) >> dataType >> dataValue >> timeStamp;
		break;
	}
	default:
		break;
	}

	PACKET_FREE(pPacket);
}

void MonitorLanServer::OnError(ULONGLONG id, int errorType, Packet* pRcvdPacket)
{
}

void MonitorLanServer::OnPost(void* order)
{
}
