#pragma once
#include "DBWriteThreadBase.h"

// WORD en_MONITOR_DB_JOB(ONOFF)
// INT SERVERNUM (CHAT,LOGIN,GAME)
// INT STATE (ON,OFF)

// WORD en_MONITOR_DB_JOB(MONITORWRITE)

enum en_MONITOR_DB_JOB
{
	ONOFF,
	MONITORWRITE
};

enum SERVERSTATE
{
	ON,
	OFF
};


class MonitorDbThread : public DBWriteThreadBase
{
public:
	MonitorDbThread(DWORD timeOutInterval, HANDLE hCompletionPort, LONG timeOutPqcsLimit);
	void ProcessOnoff(Packet* pPacket);
	void ProcessMonitorWrite();
	virtual void OnWrite(Packet* pPacket) override;
};

class DBRequestTimer : public UpdateBase
{
public:
	DBRequestTimer(DWORD requestInterval, HANDLE hCompletionPort, LONG timeOutPqcsLimit,MonitorDbThread* pMonitorDbThread);
	virtual void Update_IMPL() override;
	MonitorDbThread* pMonitorDbThread_;
};
