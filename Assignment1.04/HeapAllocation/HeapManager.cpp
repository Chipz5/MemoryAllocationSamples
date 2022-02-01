#include "HeapManager.h"
#include <cstdint>

class HeapManager {

    

public:
    struct MemoryBlock
    {
        uint8_t baseAddress;
        size_t blockSize;
    };
    struct MemoryBlock heap;
    unsigned int num;
    HeapManager(uint8_t pHeapMemory, const size_t sizeHeap, const unsigned int numDescriptors) {
        heap.baseAddress = pHeapMemory;
        heap.blockSize = sizeHeap;
        num = numDescriptors;
    }

    MemoryBlock getHeap() {
        return heap;
    }
};