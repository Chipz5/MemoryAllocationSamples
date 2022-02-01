#include "BitArray.h"

BitArray::BitArray(size_t numBits, bool initToZeroes, HeapAllocator* heapManager) :
	heapManager(heapManager)
{
	numElements = numBits / bitsPerElement;
	bits = static_cast<t_BitData*>(heapManager->alloc(numElements * sizeof(t_BitData), 4));
	assert(bits);
	memset(bits, initToZeroes ? 0x00 : 0xFF, numElements * sizeof(t_BitData));
	setAll();
}

BitArray::~BitArray() {
	heapManager->free(bits);
}

BitArray* BitArray::createBitArray(size_t numBits, bool startClear, HeapAllocator* heapManager) {
	BitArray* pBitArray = static_cast<BitArray*>(heapManager->alloc(sizeof(BitArray), 4));
	return new (pBitArray) BitArray(numBits, startClear, heapManager);
}

void BitArray::clearAll() {
	for (size_t i = 0; i < numElements; i++) {
		bits[i] = bits[i] & t_BitData(0);
	}
}

void BitArray::setAll() {
	for (size_t i = 0; i < numElements; i++) {
		cout << bits[i] << endl;
		cout << t_BitData(0) << endl;
		cout << ~(bits[i] & t_BitData(0)) << endl;
		bits[i] = ~(bits[i] & t_BitData(0));
	}
}

bool BitArray::areAllBitsClear() const {
	for (size_t i = 0; i < numElements; i++) {
		if (bits[i] != t_BitData(0)) return false;
	}
	return true;
}

bool BitArray::areAllBitsSet() const {
	bool result = false;
	for (size_t i = 0; i < numElements; i++) {
		t_BitData Bits = bits[i];
		if (Bits == t_BitData(0)) return false;
		if (((Bits + 1) & Bits) != 0) return false;
		else result = true;
	}
	return result;
}

bool BitArray::isBitSet(size_t bitIndex) const {
	assert(bitIndex < numElements* bitsPerElement);
	cout << "Inside isbitset " << (*this)[bitIndex] << endl;
	return (*this)[bitIndex];
}

void BitArray::clearBit(size_t bitIndex) {
	assert(bitIndex < numElements* bitsPerElement);
	size_t elementIndex = bitIndex / bitsPerElement;
	size_t bitIndexInElement = bitIndex % bitsPerElement;
	cout << "value of element at index " << bits[elementIndex] << endl;
	cout << "val " << ~(t_BitData(1) << bitIndexInElement) << endl;
	bits[elementIndex] &= ~(t_BitData(1) << bitIndexInElement);
	cout << "value of element at index " << bits[elementIndex] << endl;
	cout << "Val" << endl;
	for (size_t i = 0; i < 100; i++) {
		std::cout << (bits)[i];
	}
}

void BitArray::setBit(size_t bitIndex) {
	assert(bitIndex < numElements* bitsPerElement);
	size_t elementIndex = bitIndex / bitsPerElement;
	size_t bitIndexInElement = bitIndex % bitsPerElement;
	bits[elementIndex] |= (t_BitData(1) << bitIndexInElement);
	cout << "Val" << endl;
	for (size_t i = 0; i < 100; i++) {
		std::cout << (bits)[i];
	}
}

bool BitArray::findFirstClearBit(size_t& firstSetBitIndex) const {
	return true;
}

bool BitArray::findFirstSetBit(size_t& firstSetBitIndex) const {
	size_t elementIndex = 0;
	// skip the bytes where no bits are set
	while ((bits[elementIndex] == t_BitData(0)) && (elementIndex < numElements))
		elementIndex++;
	t_BitData Bits = bits[elementIndex];
	unsigned long bitIndexInElement;
	unsigned char nonZeroFound;
#ifdef _WIN64
	nonZeroFound = _BitScanForward64(&bitIndexInElement, Bits);
#else
	nonZeroFound = _BitScanForward(&bitIndexInElement, Bits);
#endif
	if (nonZeroFound) {
		// now we have the byte index, and the bit index within that byte
		firstSetBitIndex = (elementIndex * bitsPerElement) + bitIndexInElement;
		if (firstSetBitIndex >= bitsPerElement * numElements)
			return false;
		else
			return true;
	}
	else {
		cout << "No set bits found at " << elementIndex  << endl;
		return false;
	}
}

bool BitArray::operator[](size_t i_bitIndex) const {
	assert(i_bitIndex < numElements* bitsPerElement);
	size_t elementIndex = i_bitIndex / bitsPerElement;
	t_BitData Bits = bits[elementIndex];
	size_t bitIndexInElement = i_bitIndex % bitsPerElement;
	size_t bit = (Bits >> bitIndexInElement) & t_BitData(1);
	return (bit == 1);
}