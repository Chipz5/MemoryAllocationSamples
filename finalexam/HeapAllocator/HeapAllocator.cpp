#include "HeapAllocator.h"

using namespace std;

HeapAllocator* HeapAllocator::create(void* heapMemory, size_t heapMemorySize, uint16_t numMemBlocks)
{
    HeapAllocator* theHeapAllocator = reinterpret_cast<HeapAllocator*>(heapMemory);
    heapMemory = theHeapAllocator + 1;
    heapMemorySize -= sizeof(HeapAllocator);
    cout << "Heap memory: " << heapMemory << endl;
    cout << "Heap size: " << heapMemorySize << endl;
    return new (theHeapAllocator) HeapAllocator(heapMemory, heapMemorySize, numMemBlocks);
}

HeapAllocator::HeapAllocator(void* heapMemory, size_t heapMemorySize, uint16_t numMemBlocks) {
    pFreeList = nullptr;
    initializeMemoryBlocks(heapMemory, numMemBlocks * sizeof(MemoryBlock));
    pOutstandingAllocations = nullptr;
    pFreeList = getMemoryBlock();
    pFreeList->pBaseAddress = reinterpret_cast<char*>(heapMemory) + (numMemBlocks * sizeof(MemoryBlock));
    pFreeList->BlockSize = heapMemorySize - (numMemBlocks * sizeof(MemoryBlock));
    pFreeList->pNextBlock = nullptr;
}

void HeapAllocator::initializeMemoryBlocks(void* blocksMemory, size_t blocksMemorySize)
{
    assert(blocksMemory != nullptr);
    assert(blocksMemorySize > sizeof(MemoryBlock));

    pFreeMemBlocks = reinterpret_cast<MemoryBlock*>(blocksMemory);
    const size_t numBlocks = blocksMemorySize / sizeof(MemoryBlock);
    MemoryBlock* pCurrentBlock = pFreeMemBlocks;

    for (size_t i = 0; i < (numBlocks - 1); i++)
    {
        pCurrentBlock->pBaseAddress = nullptr;
        pCurrentBlock->BlockSize = 0;
        pCurrentBlock->pNextBlock = pCurrentBlock + 1;

        pCurrentBlock++;
    }
    // last block, end the list
    pCurrentBlock->pBaseAddress = nullptr;
    pCurrentBlock->BlockSize = 0;
    pCurrentBlock->pNextBlock = nullptr;

}

MemoryBlock* HeapAllocator::getMemoryBlock()
{
    assert(pFreeMemBlocks != nullptr);
    MemoryBlock* pReturnBlock = pFreeMemBlocks;
    pFreeMemBlocks = pFreeMemBlocks->pNextBlock;
    return pReturnBlock;
}

void HeapAllocator::assignOutstanding(MemoryBlock* allocation) {
    if (pOutstandingAllocations == nullptr) {
        pOutstandingAllocations = allocation;
    }
    else {
        MemoryBlock* pBlock = allocation;
        pBlock->pNextBlock = pOutstandingAllocations;
        pOutstandingAllocations = pBlock;
    }

}

void* HeapAllocator::alloc(size_t size, uint16_t alignment)
{
    if (alignment == NULL) {
        const uint16_t	alignments[] = { 4, 8, 16, 32, 64 };
        const uint16_t	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));
        alignment = alignments[index];
    }

    size_t n_size = size + alignment;
    cout << "size = " << size << endl;
    cout << "alignment = " << alignment << endl;
    MemoryBlock* pFree = pFreeList;
    while (pFree) {
        if (pFree->BlockSize > n_size)
            break;
        pFree = pFree->pNextBlock;
    }
    if (!pFree)
        return NULL;
    if (pFree->BlockSize < n_size)
        return NULL;
    cout << "Before Allocation" << endl;
    cout << "Free base address: " << pFree->pBaseAddress << endl;
    cout << "Free memory size: " << pFree->BlockSize << endl;
    void* endAddress = reinterpret_cast<char*>(pFree->pBaseAddress) + pFree->BlockSize;
    void* actualAddress = reinterpret_cast<char*>(endAddress) - size;
    size_t alignedAddress = (size_t)actualAddress - ((size_t)actualAddress % alignment);
    MemoryBlock* allocation = getMemoryBlock();
    allocation->pBaseAddress = (void*)alignedAddress;
    allocation->BlockSize = size + ((size_t)actualAddress % alignment);
    allocation->pNextBlock = nullptr;
    assignOutstanding(allocation);
    cout << "After Allocation" << endl;
    cout << "Allocated base address:" << allocation->pBaseAddress << endl;
    cout << "Allocated block size: " << allocation->BlockSize << endl;
    pFree->BlockSize -= size + ((size_t)actualAddress % alignment);
    if (pFree->BlockSize == 0) {
        pFree->pBaseAddress = NULL;
    }
    cout << "Free base address:" << pFree->pBaseAddress << endl;
    cout << "Free block size: " << pFree->BlockSize << endl;
    return allocation->pBaseAddress;

}

