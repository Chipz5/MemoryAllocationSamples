#include "BitArray.h"


BitArray::BitArray(size_t i_numBits, bool i_initToZeroes, HeapAllocator* i_pHeapManager) :
	m_pHeapManager(i_pHeapManager)
{
	m_numElements = i_numBits / bitsPerElement;
	m_pBits = static_cast<t_BitData*>(i_pHeapManager->alloc(m_numElements * sizeof(t_BitData), 4));
	assert(m_pBits);
	memset(m_pBits, i_initToZeroes ? 0x00 : 0xFF, m_numElements * sizeof(t_BitData));
	cout << m_pBits << endl;
	SetAll();
	//ClearAll();
}

BitArray::~BitArray() {
	m_pHeapManager->free(m_pBits);
}

BitArray* BitArray::CreateBitArray(size_t i_numBits, bool i_startClear, HeapAllocator* i_pHeapManager) {
	BitArray* pBitArray = static_cast<BitArray*>(i_pHeapManager->alloc(sizeof(BitArray), 4));
	return new (pBitArray) BitArray(i_numBits, i_startClear, i_pHeapManager);
}

void BitArray::ClearAll() {
	for (size_t i = 0; i < m_numElements; i++) {
		m_pBits[i] = m_pBits[i] & t_BitData(0);
	}
}

void BitArray::SetAll() {
	for (size_t i = 0; i < m_numElements; i++) {
		cout << m_pBits[i] << endl;
		cout << t_BitData(0) << endl;
		cout << ~(m_pBits[i] & t_BitData(0)) << endl;
		m_pBits[i] = ~(m_pBits[i] & t_BitData(0));
	}
	cout << "VAAAL" << endl;
	for (size_t i = 0; i < 100; i++) {
		std::cout << (m_pBits)[i];
	}
}

bool BitArray::AreAllBitsClear() const {
	for (size_t i = 0; i < m_numElements; i++) {
		if (m_pBits[i] != t_BitData(0)) return false;
	}
	return true;
}

bool BitArray::AreAllBitsSet() const {
	bool result = false;
	for (size_t i = 0; i < m_numElements; i++) {
		t_BitData Bits = m_pBits[i];
		if (Bits == t_BitData(0)) return false;
		if (((Bits + 1) & Bits) != 0) return false;
		else result = true;
	}
	return result;
}

bool BitArray::IsBitSet(size_t i_bitIndex) const {
	assert(i_bitIndex < m_numElements* bitsPerElement);
	cout << "Inside isbitset " << (*this)[i_bitIndex] << endl;
	return (*this)[i_bitIndex];
}

void BitArray::ClearBit(size_t i_bitIndex) {
	assert(i_bitIndex < m_numElements* bitsPerElement);
	size_t elementIndex = i_bitIndex / bitsPerElement;
	size_t bitIndexInElement = i_bitIndex % bitsPerElement;
	cout << "val of element at index " << m_pBits[elementIndex] << endl;
	cout << "val " << ~(t_BitData(1) << bitIndexInElement) << endl;
	m_pBits[elementIndex] &= ~(t_BitData(1) << bitIndexInElement);
	cout << "val of element at index " << m_pBits[elementIndex] << endl;
	cout << "VAAAL" << endl;
	for (size_t i = 0; i < 100; i++) {
		std::cout << (m_pBits)[i];
	}
}

void BitArray::SetBit(size_t i_bitIndex) {
	assert(i_bitIndex < m_numElements* bitsPerElement);
	size_t elementIndex = i_bitIndex / bitsPerElement;
	size_t bitIndexInElement = i_bitIndex % bitsPerElement;
	m_pBits[elementIndex] |= (t_BitData(1) << bitIndexInElement);
	cout << "VAAAL" << endl;
	for (size_t i = 0; i < 100; i++) {
		std::cout << (m_pBits)[i];
	}
}

bool BitArray::FindFirstClearBit(size_t& o_firstSetBitIndex) const {
	return true;
}

bool BitArray::FindFirstSetBit(size_t& o_firstSetBitIndex) const {
	size_t elementIndex = 0;
	// skip the bytes where no bits are set
	while ((m_pBits[elementIndex] == t_BitData(0)) && (elementIndex < m_numElements))
		elementIndex++;
	t_BitData Bits = m_pBits[elementIndex];
	unsigned long bitIndexInElement;
	unsigned char nonZeroFound;
#ifdef _WIN64
	nonZeroFound = _BitScanForward64(&bitIndexInElement, Bits);
#else
	nonZeroFound = _BitScanForward(&bitIndexInElement, Bits);
#endif
	if (nonZeroFound) {
		// now we have the byte index, and the bit index within that byte
		o_firstSetBitIndex = (elementIndex * bitsPerElement) + bitIndexInElement;
		if (o_firstSetBitIndex >= bitsPerElement * m_numElements)
			return false;
		else
			return true;
	}
	else {
		cout << "No set bits found. m_pBits[" << elementIndex << "] is zero." << endl;
		return false;
	}
}

bool BitArray::operator[](size_t i_bitIndex) const {
	assert(i_bitIndex < m_numElements* bitsPerElement);
	size_t elementIndex = i_bitIndex / bitsPerElement;
	t_BitData Bits = m_pBits[elementIndex];
	size_t bitIndexInElement = i_bitIndex % bitsPerElement;
	size_t bit = (Bits >> bitIndexInElement) & t_BitData(1);
	return (bit == 1);
}