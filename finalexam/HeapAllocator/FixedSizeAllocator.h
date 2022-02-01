#pragma once
#include "BitArray.h"

class FixedSizeAllocator {
public:
	size_t m_blockSize;
	size_t m_numBlocks;
	HeapAllocator* m_pHeapManager;
	BitArray* m_pBlockAvailabilities;
	void* m_pFSABlocks;
	FixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks, HeapAllocator* i_pHeapManager);
	static FixedSizeAllocator* CreateFixedSizeAllocator(size_t i_blockSize, size_t i_numBlocks, HeapAllocator* i_pHeapManager);
	void freeMem(void* i_ptr);
	void* allocMem(size_t i_size);
	void free(void* i_ptr);
	~FixedSizeAllocator();
	bool contains(void* i_ptr);

};
