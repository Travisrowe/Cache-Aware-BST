#include "Multi_AwareBST.h"

//recursively find the node to delete and replace it with its successor. We must also be sure to change freeIndex to the index of the node we delete. Note the index is passed by reference so that the parent node of the deleted index is updated appropriately.
void Multi_AwareBST::AuxDelete(MemoryUnitTuple &index, int v)
{
	if (index == emptyTuple)
		return; //this val is not in the tree
	else
	{
		if (v > vec[index.first][index.second].val)
		{
			AuxDelete(vec[index.first][index.second].rightChild, v);
			return; //returning here keeps us from decrementing size more than once per delete
		}
		else if (v < vec[index.first][index.second].val)
		{
			AuxDelete(vec[index.first][index.second].leftChild, v);
			return;
		}
		else // we have found the node to delete
		{
			if (vec[index.first][index.second].leftChild == emptyTuple && vec[index.first][index.second].rightChild == emptyTuple)
			{
				//this index is a leaf node, no children
				DeleteNode(index);
				index = emptyTuple; //update childPointer index of this node's parent
			}
			else //node has at least one child
			{
				if (vec[index.first][index.second].leftChild == emptyTuple) //no left child, only a right child
				{
					MemoryUnitTuple right = vec[index.first][index.second].rightChild;
					DeleteNode(index);
					//update index of parent to this node's right child
					index = right;
				}
				else if (vec[index.first][index.second].rightChild == emptyTuple) //only a left child exists
				{
					MemoryUnitTuple left = vec[index.first][index.second].leftChild;
					DeleteNode(index);
					//update index of parent to this node's left child
					index = left;
				}
				else //node has 2 children. We will replace with successor node
				{
					MemoryUnitTuple followerInd, leaderInd;
					followerInd = leaderInd = vec[index.first][index.second].rightChild; //go right 1 node
					if (vec[leaderInd.first][leaderInd.second].leftChild == emptyTuple) //this node is the successor
					{
						vec[leaderInd.first][leaderInd.second].leftChild = vec[index.first][index.second].leftChild;
						//vec[leaderInd].rightChild = vec[index].rightChild;
						DeleteNode(index);
						//update index of parent's child to successor
						index = leaderInd;
					}
					else
					{
						//the successor will be the left-most child of this sub-tree
						while (vec[leaderInd.first][leaderInd.second].leftChild != emptyTuple)
						{
							followerInd = leaderInd;
							leaderInd = vec[leaderInd.first][leaderInd.second].leftChild;
						}
						//leaderInd is the index of the successor
						vec[index.first][index.second].val = vec[leaderInd.first][leaderInd.second].val; //notice we only replace the val with the successor's val so that child indices do not need to be modified
						if (vec[leaderInd.first][leaderInd.second].rightChild != emptyTuple) //the successor node has a rightchild
							vec[followerInd.first][followerInd.second].leftChild = vec[leaderInd.first][leaderInd.second].rightChild;
						else //successor is a leaf, just delete it
							vec[followerInd.first][followerInd.second].leftChild = emptyTuple;
						DeleteNode(leaderInd);
					}
				}
			}
		}
	}
	size--;
}

// Note the &.  Why is it needed here as well 
void Multi_AwareBST::AuxInsert(MemoryUnitTuple& index, int v) {
	if (index == emptyTuple || vec[index.first][index.second].val == -1) //the parent node pointed to a non-existent node or the index is root
	{//insert node here
		index = freeIndex; //update parent pointer to freeIndex
		vec[index.first][index.second].val = v;
		MemoryUnitTuple newFreeIndex = vec[freeIndex.first][freeIndex.second].rightChild; //next free index, used to update freeIndex after insert
		size++;

		MemoryUnitTuple empty = MemoryUnitTuple(-1, -1);
		vec[freeIndex.first][freeIndex.second].rightChild = empty; //remove pointer to the next freeIndex
		UpdateFreeIndex(newFreeIndex);
	}
	else {
		if (v <= vec[index.first][index.second].val) AuxInsert(vec[index.first][index.second].leftChild, v);
		else AuxInsert(vec[index.first][index.second].rightChild, v);
	}
}

//Pre-order print
void Multi_AwareBST::AuxPrint(MemoryUnitTuple index)
{
	if (index == emptyTuple) //reached end of branch
		return;
	else
	{
		std::cout << vec[index.first][index.second].val << ' ';
		AuxPrint(vec[index.first][index.second].leftChild);
		AuxPrint(vec[index.first][index.second].rightChild);
	}
}

/* Creates a Multi_AwareBST (MAT) with a total number of nodes numNodes. 
 * This is comprised of one or more vectors of size sizeOfVector.
 */
Multi_AwareBST::Multi_AwareBST(int numNodes, int sizeOfVector)
{
	double numVectorsDouble = numNodes / sizeOfVector;
	int numVectors = (int)ceil(numVectorsDouble);
	vec.resize(numVectors);
	for (int i = 0; i < numVectors; i++)
		vec[i].resize(sizeOfVector);

	//we set each empty node's right pointer to the next empty node in the vector
	for (int i = 0; i < numVectors; i++)
	{
		for (int j = 0; j < sizeOfVector - 1; j++) //note the "sizeOfVector - 1" because the last node in a vector should point to the first node of the next vector
		{
			MemoryUnitTuple nextTuple = MemoryUnitTuple(i, j + 1);
			vec[i][j].rightChild = nextTuple; //each node points to the node to its right
		}
		MemoryUnitTuple nextTuple = MemoryUnitTuple(i + 1, 0);
		vec[i][sizeOfVector - 1].rightChild = nextTuple; //last node in vec points to first node in next vec
	}
	vec[numVectors - 1][sizeOfVector - 1].rightChild = emptyTuple; //the last node points to a non-existent index, -1
}

Multi_AwareBST::~Multi_AwareBST()
{
}

void Multi_AwareBST::Delete(int val)
{
	AuxDelete(root, val);
}

void Multi_AwareBST::DeleteNode(MemoryUnitTuple index)
{
	vec[index.first][index.second].val = -1; 
	vec[index.first][index.second].leftChild = emptyTuple;
	vec[index.first][index.second].rightChild = freeIndex; //index points right to the previous freeIndex
	freeIndex = index; //index just deleted is considered the next index to be inserted
}

int Multi_AwareBST::GetSize()
{
	return size;
}

void Multi_AwareBST::Insert(int val)
{
	AuxInsert(root, val);
}

//Inorder print of tree
void Multi_AwareBST::Print()
{
	AuxPrint(root); //start printing at root of tree, 0
}

////print vec's vals in order of the index where they reside
//void Multi_AwareBST::PrintVec()
//{
//	std::cout << '[';
//	for (auto i : vec)
//		std::cout << i.val << ", ";
//	std::cout << ']';
//}

//increment freeIndex until we find a node of -1
void Multi_AwareBST::UpdateFreeIndex(MemoryUnitTuple newIndex)
{
	freeIndex = newIndex;
}
