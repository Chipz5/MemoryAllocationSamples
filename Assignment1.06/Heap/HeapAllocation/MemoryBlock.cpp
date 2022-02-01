struct MemoryBlock {
	void* pBaseAddress; 
	size_t BlockSize; 
	struct MemoryBlock* pNextBlock;
};