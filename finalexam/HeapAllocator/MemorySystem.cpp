#include "MemorySystem.h"

vector<FixedSizeAllocator*> f;
HeapAllocator* pHeapManager;

void MemorySystem::initialise(void* pHeapMemory) {
    const size_t 		sizeHeap = 1024 * 1024;
    const uint16_t  	numDescriptors = 2048;
    pHeapManager = HeapAllocator::create(pHeapMemory, sizeHeap, numDescriptors);
    createHeaps();
}

void MemorySystem::destroy() {
    const size_t numFSAs = f.size();
    cout << endl << "NUMBER" << numFSAs<<endl;
    for (size_t i = 0; i < numFSAs; i++)
    {
        f[i]->~FixedSizeAllocator();
        pHeapManager->free(f[i]);
    }
}

void MemorySystem::allocateForFixed(HeapAllocator* pHeapManager, size_t num, size_t size) {

    //FixedSizeAllocator* f = static_cast<FixedSizeAllocator*>(pHeapManager->alloc(sizeof(FixedSizeAllocator), alignment));

    //void* h = pHeapManager->alloc(size * num, 0);
    //FixedSizeAllocator *fs = new FixedSizeAllocator(size, num, h, pHeapManager);
    FixedSizeAllocator* fs = FixedSizeAllocator::CreateFixedSizeAllocator(size, num, pHeapManager);
    f.push_back(fs);

}

FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size) {
    if (i_size <= 16 * 8) {
        return f[0];
    }
    else if (i_size <= 32 * 8) {
        return f[1];
    }
    else if (i_size <= 96 * 8) {
        return f[2];
    }
    else {
        return NULL;
    }

}

void MemorySystem::createHeaps() {

    FSA a = { 16,128 };
    FSA b = { 32,128 };
    FSA c = { 96,128 };
    FSA p[] = { { 16,100 } , { 32,200 } , { 96,400 } };

    for (unsigned int i = 0; i < 3; i++) {
        allocateForFixed(pHeapManager, p[i].numBlocks, p[i].sizeBlocks);
    }
}


void* MemorySystem::malloc(size_t i_size) {
    void* pReturn = nullptr;
    FixedSizeAllocator* pFSA = FindFixedSizeAllocator(i_size);
    if (pFSA)
        pReturn = pFSA->allocMem(i_size);
    // if no FSA available or there was one and it is full   
    if (pReturn == nullptr)
        pReturn = pHeapManager->alloc(i_size, 0);
    return pReturn;
}

void MemorySystem::free(void* i_ptr)
{
    const size_t numFSAs = f.size();
    for (size_t i = 0; i < numFSAs; i++)
    {
        if (f[i]->contains(i_ptr))
        {
            f[i]->free(i_ptr);
            return;
        }
    }
    assert(pHeapManager->isAllocated(i_ptr));
    pHeapManager->free(i_ptr);
    return;
}

void MemorySystem::collect() {
    pHeapManager->collect();
}
