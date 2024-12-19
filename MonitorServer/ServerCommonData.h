#pragma once
#include "MonitorData.h"

struct ServerCommonData
{
	MonitorData cpuTime;
	MonitorData NonPagedPoolAvaliableBytes;
	MonitorData memAvailable;
	CRITICAL_SECTION cs;
	ServerCommonData()
	{
		InitializeCriticalSection(&cs);
	}
};
