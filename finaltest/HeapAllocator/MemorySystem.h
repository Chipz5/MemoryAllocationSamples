#pragma once
#include<stdint.h>
#include <vector>
#include<iostream>
#include <cassert>

#include "HeapAllocator.h"
#include "FixedSizeAllocator.h"

using namespace std;

struct FSA {
    size_t sizeBlocks;
    size_t numBlocks;
};

class MemorySystem {
    static void createHeaps();
    static void allocateForFixed(size_t num, size_t size);
public:
    static void initialise(void* heapMemory);
    static void free(void* ptr);
    static void* malloc(size_t size);
    static void collect();
    static void destroy();
};
