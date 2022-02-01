#include "Timing/Timing.h"

#include <stdio.h>
#include <random>

#define USE_RANDOM_DISTRIBUTION

int main()
{

	// one time init
	Engine::Timing::Initialize();

	const size_t Size = 512 * 1024 * 1024;

	unsigned int* pLinearAccessArray = new unsigned int[Size];

	long unsigned LinearAccessSum = 0;
	// grab the current tick counter
	Engine::Timing::tick LinearSumStart = Engine::Timing::GetCurrentTickCounter();

	for (size_t i = 0; i < Size; i++)
		LinearAccessSum += pLinearAccessArray[i];

	double LinearAccessSumTime = Engine::Timing::GetTimeDiffInMilliseconds(LinearSumStart, Engine::Timing::GetCurrentTickCounter());

	// print the sum so sumation doesn't get optimized out.
	printf("Forward sum: %lu\n", LinearAccessSum);

	unsigned int* pRandomAccessArray = new unsigned int[Size];

#ifdef USE_RANDOM_DISTRIBUTION
	std::random_device RandomDevice;  //Will be used to obtain a seed for the random number engine
	std::mt19937 Generator(RandomDevice()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> Distribution(0UL, Size - 1);
#else
	const size_t SizeMask = Size - 1;
	size_t index = std::rand();
#endif // USE_RANDOM_DISTRIBUTION

	Engine::Timing::tick IndexGenerationTickCount = 0;

	long unsigned RandomAccessSum = 0;
	// grab the current tick counter
	Engine::Timing::tick RandomAccessStart = Engine::Timing::GetCurrentTickCounter();

	for (size_t i = 0; i < Size; i++)
	{
#ifdef USE_RANDOM_DISTRIBUTION
		// track how much time we take generating the random index so we can subtract it out later
		Engine::Timing::tick IndexGenStart = Engine::Timing::GetCurrentTickCounter();
		size_t index = Distribution(Generator);
		IndexGenerationTickCount += Engine::Timing::GetCurrentTickCounter() - IndexGenStart;
#else
		index = (index + 9999) & SizeMask;
#endif // USE_RANDOM_DISTRIBUTION

		RandomAccessSum += pRandomAccessArray[index];
	}

	// grab the current tick counter again
	Engine::Timing::tick RandomAccessEnd = Engine::Timing::GetCurrentTickCounter();
	// calculate how long it took to sum up randomly, subtracking ticks spent generati
	double RandomAccessSumTime = Engine::Timing::ConvertTicksToMilliseconds( RandomAccessEnd - RandomAccessStart - IndexGenerationTickCount);

	// print the sum so sumation doesn't get optimized out.

	printf("Random sum: %lu\n", RandomAccessSum);

	printf("Linear access sum time: %fms\n", LinearAccessSumTime);
	printf("Random access sum time: %fms\n", RandomAccessSumTime);
	printf("Random access %fx linear.\n", RandomAccessSumTime / LinearAccessSumTime);

#ifdef USE_RANDOM_DISTRIBUTION
	printf("Random index generation time: %fms\n", Engine::Timing::ConvertTicksToMilliseconds(IndexGenerationTickCount));
#endif // USE_RANDOM_DISTRIBUTION

	delete[] pLinearAccessArray;
	delete[] pRandomAccessArray;

	return 0;
}
