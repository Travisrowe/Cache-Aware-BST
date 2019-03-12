#pragma once
#include "ANode.h"
#include <vector>
#include <iostream>
class AwareBST
{
	std::vector<ANode> vec;
	int root = 0;
	int freeIndex = 0; //the next index to insert into
	void AuxPrint(int);
	void AuxInsert(int, int);
	void AuxGetSize(int, int&);
	void AuxDelete(int&, int);
	void DeleteNode(int);
	void UpdateFreeIndex();

public:
	AwareBST() = delete;
	AwareBST(int);
	~AwareBST();
	void Insert(int); //insert node with val
	void Delete(int); //Delete a Node of int val
	int GetSize();
	void Print(); //prints tree using in-order traversal
	void PrintVec(); //prints vec vals in order of index
};

