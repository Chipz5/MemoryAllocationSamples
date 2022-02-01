#include <stdint.h>

namespace Engine
{
	static const uint32_t 	allBitsSet = ~0;
	const float 				NAN = *reinterpret_cast<const float*>(&allBitsSet);
} // namespace Engine