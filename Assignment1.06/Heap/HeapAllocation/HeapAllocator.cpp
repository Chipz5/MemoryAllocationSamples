#include "HeapAllocator.h"
    
#include <assert.h>
#include<iostream>
#include <list>

using namespace std;

    HeapAllocator* HeapAllocator::Create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks)
    {
        HeapAllocator* TheHeapAllocator = reinterpret_cast<HeapAllocator*>(i_pHeapMemory);
        i_pHeapMemory = TheHeapAllocator + 1;
        i_HeapMemorySize -= sizeof(HeapAllocator);
        cout << "Heap memory: " << i_pHeapMemory << endl;
        cout << "Heap size: " << i_HeapMemorySize << endl;
         return new HeapAllocator(i_pHeapMemory, i_HeapMemorySize, i_NumMemBlocks);
    }

    HeapAllocator::HeapAllocator(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_NumMemBlocks) {
        pFreeList = nullptr;
        pFreeMemBlocks = InitializeMemoryBlocks(i_pHeapMemory, i_NumMemBlocks * sizeof(MemoryBlock));
        
        //pOutstandingAllocations = nullptr;
        pFreeList = GetMemoryBlock();
        assert(pFreeList);
        pFreeList->pBaseAddress = reinterpret_cast<char*>(i_pHeapMemory) + (i_NumMemBlocks * sizeof(MemoryBlock));
        pFreeList->BlockSize = i_HeapMemorySize - (i_NumMemBlocks * sizeof(MemoryBlock));
        pFreeList->pNextBlock = nullptr;
        start = *pFreeList;
    }

    MemoryBlock* HeapAllocator::InitializeMemoryBlocks(void* i_pBlocksMemory, size_t i_BlocksMemorySize)
    {
        assert(i_pBlocksMemory != nullptr);
        assert(i_BlocksMemorySize > sizeof(MemoryBlock));

        pFreeList=reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
        //pOutstandingAllocations = reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
        //MemoryBlock* pCurrentBlock = reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
        const size_t numBlocks = i_BlocksMemorySize / sizeof(MemoryBlock);
        MemoryBlock* pCurrentBlock = pFreeList;

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

        return reinterpret_cast<MemoryBlock*>(i_pBlocksMemory);
    }

    MemoryBlock* HeapAllocator::GetMemoryBlock()
    {
        assert(pFreeMemBlocks != nullptr);

        MemoryBlock* pReturnBlock = pFreeMemBlocks;
        pFreeMemBlocks = pFreeMemBlocks->pNextBlock;
        return pReturnBlock;


    }

    void HeapAllocator::ReturnMemoryBlock(MemoryBlock* i_pFreeBlock)
    {
        assert(i_pFreeBlock != nullptr);

        i_pFreeBlock->pBaseAddress = nullptr;
        i_pFreeBlock->BlockSize = 0;
        i_pFreeBlock->pNextBlock = pFreeList;

        pFreeList = i_pFreeBlock;
    }

    void HeapAllocator::assignOutstanding(MemoryBlock allocation) {
        pOutstandingAllocations.insert(pOutstandingAllocations.begin(),allocation);
        //if (pOutstandingAllocations == nullptr) {
        //    cout << "INSIDE IF";
        //    MemoryBlock pBlock = allocation;
        //    //pOutstandingAllocations = GetMemoryBlock();
        //    pOutstandingAllocations->pBaseAddress = pBlock.pBaseAddress;
        //    pOutstandingAllocations->BlockSize = pBlock.BlockSize;
        //    pOutstandingAllocations->pNextBlock = nullptr;
        //   // pOutstandingAllocations = allocation;
        //   // pOutstandingAllocations.pNextBlock = nullptr;
        //   // cout << pOutstandingAllocations.pBaseAddress<<endl;
        //    //MemoryBlock pBlock = pOutstandingAllocations;
        //    /*while (pBlock.pNextBlock!=nullptr) {
        //        cout << pBlock.pBaseAddress << endl;
        //        cout << pBlock.BlockSize << endl;
        //        pBlock = pBlock.pNextBlock;
        //    }*/
        //}
        //else {
        //    cout << "INSIDE ELSE";
        //    //MemoryBlock pBlock = allocation;
        //   // cout << allocation.pBaseAddress << endl;
        //    ///pBlock.pNextBlock = &pOutstandingAllocations;
        //    //pOutstandingAllocations = pBlock;
        //    /*while (pOutstandingAllocations) {
        //        cout << pOutstandingAllocations->pBaseAddress << endl;
        //        pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
        //    }
        //    cout << "dfsfsdfsdfsdfs" << endl;
        //    MemoryBlock* pBlock = allocation;
        //    cout << allocation->pBaseAddress << endl;
        //    pBlock->pNextBlock = pOutstandingAllocations;
        //    pOutstandingAllocations = pBlock;
        //    for(int i=0;i<6;i++) {
        //        cout << pOutstandingAllocations->pBaseAddress << endl;
        //        pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
        //    }*/
        //    //pOutstandingAllocations->pNextBlock = nullptr;
        //    //cout << pOutstandingAllocations->pBaseAddress<<endl;
        //    //MemoryBlock old = *pOutstandingAllocations;
        //    //pOutstandingAllocations->pNextBlock = &allocation;
        //}
    }

    void* HeapAllocator::malloc(size_t size) {
        const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };

        const unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

        const unsigned int	alignment = alignments[index];
 
        size_t n_size = size + alignment;
        cout << "size = " << size << endl;
        cout << "alignment = " << alignment << endl;
        cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        /*MemoryBlock pBlock = pOutstandingAllocations;
        while (pBlock.pNextBlock!=nullptr) {
            cout << pBlock.pBaseAddress << endl;
            cout << pBlock.BlockSize << endl;
            pBlock = *pBlock.pNextBlock;
        }*/
        //MemoryBlock allocation = *pFreeList;
        //pFreeList = &start;
        MemoryBlock* p = pFreeList;
        while (p) {
            if (p->BlockSize > n_size)
                break;
            p = p->pNextBlock;
        }
        if (!p)
            return NULL;
        if (p->BlockSize < n_size)
            return NULL;
        cout << "Before Allocation" << endl;
        cout << "Free base address: "<< p->pBaseAddress << endl;
        cout << "Free memory size: "<< p->BlockSize << endl;
        void* endAddress = reinterpret_cast<char*>(p->pBaseAddress) + p->BlockSize;
        void* actualAddress = reinterpret_cast<char*>(endAddress) - size;
        size_t alignedAddress = (size_t)actualAddress - ((size_t)actualAddress % alignment);

        void* a = (void*)alignedAddress;
        size_t b = size + ((size_t)actualAddress % alignment);
        MemoryBlock allocation = {};
        allocation.pBaseAddress = (void*)alignedAddress;
        allocation.BlockSize = size + ((size_t)actualAddress % alignment);
        cout << "After Allocation" << endl;
        cout << "Allocated base address:"<< allocation.pBaseAddress << endl;
        cout << "Allocated block size: "<< allocation.BlockSize << endl;
        cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        /*pBlock = pOutstandingAllocations;
        while (pBlock) {
            cout << pBlock->pBaseAddress << endl;
            cout << pBlock->BlockSize << endl;
            pBlock = pBlock->pNextBlock;
        }*/
        p->BlockSize -= size + ((size_t)actualAddress % alignment);
        if (p->BlockSize == 0) {
            p->pBaseAddress = NULL;
        }

        cout << "Free base address:" << p->pBaseAddress << endl;
        cout << "Free block size: " << p->BlockSize << endl;
        HeapAllocator::assignOutstanding(allocation);
        cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        /*pBlock = pOutstandingAllocations;
        while (pBlock) {
            cout << pBlock->pBaseAddress << endl;
            cout << pBlock->BlockSize << endl;
            pBlock = pBlock->pNextBlock;
        }*/
        return allocation.pBaseAddress;
    }


    void* HeapAllocator::alloc(size_t size, unsigned int alignment) {

        size_t n_size = size + alignment;
        cout << "size = " << size << endl;
        cout << "alignment = " << alignment << endl;
        
        
        
        //changes 
        //GetMemoryBlock();
        //MemoryBlock all = *pFreeList;
        //pFreeList = &start;
        MemoryBlock* p = pFreeList;
        while (p) {
            if (p->BlockSize > n_size)
                break;
            p = p->pNextBlock;
        }
        if (!p)
            return NULL;
        if (p->BlockSize < n_size)
            return NULL;
        cout << "Before Allocation" << endl;
        cout << "Free base address: " << p->pBaseAddress << endl;
        cout << "Free memory size: " << p->BlockSize << endl;
        void* endAddress = reinterpret_cast<char*>(p->pBaseAddress) + p->BlockSize;
        void* actualAddress = reinterpret_cast<char*>(endAddress) - size;
        size_t alignedAddress = (size_t)actualAddress - ((size_t)actualAddress % alignment);

        void* a = (void*)alignedAddress;
        size_t b = size + ((size_t)actualAddress % alignment);
        MemoryBlock allocation = {};
        allocation.pBaseAddress = (void*)alignedAddress;
        allocation.BlockSize = size + ((size_t)actualAddress % alignment);
        cout << "After Allocation" << endl;
        cout << "Allocated base address:" << allocation.pBaseAddress << endl;
        cout << "Allocated block size: " << allocation.BlockSize << endl;
        cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        /*pBlock = pOutstandingAllocations;
        while (pBlock) {
            cout << pBlock->pBaseAddress << endl;
            cout << pBlock->BlockSize << endl;
            pBlock = pBlock->pNextBlock;
        }*/
        p->BlockSize -= size + ((size_t)actualAddress % alignment);
        if (p->BlockSize == 0) {
            start = *p->pNextBlock;
            p->pBaseAddress = NULL;
        }

        cout << "Free base address:" << p->pBaseAddress << endl;
        cout << "Free block size: " << p->BlockSize << endl;
        HeapAllocator::assignOutstanding(allocation);
        cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        /*pBlock = pOutstandingAllocations;
        while (pBlock) {
            cout << pBlock->pBaseAddress << endl;
            cout << pBlock->BlockSize << endl;
            pBlock = pBlock->pNextBlock;
        }*/
        return allocation.pBaseAddress;


        /*MemoryBlock allocation = *pFreeList;
        while (pFreeList) {
            if (pFreeList->BlockSize > n_size)
                break;
            pFreeList = pFreeList->pNextBlock;
        }
        if (!pFreeList)
            return NULL;
        if (pFreeList->BlockSize < n_size)
            return NULL;
        cout << "Before Allocation" << endl;
        cout << "Free base address: " << pFreeList->pBaseAddress << endl;
        cout << "Free memory size: " << pFreeList->BlockSize << endl;
        void* endAddress = reinterpret_cast<char*>(pFreeList->pBaseAddress) + pFreeList->BlockSize;
        void* actualAddress = reinterpret_cast<char*>(endAddress) - size;
        size_t alignedAddress = (size_t)actualAddress - ((size_t)actualAddress % alignment);
        allocation.pBaseAddress = (void*)alignedAddress;
        allocation.BlockSize = size + ((size_t)actualAddress % alignment);
        cout << "After Allocation" << endl;
        cout << "Allocated base address:" << allocation.pBaseAddress << endl;
        cout << "Allocated block size: " << allocation.BlockSize << endl;

        pFreeList->BlockSize -= size + ((size_t)actualAddress % alignment);
        if (pFreeList->BlockSize == 0) {
            pFreeList->pBaseAddress = NULL;
        }

        cout << "Free base address:" << pFreeList->pBaseAddress << endl;
        cout << "Free block size: " << pFreeList->BlockSize << endl;
        //HeapAllocator::assignOutstanding(allocation);
        return allocation.pBaseAddress;*/
    }

    void HeapAllocator::collect() {
        //assert(pFreeList != nullptr);
        //pFreeList = &start;
        while (pFreeList) {
            MemoryBlock* pFreeList1 = pFreeList;
            if (pFreeList->pNextBlock) {
                MemoryBlock* pFreeList2 = pFreeList->pNextBlock;
                if (reinterpret_cast<char*>(pFreeList->pBaseAddress) + pFreeList1->BlockSize == reinterpret_cast<char*>(pFreeList2->pBaseAddress)) {
                    pFreeList1->BlockSize += pFreeList2->BlockSize;
                    pFreeList1->pNextBlock = pFreeList2->pNextBlock;
                }
            }
            pFreeList = pFreeList->pNextBlock;
        }

        /*MemoryBlock*  pFreeList1 = pFreeList;
        MemoryBlock*  pFreeList2 = pFreeMemBlocks->pNextBlock;
        if (reinterpret_cast<char*>(pFreeList->pBaseAddress) + pFreeList1->BlockSize == reinterpret_cast<char*>(pFreeList2->pBaseAddress)) {
            pFreeList1->BlockSize += pFreeList2->BlockSize;
        }*/
    }


   void HeapAllocator::free(void* pPtr) {
       std::list<MemoryBlock>::iterator it;
       MemoryBlock toFree;
       //pFreeList = &start;
       MemoryBlock* p = pFreeList;
       for (it = pOutstandingAllocations.begin(); it != pOutstandingAllocations.end(); ++it) {
          
           if (it->pBaseAddress == pPtr) {
               toFree = *it;
               /*while (p->pNextBlock) {
                   p = p->pNextBlock;
               }
               p->pNextBlock = &toFree;*/
               toFree.pNextBlock = pFreeList;
               pFreeList = &toFree;
               //start = *pFreeList;
               it = pOutstandingAllocations.erase(it);
               break;
           }
       }
      // start = *pFreeList;
     /*MemoryBlock* allocations = pOutstandingAllocations;
       MemoryBlock* pBlock = pFreeList;
       while (allocations) {
           if (allocations->pBaseAddress == pPtr) {
               pBlock = allocations;
           }
           allocations = allocations->pNextBlock;
       }

        // put the block on the Freelist
        pBlock->pNextBlock=pFreeList;
        pFreeList=pBlock;*/
    }

   /*void HeapAllocator::printAll() {
       while (pOutstandingAllocations) {
           if (pOutstandingAllocations->pBaseAddress) {
               cout << pOutstandingAllocations->pBaseAddress<<endl;
           }
           pOutstandingAllocations = pOutstandingAllocations->pNextBlock;
       }
   }*/

    bool HeapAllocator::isAllocated(void* pPtr) {
        std::list<MemoryBlock>::iterator it;
        for (it = pOutstandingAllocations.begin(); it != pOutstandingAllocations.end(); ++it) {
           if(it->pBaseAddress == pPtr) {
               return true;
           }
        }
        
        return false;
    }