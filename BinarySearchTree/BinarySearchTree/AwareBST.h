#pragma once
#include "ANode.h"
#include <vector>
#include <iostream>
class AwareBST
{
	std::vector<ANode> vec;
	int freeIndex = 0; //the next index to insert into
	void AuxInsert(int, int = 0);
	void AuxDelete(int, int = 0);
	void UpdateFreeIndex();

public:
	AwareBST() = delete;
	AwareBST(int);
	~AwareBST();
	void Insert(int); //insert node with val
	void Delete(int); //Delete a Node of int val
	void Print();
};

