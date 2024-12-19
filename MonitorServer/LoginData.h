#pragma once
#include "MonitorData.h"
struct LoginData 
{
	bool onoff_ = false;			// ���� ����
	MonitorData cpuTime_;			// CPU ����
	MonitorData memoryAvailableByte_;			// �޸� ��� MByte
	MonitorData sessionCnt_;		// Session ��
	MonitorData loginProcessTps_;			// �ʴ� �α��� ó�� ��
	MonitorData packetPoolAlloced_;		// Packet Pool ��뷮
	CRITICAL_SECTION cs;
	LoginData()
	{
		InitializeCriticalSection(&cs);
	}
};
