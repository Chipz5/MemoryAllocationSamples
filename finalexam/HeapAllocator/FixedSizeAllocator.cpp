#pragma once
#include "BitArray.h"
#include <cassert>
#include "FixedSizeAllocator.h"

FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks, HeapAllocator* i_pHeapManager) :
	m_blockSize(i_blockSize),
	m_numBlocks(i_numBlocks),
	m_pHeapManager(i_pHeapManager)
{
	m_pBlockAvailabilities = BitArray::CreateBitArray(i_numBlocks, false, i_pHeapManager);
	m_pFSABlocks = static_cast<MemoryBlock*>(i_pHeapManager->alloc(i_blockSize * i_numBlocks, 4));
}


FixedSizeAllocator* FixedSizeAllocator::CreateFixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks, HeapAllocator* i_pHeapManager) {
	FixedSizeAllocator* pFixedSizeAllocator = static_cast<FixedSizeAllocator*>(i_pHeapManager->alloc(sizeof(FixedSizeAllocator), 4));
	return new (pFixedSizeAllocator) FixedSizeAllocator(i_blockSize, i_numBlocks, i_pHeapManager);
}

void* FixedSizeAllocator::allocMem(size_t i_size) {
	size_t o_firstAvailableIndex;
	if (m_pBlockAvailabilities->FindFirstSetBit(o_firstAvailableIndex)) {
		// mark the bit in use
		m_pBlockAvailabilities->SetBit(o_firstAvailableIndex);
		return reinterpret_cast<char*>(m_pFSABlocks) + (o_firstAvailableIndex * m_blockSize);
	}
	else {
		return nullptr;
	}
}

FixedSizeAllocator::~FixedSizeAllocator() {
	// free BitArray intance, BitArray m_pBits memory, and pFSABlock memory
	m_pBlockAvailabilities->~BitArray();
	m_pHeapManager->free(m_pBlockAvailabilities);
	m_pHeapManager->free(m_pFSABlocks);
}

bool FixedSizeAllocator::contains(void* i_ptr) {
	if (i_ptr >= m_pFSABlocks && i_ptr <= (reinterpret_cast<char*>(m_pFSABlocks) + m_blockSize * m_numBlocks)) {
		size_t i_bitIndex = (reinterpret_cast<char*>(i_ptr) - reinterpret_cast<char*>(m_pFSABlocks)) / m_blockSize;
		cout << "to find at index : " << i_bitIndex << endl;
		return m_pBlockAvailabilities->IsBitSet(i_bitIndex);
	}
	else
		return false;
}


void FixedSizeAllocator::free(void* i_ptr) {
	char* i_ptrAddress = reinterpret_cast<char*>(i_ptr);
	char* FSAMemBaseAddress = reinterpret_cast<char*>(m_pFSABlocks);
	if (!(i_ptrAddress >= FSAMemBaseAddress && i_ptrAddress < (FSAMemBaseAddress + m_blockSize * m_numBlocks))) {
		return;
	}
	size_t addressDiff = i_ptrAddress - FSAMemBaseAddress;
	size_t bitIndex = 0;
	if (addressDiff == 0) {
		bitIndex = 0;
	}
	else {
		bitIndex = addressDiff / m_blockSize;
	}

	if (m_pBlockAvailabilities->IsBitSet(bitIndex)) {
		return;
	}

	m_pBlockAvailabilities->SetBit(bitIndex);
}