#pragma once
class UNode
{
public:
	int val;
	UNode *left;
	UNode *right;
	UNode() = delete;
	UNode(int);
	~UNode();
};

