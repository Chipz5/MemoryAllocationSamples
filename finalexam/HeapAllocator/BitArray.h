#pragma once
#include "HeapAllocator.h"
#include <cstdint>
#include <vcruntime_string.h>
#include "HeapAllocator.h"
#include <cassert>
#include <intrin0.h>
#include <iostream>

class BitArray
{
#ifdef _WIN64
	typedef uint32_t t_BitData;
#else
	typedef uint64_t t_BitData;
#endif // WIN32

private:
	t_BitData* m_pBits;

	const size_t bitsPerElement = sizeof(t_BitData) * 8;

	HeapAllocator* m_pHeapManager;

	size_t m_numElements;
public:

	BitArray(size_t i_numBits, bool i_initToZeroes, HeapAllocator* i_pHeapManager);
	~BitArray();
	static BitArray* CreateBitArray(size_t i_numBits, bool i_startClear, HeapAllocator* i_pHeapManager);
	void ClearAll();
	void SetAll();
	bool AreAllBitsClear() const;
	bool AreAllBitsSet() const;
	bool IsBitSet(size_t i_bitNumber) const;
	void ClearBit(size_t i_bitNumber);
	void SetBit(size_t i_bitNumber);
	bool FindFirstClearBit(size_t& o_firstSetBitIndex) const;
	bool FindFirstSetBit(size_t& o_firstSetBitIndex) const;
	bool operator[](size_t i_bitIndex) const;

};