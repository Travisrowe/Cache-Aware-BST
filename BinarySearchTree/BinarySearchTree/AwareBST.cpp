#include "AwareBST.h"

//index starts at 0
void AwareBST::AuxInsert(int v, int index)
{
	//look for a free node by comparing val to root until we find a root.child of -1
	//when we find that spot, make v[freeIndex] = val
	bool search = true;
	if (index == freeIndex) //we insert at root
	{
		search = false;
		vec[index].val = v;
	}
	while (search)
	{
		if (v < vec[index].val)
		{
			if (vec[index].leftChild == -1)
			{ //we insert at freeIndex
				vec[index].leftChild = freeIndex;
				vec[freeIndex].val = v;
			}
			else
				index = vec[index].leftChild;
		}
		else //v >= vec[index].val
		{
			if (vec[index].rightChild == -1)
			{ //we insert at freeIndex
				vec[index].rightChild = freeIndex;
				vec[freeIndex].val = v;
			}
			else
				index = vec[index].rightChild;
		}
	}
	//val has been inserted, update freeIndex
	UpdateFreeIndex();
}

AwareBST::AwareBST(int size)
{
	vec.resize(size);
}


AwareBST::~AwareBST()
{
}

void AwareBST::Delete(int val)
{
	AuxDelete(val);
}

void AwareBST::Insert(int val)
{
	AuxInsert(val);
}

//increment freeIndex until we find a node of -1
void AwareBST::UpdateFreeIndex()
{
	while (vec[freeIndex].val != -1) //Null nodes have val of -1
		freeIndex++;
}