void HeapAllocator::free(void* pPtr) {
    MemoryBlock* allocated = pOutstandingAllocations;
    if (allocated->pBaseAddress == pPtr) {
        MemoryBlock* head = allocated->pNextBlock;
        allocated->pNextBlock = nullptr;
        MemoryBlock* pBlock = allocated;
        cout << endl << "to free " << allocated->BlockSize << endl;
        pFreeList->BlockSize += allocated->BlockSize;
        pBlock->pNextBlock = pFreeMemBlocks;
        pFreeMemBlocks = pBlock;
        pOutstandingAllocations = head;
        cout << "Free base address:" << pFreeList->pBaseAddress << endl;
        cout << "Free block size: " << pFreeList->BlockSize << endl;
        return;
    }
    MemoryBlock* prev = pOutstandingAllocations;
    while (prev->pNextBlock && prev->pNextBlock->pBaseAddress != pPtr)
        prev = prev->pNextBlock;
    if (!prev->pNextBlock)
        return;
    allocated = prev->pNextBlock;
    cout << endl << "to free " << allocated->BlockSize << endl;
    prev->pNextBlock = prev->pNextBlock->pNextBlock;
    pFreeList->BlockSize += allocated->BlockSize;
    allocated->pNextBlock = nullptr;
    MemoryBlock* pBlock = allocated;
    pBlock->pNextBlock = pFreeMemBlocks;
    pFreeMemBlocks = pBlock;
    cout << "Free base address:" << pFreeList->pBaseAddress << endl;
    cout << "Free block size: " << pFreeList->BlockSize << endl;

}


void HeapAllocator::collect() {
    MemoryBlock* head = pFreeList;
    bool resetHead = false;
    while (head) {
        MemoryBlock* list = pFreeList;
        resetHead = false;
        while (list) {
            if (list->pNextBlock) {

                if (reinterpret_cast<char*>(head->pBaseAddress) + head->BlockSize == reinterpret_cast<char*>(list->pNextBlock->pBaseAddress)) {
                    head->BlockSize += list->pNextBlock->BlockSize;
                    list->pNextBlock = list->pNextBlock->pNextBlock;
                    resetHead = true;
                }
            }
            else {
                if (reinterpret_cast<char*>(head->pBaseAddress) + head->BlockSize == reinterpret_cast<char*>(list->pBaseAddress)) {
                    head->BlockSize += list->BlockSize;
                    list = nullptr;
                    resetHead = true;
                }
            }
            if (list) {
                list = list->pNextBlock;
            }
        }
        head = head->pNextBlock;
        if (resetHead)
            head = pFreeList;
    }
}


bool HeapAllocator::isAllocated(void* pPtr) {
    MemoryBlock* allocated = pOutstandingAllocations;
    while (allocated) {
        if (allocated->pBaseAddress == pPtr) {
            return true;
        }
        allocated = allocated->pNextBlock;
    }
    return false;
}

void HeapAllocator::printAll() {
    while (pFreeMemBlocks != nullptr) {
        cout << pFreeMemBlocks->pBaseAddress << endl;
        cout << pFreeMemBlocks->BlockSize << endl;
        pFreeMemBlocks = pFreeMemBlocks->pNextBlock;
    }

    while (pFreeList != nullptr) {
        cout << pFreeList->pBaseAddress << endl;
        cout << pFreeList->BlockSize << endl;
        pFreeList = pFreeList->pNextBlock;
    }

    while (pOutstandingAllocations != nullptr) {
        cout << pOutstandingAllocations->pBaseAddress << endl;
        cout << pOutstandingAllocations->BlockSize << endl;
        pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
    }
}

void HeapAllocator::destroy() {
    pFreeList = nullptr;
    pOutstandingAllocations = nullptr;
    pFreeMemBlocks = nullptr;
}

void HeapAllocator::showFreeBlocks() {
    MemoryBlock* free = pFreeList;
    while (free != nullptr) {
        cout << free->pBaseAddress << endl;
        cout << free->BlockSize << endl;
        free = free->pNextBlock;
    }
}

void HeapAllocator::showOutstandingBlocks() {
    MemoryBlock* allocated = pOutstandingAllocations;
    while (allocated != nullptr) {
        cout << allocated->pBaseAddress << endl;
        cout << allocated->BlockSize << endl;
        allocated = allocated->pNextBlock;
    }
}

HeapAllocator::~HeapAllocator() {

}