#pragma once
#pragma once
#include<stdint.h>
#include "HeapAllocator.h"
#include <vector>
#include "FixedSizeAllocator.h"
#include<iostream>
#include <cassert>
using namespace std;

struct FSA {
    size_t sizeBlocks;
    size_t numBlocks;
};

class MemorySystem {
public:
    static void initialise(void* pHeapMemory);
    static void allocateForFixed(HeapAllocator* pHeapManager, size_t num, size_t size);
    static void createHeaps();
    static void free(void* i_ptr);
    static void* malloc(size_t i_size);
    static void collect();
    static void destroy();
};
