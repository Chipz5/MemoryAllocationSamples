#include "FixedSizeAllocator.h"

FixedSizeAllocator::FixedSizeAllocator(size_t blockSize, size_t numBlocks, HeapAllocator* heapManager) :
	blockSize(blockSize),
	numBlocks(numBlocks),
	heapManager(heapManager)
{
	bitArray = BitArray::createBitArray(numBlocks, false, heapManager);
	FSABlocks = static_cast<MemoryBlock*>(heapManager->alloc(blockSize * numBlocks, 4));
}


FixedSizeAllocator* FixedSizeAllocator::CreateFixedSizeAllocator(size_t blockSize, size_t numBlocks, HeapAllocator* heapManager) {
	FixedSizeAllocator* pFixedSizeAllocator = static_cast<FixedSizeAllocator*>(heapManager->alloc(sizeof(FixedSizeAllocator), 4));
	return new (pFixedSizeAllocator) FixedSizeAllocator(blockSize, numBlocks, heapManager);
}

void* FixedSizeAllocator::allocMem() {
	size_t firstAvailableIndex;
	if (bitArray->findFirstSetBit(firstAvailableIndex)) {
		bitArray->setBit(firstAvailableIndex);
		return reinterpret_cast<char*>(FSABlocks) + (firstAvailableIndex * blockSize);
	}
	else {
		return nullptr;
	}
}

FixedSizeAllocator::~FixedSizeAllocator() {
	bitArray->~BitArray();
	heapManager->free(bitArray);
	heapManager->free(FSABlocks);
}

bool FixedSizeAllocator::contains(void* ptr) {
	if (ptr >= FSABlocks && ptr <= (reinterpret_cast<char*>(FSABlocks) + blockSize * numBlocks)) {
		size_t bitIndex = (reinterpret_cast<char*>(ptr) - reinterpret_cast<char*>(FSABlocks)) / blockSize;
		return bitArray->isBitSet(bitIndex);
	}
	else
		return false;
}


void FixedSizeAllocator::free(void* ptr) {
	char* ptrAddress = reinterpret_cast<char*>(ptr);
	char* FSAMemBaseAddress = reinterpret_cast<char*>(FSABlocks);
	if (!(ptrAddress >= FSAMemBaseAddress && ptrAddress < (FSAMemBaseAddress + blockSize * numBlocks))) {
		return;
	}
	size_t addressDiff = ptrAddress - FSAMemBaseAddress;
	size_t bitIndex = 0;
	if (addressDiff == 0) {
		bitIndex = 0;
	}
	else {
		bitIndex = addressDiff / blockSize;
	}

	if (bitArray->isBitSet(bitIndex)) {
		return;
	}

	bitArray->setBit(bitIndex);
}