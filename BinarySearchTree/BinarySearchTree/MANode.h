#pragma once
#include "MemoryUnitTuple.h"
class MANode
{
public:
	MemoryUnitTuple leftChild;
	int val;
	MemoryUnitTuple rightChild;
	
	MANode();
	~MANode();
};

