
#include <iostream>
#include <Windows.h>

#include <assert.h>
#include "HeapAllocator.h"

#include "HeapManager_UnitTest.h"

using namespace std;
struct Sample {
	char a; // size: 1, alignment: 1
	char b; // size: 1, alignment: 1
	float c;
	int d;
};
int main() {
	bool a = HeapManager_UnitTest();
	assert(a);
	//bottom up memory allocation
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);
	cout << "Initialising heap manager .. " << endl;
	HeapAllocator* pHeapManager = reinterpret_cast<HeapAllocator*>(HeapAllocator::Create(pHeapMemory, sizeHeap, numDescriptors));
	assert(pHeapManager);
	cout << "Storing int values" << endl;
	int* ptr;
	ptr = (int*)pHeapManager->malloc(5 * sizeof(int));
	if (!ptr) {
		cout << "Memory allocation failed"<<endl;
		return 1;
	}
	cout << "Initialising values.. " << endl;
	for (int i = 0; i < 5; i++)
	{
		ptr[i] = i;
	}
	cout << "The values are .." << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << *(ptr + i) << endl;
	}
	cout << "Storing struct values" << endl;
	Sample *s = (struct Sample*)pHeapManager->malloc(sizeof(Sample));
	cout << "Initialising values.. " << endl;
	s->a = 'a';
	s->b = 'b';
	s->c = 1.2;
	s->d = 1.453;
	cout << "The values are .." << endl;
	if (!s) {
		cout << "Memory allocation failed" << endl;
		return 1;
	}
	cout << s->a << endl;
	cout << s->b << endl;
	cout << s->c << endl;
	cout << s->d << endl;
	//pHeapManager->free(ptr);
	//pHeapManager->collect();
	//pHeapManager->printAll();
	//pHeapManager->malloc(sizeof(char));
	//pHeapManager->malloc(sizeof(float));
	//pHeapManager->malloc(sizeof(int));
	//pHeapManager->malloc(sizeof(double));

}