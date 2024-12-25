#include <WinSock2.h>
#include <windows.h>
#include "MonitorLanServer.h"
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"Winmm.lib")


MonitorLanServer g_MLS;

int main()
{
	g_MLS.Start();
	g_MLS.WaitUntilShutDown();
	return 0;
}