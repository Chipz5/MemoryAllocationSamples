#pragma once
#include<stdint.h>
using namespace std;
struct MemoryBlock {
    void* pBaseAddress;
    size_t BlockSize;
    struct MemoryBlock* pNextBlock;
};

class HeapAllocator
{
public:
    static HeapAllocator* Create(void* i_pHeapMemory, size_t i_HeapMemorySize, uint16_t i_NumMemBlocks);

    HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, uint16_t i_NumMemBlocks);
    ~HeapAllocator();
    void InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize);
    MemoryBlock* GetMemoryBlock();
    void ReturnMemoryBlock(MemoryBlock* i_pFreeBlock);
    void* malloc(size_t size);
    void* alloc(size_t size, uint16_t alignment);
    struct MemoryBlock* pFreeMemBlocks;
    struct MemoryBlock* pFreeList;
    struct MemoryBlock* pOutstandingAllocations;
    void assignOutstanding(MemoryBlock* allocation);
    void collect();
    bool isAllocated(void* pPtr);
    void free(void* i_ptr);
    void printAll();
    void destroy();
    void showFreeBlocks();
    void showOutstandingBlocks();
};
