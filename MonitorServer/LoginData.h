#pragma once
#include "MonitorData.h"
struct LoginData 
{
	bool onoff_ = false;			// 실행 여부
	MonitorData cpuTime_;			// CPU 사용률
	MonitorData memoryAvailableByte_;			// 메모리 사용 MByte
	MonitorData sessionCnt_;		// Session 수
	MonitorData loginProcessTps_;			// 초당 로그인 처리 수
	MonitorData packetPoolAlloced_;		// Packet Pool 사용량
	CRITICAL_SECTION cs;
	LoginData()
	{
		InitializeCriticalSection(&cs);
	}
};
