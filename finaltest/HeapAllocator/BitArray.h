#pragma once
#include <cstdint>
#include <vcruntime_string.h>
#include <cassert>
#include <intrin0.h>
#include <iostream>
#include "HeapAllocator.h"

class BitArray
{
#ifdef _WIN64
	typedef uint32_t t_BitData;
#else
	typedef uint64_t t_BitData;
#endif // WIN32

private:
	t_BitData* bits;
	const size_t bitsPerElement = sizeof(t_BitData) * 8;
	HeapAllocator* heapManager;
	size_t numElements;
	bool operator[](size_t bitIndex) const;
	bool findFirstClearBit(size_t& firstSetBitIndex) const;
	void clearBit(size_t bitNumber);
	void clearAll();
	bool areAllBitsClear() const;
	bool areAllBitsSet() const;

public:
	BitArray(size_t numBits, bool initToZeroes, HeapAllocator* heapManager);
	~BitArray();
	static BitArray* createBitArray(size_t numBits, bool startClear, HeapAllocator* heapManager);
	void setAll();
	bool isBitSet(size_t bitNumber) const;
	void setBit(size_t bitNumber);
	bool findFirstSetBit(size_t& firstSetBitIndex) const;
};