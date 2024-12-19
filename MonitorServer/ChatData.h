#pragma once
#include "MonitorData.h"
struct ChatData
{
	bool onoff_ = false;			
	MonitorData cpuTime_;			
	MonitorData memAvailableByte_;			 
	MonitorData sessionCnt_;		
	MonitorData playerCnt_;		
	MonitorData updateTps_;		
	MonitorData packetPoolAlloced_;		
	MonitorData mQAlloced_;			
	CRITICAL_SECTION cs;
	ChatData()
	{
		InitializeCriticalSection(&cs);
	}
};
