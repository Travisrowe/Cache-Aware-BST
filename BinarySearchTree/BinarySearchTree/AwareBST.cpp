#include "AwareBST.h"

//recursively find the node to delete and replace it with its successor. We must also be sure to change freeIndex to the index of the node we delete. Note the index is passed by reference so that the parent node of the deleted index is updated appropriately.
void AwareBST::AuxDelete(int &index, int v)
{
	if (index == -1)
		return; //this val is not in the tree
	else
	{
		if (v > vec[index].val)
		{
			AuxDelete(vec[index].rightChild, v);
			return; //returning here keeps us from decrementing size more than once per delete
		}
		else if (v < vec[index].val)
		{
			AuxDelete(vec[index].leftChild, v);
			return;
		}
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
	size--;
}

// Note the &.  Why is it needed here as well 
void AwareBST::AuxInsert(int& index, int v) {
	if (index == -1 || vec[index].val == -1) //the parent node pointed to a non-existent node or the index is root
	{//insert node here
		index = freeIndex; //update parent pointer to freeIndex
		vec[index].val = v;
		int newFreeIndex = vec[freeIndex].rightChild; //next free index, used to update freeIndex after insert
		size++;
		vec[freeIndex].rightChild = -1; //remove pointer to the next freeIndex
		UpdateFreeIndex(newFreeIndex);
	}
	else {
		if (v <= vec[index].val) AuxInsert(vec[index].leftChild, v);
		else AuxInsert(vec[index].rightChild, v);
	}
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

	//we set each empty node's right pointer to the next empty node in the vector
	for (int i = 0; i < size - 1; i++)
	{
		vec[i].rightChild = i + 1; //each node points to the node to its right
	}
	vec[size - 1].rightChild = -1; //the last node points to a non-existent index, -1
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
	vec[index].val = vec[index].leftChild = -1; 
	vec[index].rightChild = freeIndex; //index points right to the previous freeIndex
	freeIndex = index; //index just deleted is considered the next index to be inserted
}

int AwareBST::GetSize()
{
	return size;
}

void AwareBST::Insert(int val)
{
	AuxInsert(root, val);
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
void AwareBST::UpdateFreeIndex(int newIndex)
{
	freeIndex = newIndex;
	//if (size == vec.size()) //the number of nodes we have inserted is equal to the size of our memory unit
	//{
	//	//therefore, freeIndex is out of bounds
	//	freeIndex = size;
	//}
	//else //we have to find the freeIndex in O(n) time (although freeIndex is found in one iteration of the loop if we are only building the tree for the first time)
	//	while (freeIndex != vec.size() && vec[freeIndex].val != -1) //Null nodes have val of -1
	//		freeIndex++;
}