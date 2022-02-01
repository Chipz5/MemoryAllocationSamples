#include "MemorySystem_UnitTest.h"
#include "HeapManager_UnitTest.h"
using namespace std;
struct Sample {
	char a; // size: 1, alignment: 1
	char b; // size: 1, alignment: 1
	double c;
	int d;
};

int main() {
	bool memSys = MemorySystem_UnitTest();
	assert(memSys);

	bool heapMan = HeapManager_UnitTest();
	assert(heapMan);
	//bottom up memory allocation
	const size_t 		sizeHeap = 1024 * 1024;
	const uint16_t  	numDescriptors = 2048;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);

	cout << "Initialising heap manager .. " << endl;
	HeapAllocator* pHeapManager = HeapAllocator::create(pHeapMemory, sizeHeap, numDescriptors);
	assert(pHeapManager);

	uint16_t  alignment;
	cout << "Enter the alignment value. Choose between 4,8,16,32 or 64" << endl;
	cin >> alignment;
	if (alignment > 64 || alignment % 4 != 0) {
		cout << "Wrong alignment given. Choosing default alignment value 4" <<endl;
		alignment = 4;
	}
	cout << "Storing int values" << endl;
	intptr_t* ptr;
	ptr = (intptr_t*)pHeapManager->alloc(5 * sizeof(intptr_t), alignment);
	if (!ptr) {
		cout << "Memory allocation failed" << endl;
		return 1;
	}
	cout << "Initialising values.. " << endl;
	for (uint8_t i = 0; i < 5; i++)
	{
		ptr[i] = i;
	}
	cout << "The values are .." << endl;
	for (uint8_t i = 0; i < 5; i++)
	{
		cout << *(ptr + i) << endl;
	}
	cout << "Storing struct values" << endl;
	Sample* s = (struct Sample*)pHeapManager->alloc(sizeof(Sample), alignment);
	cout << "Initialising values.. " << endl;
	s->a = 'a';
	s->b = 'b';
	s->c = 1.2;
	s->d = 1;
	cout << "The values are .." << endl;
	if (!s) {
		cout << "Memory allocation failed" << endl;
		return 1;
	}
	cout << s->a << endl;
	cout << s->b << endl;
	cout << s->c << endl;
	cout << s->d << endl;
	cout << "Is allocated? " << pHeapManager->isAllocated(ptr) << endl;
	cout << "Is allocated? " << pHeapManager->isAllocated(s);
	pHeapManager->free(s);
	pHeapManager->free(ptr);

	pHeapManager->collect();
	pHeapManager->destroy();
	pHeapManager->~HeapAllocator();

	HeapFree(GetProcessHeap(), 0, pHeapMemory);

	return 0;
}