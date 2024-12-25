#pragma once
#include "MonitorData.h"

struct LoginData 
{
	bool onoff_ = false;			// ���� ����
	MonitorData cpuTime_;			// CPU ����
	MonitorData memAvailableByte_;			// �޸� ��� MByte
	MonitorData sessionCnt_;		// Session ��
	MonitorData loginProcessTps_;			// �ʴ� �α��� ó�� ��
	MonitorData packetPoolAlloced_;		// Packet Pool ��뷮
	CRITICAL_SECTION cs;
	LoginData()
	{
		InitializeCriticalSection(&cs);
	}

	LoginData& operator=(const LoginData& rhs)
	{
		if (this == &rhs)
			return *this;

		onoff_ = rhs.onoff_;
		cpuTime_ = rhs.cpuTime_;
		memAvailableByte_ = rhs.memAvailableByte_;
		sessionCnt_ = rhs.sessionCnt_;
		loginProcessTps_ = rhs.loginProcessTps_;
		packetPoolAlloced_ = rhs.packetPoolAlloced_;
		return *this;
	}
	__forceinline void Init()
	{
		new(&cpuTime_)MonitorData{};
		new(&memAvailableByte_)MonitorData{};
		new(&sessionCnt_)MonitorData{};
		new(&loginProcessTps_)MonitorData{};
		new(&packetPoolAlloced_)MonitorData{};
	}
};
