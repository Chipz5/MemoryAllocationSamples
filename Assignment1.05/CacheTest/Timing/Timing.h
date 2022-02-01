#ifndef __TIMING_H
#define __TIMING_H

#include <stdint.h>

namespace Engine
{
namespace Timing
{
	typedef uint64_t	tick;
	
	bool Initialize();
	
	tick GetCurrentTickCounter();
	double GetTimeDiffInMilliseconds(tick i_StartTick, tick i_EndTick = GetCurrentTickCounter());
	double ConvertTicksToMilliseconds(tick i_TickCount);

	inline double ConvertSecondsToMilliseconds( double i_Seconds );
	inline double ConverttPerSecondToPerMillisecond( double i_PerSecond );
	
}
} // namespace Engine

#include "Timing-inl.h"

#endif // __TIMING_H