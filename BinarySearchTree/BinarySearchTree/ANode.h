#pragma once
class ANode
{
	//Here we use Node like a struct. All public vars and functions
public:
	int val;
	int leftChild; //index of left child
	int rightChild; //index of right child
	ANode();
	ANode(int, int = -1, int = -1);
	~ANode();
};

