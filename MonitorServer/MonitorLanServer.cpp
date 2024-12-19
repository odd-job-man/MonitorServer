#include <WinSock2.h>
#include <unordered_map>
#include "CommonProtocol.h"
#include "MonitorLanServer.h"
#include "Timer.h"
#include "MyJob.h"
#include "ChatData.h"
#include "EchoData.h"
#include "LoginData.h"
#include "ServerCommonData.h"

ChatData g_chatData;
EchoData g_echoData;
LoginData g_loginData;
ServerCommonData g_common;

LONG LoginArr[SERVERNUM::NUM];

#define PROCESS_QUERY_IMPL(Server,elem,dataValue) do{\
	EnterCriticalSection(&Server.cs);\
	Server.elem.total_ += dataValue;\
	Server.elem.min_ = min(Server.elem.min_,dataValue);\
	Server.elem.max_ = max(Server.elem.min_,dataValue);\
	LeaveCriticalSection(&Server.cs);\
}while (0)\


__forceinline void ProcessQueryData(BYTE dataType, int dataValue, int timeStamp)
{
	en_PACKET_SS_MONITOR_DATA_UPDATE_TYPE type = (en_PACKET_SS_MONITOR_DATA_UPDATE_TYPE)dataType;
	switch (type)
	{
	case dfMONITOR_DATA_TYPE_LOGIN_SERVER_RUN:
		break;
	case dfMONITOR_DATA_TYPE_LOGIN_SERVER_CPU:
	{
		PROCESS_QUERY_IMPL(g_loginData, cpuTime_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_LOGIN_SERVER_MEM:
	{
		PROCESS_QUERY_IMPL(g_loginData, memoryAvailableByte_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_LOGIN_SESSION:
	{
		PROCESS_QUERY_IMPL(g_loginData, sessionCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_LOGIN_AUTH_TPS:
	{
		PROCESS_QUERY_IMPL(g_loginData, loginProcessTps_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_LOGIN_PACKET_POOL:
	{
		PROCESS_QUERY_IMPL(g_loginData,packetPoolAlloced_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_SERVER_RUN:
		break;
	case dfMONITOR_DATA_TYPE_GAME_SERVER_CPU:
	{
		PROCESS_QUERY_IMPL(g_echoData, cpuTime_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_SERVER_MEM:
	{
		PROCESS_QUERY_IMPL(g_echoData, memAvailableByte_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_SESSION:
	{
		PROCESS_QUERY_IMPL(g_echoData, sessionCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_AUTH_PLAYER:
	{
		PROCESS_QUERY_IMPL(g_echoData, authCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_GAME_PLAYER:
	{
		PROCESS_QUERY_IMPL(g_echoData, gameCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_ACCEPT_TPS:
	{
		PROCESS_QUERY_IMPL(g_echoData, acceptTps_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_PACKET_RECV_TPS:
	{
		PROCESS_QUERY_IMPL(g_echoData, recvTPS_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_PACKET_SEND_TPS:
	{
		PROCESS_QUERY_IMPL(g_echoData, sendTPS_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_DB_WRITE_TPS:
		break;
	case dfMONITOR_DATA_TYPE_GAME_DB_WRITE_MSG:
		break;
	case dfMONITOR_DATA_TYPE_GAME_AUTH_THREAD_FPS:
	{
		PROCESS_QUERY_IMPL(g_echoData, authFPS_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_GAME_THREAD_FPS:
	{
		PROCESS_QUERY_IMPL(g_echoData, gameFPS_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_GAME_PACKET_POOL:
	{
		PROCESS_QUERY_IMPL(g_echoData, packetPoolAlloced_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_SERVER_RUN:
		break;
	case dfMONITOR_DATA_TYPE_CHAT_SERVER_CPU:
	{
		PROCESS_QUERY_IMPL(g_chatData, cpuTime_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_SERVER_MEM:
	{
		PROCESS_QUERY_IMPL(g_chatData, memAvailableByte_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_SESSION:
	{
		PROCESS_QUERY_IMPL(g_chatData, sessionCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_PLAYER:
	{
		PROCESS_QUERY_IMPL(g_chatData, playerCnt_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_UPDATE_TPS:
	{
		PROCESS_QUERY_IMPL(g_chatData, updateTps_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_PACKET_POOL:
	{
		PROCESS_QUERY_IMPL(g_chatData, packetPoolAlloced_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_CHAT_UPDATEMSG_POOL:
	{
		PROCESS_QUERY_IMPL(g_chatData, updateTps_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL:
	{
		PROCESS_QUERY_IMPL(g_chatData, updateTps_, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY:
	{
		PROCESS_QUERY_IMPL(g_common, NonPagedPoolAvaliableBytes, dataValue);
		break;
	}
	case dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV:
		break;
	case dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND:
		break;
	case dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY:
	{
		PROCESS_QUERY_IMPL(g_common, memAvailable, dataValue);
		break;
	}
	default:
		__debugbreak();
		break;
	}
}


MonitorLanServer::MonitorLanServer()
	:LanServer{ L"MonitorLanConfig.txt" }
{
}

BOOL MonitorLanServer::Start()
{
	pSIArr_ = new ServerInfo[maxSession_];
	MonitoringUpdate* pMU = new MonitoringUpdate{ hcp_,1000,3 };
	pMU->RegisterMonitor(static_cast<const Monitorable*>(this));

	for (DWORD i = 0; i < IOCP_WORKER_THREAD_NUM_; ++i)
		ResumeThread(hIOCPWorkerThreadArr_[i]);

	ResumeThread(hAcceptThread_);

	pNetServer = new MonitorNetServer;
	pNetServer->Start();

	Timer::Reigster_UPDATE(pMU);
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
	switch ((SERVERNUM)(pSI->num_))
	{
	case CHAT:
	{
		EnterCriticalSection(&g_chatData.cs);
		g_chatData.onoff_ = false;
		LeaveCriticalSection(&g_chatData.cs);
		break;
	}
	case LOGIN:
	{
		EnterCriticalSection(&g_loginData.cs);
		g_loginData.onoff_ = false;
		LeaveCriticalSection(&g_loginData.cs);
		break;
	}
	case GAME:
	{
		EnterCriticalSection(&g_echoData.cs);
		g_echoData.onoff_ = false;
		LeaveCriticalSection(&g_echoData.cs);
		break;
	}
	default:
		__debugbreak();
		break;
	}
	InterlockedDecrement(LoginArr + pSI->num_);
	InterlockedDecrement(&loginServerNum_);
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
		InterlockedIncrement(&loginServerNum_);
		switch ((SERVERNUM)serverNo)
		{
		case CHAT:
		{
			EnterCriticalSection(&g_chatData.cs);
			g_chatData.onoff_ = true;
			LeaveCriticalSection(&g_chatData.cs);
			break;
		}
		case LOGIN:
		{
			EnterCriticalSection(&g_loginData.cs);
			g_loginData.onoff_ = true;
			LeaveCriticalSection(&g_loginData.cs);
			break;
		}
		case GAME:
		{
			EnterCriticalSection(&g_echoData.cs);
			g_echoData.onoff_ = true;
			LeaveCriticalSection(&g_echoData.cs);
			break;
		}
		default:
			__debugbreak();
			break;
		}
		break;
	}
	case en_PACKET_SS_MONITOR_DATA_UPDATE:
	{
		BYTE serverNo;
		BYTE dataType;
		int dataValue;
		int timeStamp;
		(*pPacket) >> serverNo >> dataType >> dataValue >> timeStamp;
		int idx = LanSession::GET_SESSION_INDEX(id);
		ServerInfo* pSI = pSIArr_ + idx;
		pNetServer->SendToAllClient(pSI->num_, dataType, dataValue, timeStamp);
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

void MonitorLanServer::OnMonitor()
{
	FILETIME ftCreationTime, ftExitTime, ftKernelTime, ftUsertTime;
	FILETIME ftCurTime;
	GetProcessTimes(GetCurrentProcess(), &ftCreationTime, &ftExitTime, &ftKernelTime, &ftUsertTime);
	GetSystemTimeAsFileTime(&ftCurTime);

	ULARGE_INTEGER start, now;
	start.LowPart = ftCreationTime.dwLowDateTime;
	start.HighPart = ftCreationTime.dwHighDateTime;
	now.LowPart = ftCurTime.dwLowDateTime;
	now.HighPart = ftCurTime.dwHighDateTime;


	ULONGLONG ullElapsedSecond = (now.QuadPart - start.QuadPart) / 10000 / 1000;

	ULONGLONG temp = ullElapsedSecond;

	ULONGLONG ullElapsedMin = ullElapsedSecond / 60;
	ullElapsedSecond %= 60;

	ULONGLONG ullElapsedHour = ullElapsedMin / 60;
	ullElapsedMin %= 60;

	ULONGLONG ullElapsedDay = ullElapsedHour / 24;
	ullElapsedHour %= 24;

	LONG64 recvTPS = InterlockedExchange64(&recvTPS_, 0);
	LONG sendTPS = InterlockedExchange(&pNetServer->sendTPS_, 0);
	

	printf(
		"Elapsed Time : %02lluD-%02lluH-%02lluMin-%02lluSec\n"
		"LanSession Num : %d\n"
		"Lan Login UserServer Num : %d\n"
		"NetSession Num : %d\n"
		"Net Login MonitorClient Num : %d\n"
		"Lan RecvTPS : %llu\n"
		"Net SendTPS: %d\n\n",
		ullElapsedDay, ullElapsedHour, ullElapsedMin, ullElapsedSecond,
		lSessionNum_,
		loginServerNum_,
		pNetServer->lSessionNum_,
		pNetServer->monitorClientNum_,
		recvTPS,
		sendTPS
	);
}

