#include "MANode.h"

MANode::MANode()
{
	MemoryUnitTuple defaultPtr; //(-1, -1)
	leftChild = rightChild = defaultPtr;
	val = -1;
}


MANode::~MANode()
{
}
