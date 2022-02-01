#include "HeapManager.cpp"
namespace HeapManagerProxy {

	HeapManager* CreateHeapManager(void* pHeapMemory, const size_t sizeHeap, const unsigned int numDescriptors) {
		HeapManager heap = HeapManager((uint8_t)pHeapMemory, sizeHeap, numDescriptors);
		return &heap;
	}

	void* alloc(HeapManager* pHeapManager, size_t sizeAlloc, const unsigned int alignment) {
		HeapManager::MemoryBlock heap = pHeapManager->heap;
		void* pUserAddress = nullptr;
		uint8_t baseAddress = heap.baseAddress;
		size_t heapSize = heap.blockSize;
		pUserAddress = (void*)((baseAddress + heapSize) - sizeAlloc);
		if (pUserAddress % alignment = 0) {
			continue;
		}
		else {
			pUserAddress + alignment;
		}

	}
}