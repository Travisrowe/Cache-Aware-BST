#include "AwareBST.h"

//recursively find the node to delete and replace it with its successor. We must also be sure to change freeIndex to the index of the node we delete
void AwareBST::AuxDelete(int &index, int v)
{
	if (index == -1)
		return; //this val is not in the tree
	else
	{
		if (v > vec[index].val)
			AuxDelete(vec[index].rightChild, v);
		else if (v < vec[index].val)
			AuxDelete(vec[index].leftChild, v);
		else // we have found the node to delete
		{
			if (vec[index].leftChild == vec[index].rightChild == -1)
			{
				//this index is a leaf node, no children
				DeleteNode(index);
				index = -1; //update childPointer index of this node's parent
			}
			else //node has at least one child
			{
				if (vec[index].leftChild == -1) //no left child, only a right child
				{
					int right = vec[index].rightChild;
					DeleteNode(index);
					//update index of parent to this node's right child
					index = right;
				}
				else if (vec[index].rightChild == -1) //only a left child exists
				{
					int left = vec[index].leftChild;
					DeleteNode(index);
					//update index of parent to this node's left child
					index = left;
				}
				else //node has 2 children. We will replace with successor node
				{
					int followerInd, leaderInd;
					followerInd = leaderInd = vec[index].rightChild; //go right 1 node
					if (vec[leaderInd].leftChild == -1) //this node is the successor
					{
						vec[leaderInd].leftChild = vec[index].leftChild;
						//vec[leaderInd].rightChild = vec[index].rightChild;
						DeleteNode(index);
						//update index of parent's child to successor
						index = leaderInd;
						return;
					}
					else
					{
						//the successor will be the left-most child of this sub-tree
						while (vec[leaderInd].leftChild != -1)
						{
							followerInd = leaderInd;
							leaderInd = vec[leaderInd].leftChild;
						}
						//leaderInd is the index of the successor
						vec[index].val = vec[leaderInd].val; //notice we only replace the val with the successor's val so that child indices do not need to be modified
						if (vec[leaderInd].rightChild != -1) //the successor node has a rightchild
							vec[followerInd].leftChild = vec[leaderInd].rightChild;
						else //successor is a leaf, just delete it
							vec[followerInd].leftChild = -1;
						DeleteNode(leaderInd);
					}
				}
			}
		}
	}
}

void AwareBST::AuxGetSize(int index, int& size)
{
	if (index == -1) //reached end of branch
		return;
	else
	{
		size++;
		AuxGetSize(vec[index].leftChild, size);
		AuxGetSize(vec[index].rightChild, size);
	}
}

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
				search = false;
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
				search = false;
			}
			else
				index = vec[index].rightChild;
		}
	}
	//val has been inserted, update freeIndex
	UpdateFreeIndex();
}

//Pre-order print
void AwareBST::AuxPrint(int index)
{
	if (index == -1) //reached end of branch
		return;
	else
	{
		std::cout << vec[index].val << ' ';
		AuxPrint(vec[index].leftChild);
		AuxPrint(vec[index].rightChild);
	}
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
	AuxDelete(root, val);
}

void AwareBST::DeleteNode(int index)
{
	vec[index].val = vec[index].leftChild = vec[index].rightChild = -1;
	if (index < freeIndex)
		freeIndex = index;
}

int AwareBST::GetSize()
{
	int size = 0;
	AuxGetSize(root, size);
	return size;
}

void AwareBST::Insert(int val)
{
	AuxInsert(val, root);
}

//Inorder print of tree
void AwareBST::Print()
{
	AuxPrint(root); //start printing at root of tree, 0
}

//print vec's vals in order of the index where they reside
void AwareBST::PrintVec()
{
	std::cout << '[';
	for (auto i : vec)
		std::cout << i.val << ", ";
	std::cout << ']';
}

//increment freeIndex until we find a node of -1
void AwareBST::UpdateFreeIndex()
{
	while (freeIndex != vec.size() && vec[freeIndex].val != -1) //Null nodes have val of -1
		freeIndex++;
}