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

	EchoData& operator=(const EchoData& rhs)
	{
		if (this == &rhs)
			return *this;

		onoff_ = rhs.onoff_;
		cpuTime_ = rhs.cpuTime_;
		memAvailableByte_ = rhs.memAvailableByte_;
		sessionCnt_ = rhs.sessionCnt_;
		authCnt_ = rhs.authCnt_;
		gameCnt_ = rhs.gameCnt_;
		acceptTps_ = rhs.acceptTps_;
		recvTPS_ = rhs.recvTPS_;
		sendTPS_ = rhs.sendTPS_;
		authFPS_ = rhs.authFPS_;
		gameFPS_ = rhs.gameFPS_;
		packetPoolAlloced_ = rhs.packetPoolAlloced_;
		return *this;
	}

	__forceinline void Init()
	{
		new(&cpuTime_)MonitorData{};
		new(&memAvailableByte_)MonitorData{};
		new(&sessionCnt_)MonitorData{};
		new(&authCnt_)MonitorData{};
		new(&gameCnt_)MonitorData{};
		new(&acceptTps_)MonitorData{};
		new(&recvTPS_)MonitorData{};
		new(&sendTPS_)MonitorData{};
		new(&authFPS_)MonitorData{};
		new(&gameFPS_)MonitorData{};
		new(&packetPoolAlloced_)MonitorData{};
	}
};
