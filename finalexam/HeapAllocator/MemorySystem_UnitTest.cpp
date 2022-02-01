#include "MemorySystem_UnitTest.h"
bool MemorySystem_UnitTest()
{
	const size_t maxAllocations = 10 * 1024;
	std::vector<void*> AllocatedAddresses;
	const size_t 		sizeHeap = 1024 * 1024;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	size_t totalAllocated = 0;

	// reserve space in AllocatedAddresses for the maximum number of allocation attempts
	// prevents new returning null when std::vector expands the underlying array
	AllocatedAddresses.reserve(10 * 1024);
	MemorySystem::initialise(pHeapMemory);
	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void* pPtr = MemorySystem::malloc(sizeAlloc);

		// if allocation failed see if garbage collecting will create a large enough block
		if (pPtr == nullptr)
		{
			MemorySystem::collect();

			pPtr = MemorySystem::malloc(sizeAlloc);

			// if not we're done. go on to cleanup phase of test
			if (pPtr == nullptr)
				break;
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		totalAllocated += sizeAlloc;

		// randomly free and/or garbage collect during allocation phase
		const unsigned int freeAboutEvery = 0x07;
		const unsigned int garbageCollectAboutEvery = 0x07;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void* pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			MemorySystem::free(pPtrToFree);
			numFrees++;
		}
		else if ((rand() % garbageCollectAboutEvery) == 0)
		{
			MemorySystem::collect();

			numCollects++;
		}

	} while (numAllocs < 2);

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty()) 
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void* pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			MemorySystem::free(pPtrToFree);
			//delete[] pPtrToFree;
		}

		// do garbage collection
		MemorySystem::destroy();
		MemorySystem::collect();
		// our heap should be one single block, all the memory it started with

		// do a large test allocation to see if garbage collection worked
		void* pPtr = MemorySystem::malloc(sizeHeap / 2);

		if (pPtr)
		{
			MemorySystem::free(pPtr);
		}
		else
		{
			// something failed
			return false;
		}
	}
	else
	{
		return false;
	}
	cout << endl<< "FINAL " << totalAllocated << endl;
	// this new [] / delete [] pair should run through your allocator
	//char* pNewTest = new char[1024];

	//delete[] pNewTest;
	// we succeeded
	return true;
}