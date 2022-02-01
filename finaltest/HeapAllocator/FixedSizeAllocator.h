#pragma once
#include "BitArray.h"
#include <cassert>

class FixedSizeAllocator {
private:
	size_t blockSize;
	size_t numBlocks;
	HeapAllocator* heapManager;
	BitArray* bitArray;
	void* FSABlocks;
public:
	FixedSizeAllocator(size_t blockSize, size_t numBlocks, HeapAllocator* heapManager);
	static FixedSizeAllocator* CreateFixedSizeAllocator(size_t blockSize, size_t numBlocks, HeapAllocator* heapManager);
	void* allocMem();
	void free(void* ptr);
	~FixedSizeAllocator();
	bool contains(void* ptr);
};
