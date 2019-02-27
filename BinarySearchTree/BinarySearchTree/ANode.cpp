#include "ANode.h"

ANode::ANode()
{
	//null Nodes have val of -1
	val = leftChild = rightChild = -1;
}

ANode::ANode(int v, int leftCh, int rightCh)
{
	val = v;
	leftChild = leftCh;
	rightChild = rightCh;
}

ANode::~ANode()
{
}