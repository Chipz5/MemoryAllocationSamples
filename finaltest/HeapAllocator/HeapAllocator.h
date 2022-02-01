#pragma once
#include<stdint.h>
#include<iostream>
#include <cassert>

using namespace std;

struct MemoryBlock {
    void* pBaseAddress;
    size_t BlockSize;
    struct MemoryBlock* pNextBlock;
};

class HeapAllocator
{
private:
    struct MemoryBlock* pFreeMemBlocks;
    struct MemoryBlock* pFreeList;
    struct MemoryBlock* pOutstandingAllocations;
    void initializeMemoryBlocks(void* blocksMemory, size_t blocksMemorySize);
    MemoryBlock* getMemoryBlock();
    void assignOutstanding(MemoryBlock* allocation);
    void printAll();
    void showFreeBlocks();
    void showOutstandingBlocks();

public:
    static HeapAllocator* create(void* heapMemory, size_t heapMemorySize, uint16_t numMemBlocks);
    HeapAllocator(void* heapMemory, size_t heapMemorySize, uint16_t numMemBlocks);
    ~HeapAllocator();
    void* alloc(size_t size, uint16_t alignment);
    void free(void* ptr);
    void collect();
    bool isAllocated(void* ptr);
    void destroy();
};
