#include "MemoryUnitTuple.h"



bool MemoryUnitTuple::operator==(const MemoryUnitTuple &A)
{
	return this->first == A.first && this->second == A.second;
}

bool MemoryUnitTuple::operator!=(const MemoryUnitTuple &A)
{
	return !operator==(A);
}

MemoryUnitTuple::MemoryUnitTuple()
{
	first = -1;
	second = -1;
}

MemoryUnitTuple::MemoryUnitTuple(int f, int s)
{
	first = f;
	second = s;
}


MemoryUnitTuple::~MemoryUnitTuple()
{
}
