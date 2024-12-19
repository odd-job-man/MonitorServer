#pragma once
#include <windows.h>
struct MonitorData
{
	LONG total_ = 0;
	LONG cnt_ = 0;
	LONG min_ = LONG_MAX;
	LONG max_ = LONG_MIN;
};
