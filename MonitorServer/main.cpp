#include <WinSock2.h>
#include <windows.h>
#include "MonitorLanServer.h"
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"Winmm.lib")
#include "Parser.h"


//MonitorLanServer g_MLS;

int main()
{
	PARSER psr = CreateParser(L"MonitorNetConfig.txt");
	WCHAR ipStr[20];
	int len = GetValueWSTR(psr, ipStr, _countof(ipStr), L"BIND_IP");
	auto* pMonitorNetServer = new MonitorNetServer
	{ 
		ipStr,
		(const USHORT)GetValueINT(psr,L"BIND_PORT"),
		GetValueUINT(psr,L"IOCP_WORKER_THREAD"),
		GetValueUINT(psr,L"IOCP_ACTIVE_THREAD"),
		GetValueINT(psr,L"IS_ZERO_BYTE_SEND"),
		GetValueINT(psr,L"SESSION_MAX"),
		GetValueINT(psr,L"USER_MAX"),
		(BYTE)GetValueINT(psr,L"PACKET_CODE"),
		(BYTE)GetValueINT(psr,L"PACKET_KEY"),FALSE,0,0 
	};
	ReleaseParser(psr);

	psr = CreateParser(L"MonitorLanConfig.txt");
	len = GetValueWSTR(psr, ipStr, _countof(ipStr), L"BIND_IP");
	auto* pMonitorLanServer = new MonitorLanServer
	{
		ipStr,
		(const USHORT)GetValueINT(psr,L"BIND_PORT"),
		GetValueUINT(psr,L"IOCP_WORKER_THREAD"),
		GetValueUINT(psr,L"IOCP_ACTIVE_THREAD"),
		GetValueINT(psr,L"IS_ZERO_BYTE_SEND"),
		GetValueINT(psr,L"SESSION_MAX"),
		FALSE,
		1000,
		3000,
		GetValueUINT(psr,L"MONITOR_DATA_DB_WRITE_REQUEST_INTERVAL"),
		GetValueUINT(psr,L"DB_WRITE_TIMEOUT")
	};
	ReleaseParser(psr);

	pMonitorLanServer->Start(pMonitorNetServer);
	pMonitorLanServer->WaitUntilShutDown();

	//g_MLS.Start(pMonitorNetServer);
	//g_MLS.WaitUntilShutDown();
	return 0;
}