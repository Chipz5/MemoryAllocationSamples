#include "MemorySystem.h"

vector<FixedSizeAllocator*> fsa;
HeapAllocator* heapManager;

void MemorySystem::initialise(void* heapMemory) {
    const size_t 		sizeHeap = 1024 * 1024;
    const uint16_t  	numDescriptors = 2048;
    heapManager = HeapAllocator::create(heapMemory, sizeHeap, numDescriptors);
    createHeaps();
}

void MemorySystem::destroy() {
    const size_t numFSAs = fsa.size();
    cout << "Destroying and cleaning m/y system" <<endl;
    for (size_t i = 0; i < numFSAs; i++)
    {
        fsa[i]->~FixedSizeAllocator();
        heapManager->free(fsa[i]);
    }
}

void MemorySystem::allocateForFixed(size_t num, size_t size) {
    FixedSizeAllocator* fs = FixedSizeAllocator::CreateFixedSizeAllocator(size, num, heapManager);
    fsa.push_back(fs);
}

FixedSizeAllocator* findFixedSizeAllocator(size_t size) {
    if (size <= 16 * 8) {
        return fsa[0];
    }
    else if (size <= 32 * 8) {
        return fsa[1];
    }
    else if (size <= 96 * 8) {
        return fsa[2];
    }
    else {
        return NULL;
    }

}

void MemorySystem::createHeaps() {
    FSA p[] = { { 16,120 } , { 32,200 } , { 96,400 } };
    for (unsigned int i = 0; i < 3; i++) {
        allocateForFixed(p[i].numBlocks, p[i].sizeBlocks);
    }
}

void* MemorySystem::malloc(size_t size) {
    void* pReturn = nullptr;
    FixedSizeAllocator* pFSA = findFixedSizeAllocator(size);
    if (pFSA)
        pReturn = pFSA->allocMem();
    // if no FSA available or there was one and it is full   
    if (pReturn == nullptr)
        pReturn = heapManager->alloc(size, 0);
    return pReturn;
}

void MemorySystem::free(void* ptr)
{
    const size_t numFSAs = fsa.size();
    for (size_t i = 0; i < numFSAs; i++)
    {
        if (fsa[i]->contains(ptr))
        {
            fsa[i]->free(ptr);
            return;
        }
    }
    assert(heapManager->isAllocated(ptr));
    heapManager->free(ptr);
    return;
}

void MemorySystem::collect() {
    heapManager->collect();
}
