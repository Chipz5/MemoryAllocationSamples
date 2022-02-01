HeapAllocator.cpp
	contains methods to create heap memory, initialize memory blocks, retrieve the memory blocks, assign outstanding blocks, allocate memory,
free and collect freed memory blocks, checks whether memory has been allocated, etc. Alignment of address is also done in alloc() 


MemorySystem.cpp
	contains helper methods that creates fixed size allocators, allocates memory, frees and collects memory

FixedSizeAllocator.cpp
	creates FSAs for 16, 32 and 92 bytes. Contains methods to allocate heap memory and create bit arrays

BitArray.cpp
	creates a bit array which indicates whether m/y space is available or not.Contain methods that set, clear bits within the bit array, finds the first available m/y space,
