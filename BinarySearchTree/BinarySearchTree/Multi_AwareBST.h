#pragma once
#include <vector>
#include <iostream>
#include "MANode.h"
class Multi_AwareBST
{
	std::vector<std::vector<MANode>> vec;
	MemoryUnitTuple root = MemoryUnitTuple(0, 0);
	MemoryUnitTuple freeIndex = root; //the next index to insert into
	MemoryUnitTuple emptyTuple = MemoryUnitTuple(-1, -1);
	int size = 0; //we can use size to update freeIndex more quickly
	void AuxPrint(MemoryUnitTuple);
	//void AuxInsert(int, int);
	void AuxInsert(MemoryUnitTuple&, int);
	void AuxDelete(MemoryUnitTuple&, int);
	void DeleteNode(MemoryUnitTuple);
	void UpdateFreeIndex(MemoryUnitTuple);

public:
	Multi_AwareBST() = delete;
	Multi_AwareBST(int, int);
	~Multi_AwareBST();
	void Insert(int); //insert node with val
	void Delete(int); //Delete a Node of int val
	int GetSize();
	void Print(); //prints tree using in-order traversal
	//void PrintVec(); //prints vec vals in order of index
};

