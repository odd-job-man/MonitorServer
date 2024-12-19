#pragma once
#include "MonitorData.h"
struct EchoData
{
	bool onoff_ = false;
	MonitorData cpuTime_;
	MonitorData memAvailableByte_;
	MonitorData sessionCnt_;
	MonitorData authCnt_;
	MonitorData gameCnt_;
	MonitorData acceptTps_;
	MonitorData recvTPS_;
	MonitorData sendTPS_;
	MonitorData authFPS_;
	MonitorData gameFPS_;
	MonitorData packetPoolAlloced_;
	CRITICAL_SECTION cs;
	EchoData()
	{
		InitializeCriticalSection(&cs);
	}
};
