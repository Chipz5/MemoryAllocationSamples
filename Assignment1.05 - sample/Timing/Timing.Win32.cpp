#include <windows.h>

#include <assert.h>
#include <limits.h>

#include "Timing.h"

namespace Engine
{
namespace Timing
{
	unsigned int LastFrame_ms;

	LARGE_INTEGER PerformanceFrequency = { 0 };

	bool Initialize()
	{
		if (!QueryPerformanceFrequency(&PerformanceFrequency))
			return false;

		return true;
	}

	tick GetCurrentTickCounter()
	{
		LARGE_INTEGER CurrentFrameCounter;

		BOOL success = QueryPerformanceCounter(&CurrentFrameCounter);
		assert(success == TRUE);

		return CurrentFrameCounter.QuadPart;
	}

	double GetTimeDiffInMilliseconds(tick i_StartTick, tick i_EndTick)
	{
		assert(PerformanceFrequency.QuadPart != 0);

		return (1000.0 * double(i_EndTick - i_StartTick)) / PerformanceFrequency.QuadPart;
	}

	double ConvertTicksToMilliseconds(tick i_TickCount)
	{
		assert(PerformanceFrequency.QuadPart != 0);

		return (1000.0 * double(i_TickCount)) / PerformanceFrequency.QuadPart;
	}
} // Timing
} // Engine