//UnawareBST.cpp
#include "UnawareBST.h"
#include "UNode.h"
//constructor
UnawareBST::UnawareBST(void)
{
	root = 0;
}

// This is the destructor.  When does it get called.
// There are several places of interest
UnawareBST::~UnawareBST(void)
{
	RemoveTree(root);
}

// Note the & .  Why is it needed
void UnawareBST::RemoveTree(Node *& r) {//Inorder deletion of entire UnawareBST;
	if (r == 0)return;
	else {
		RemoveTree(r->left);
		RemoveTree(r->right);
		delete r;
		r = 0;
	}
}

// Note the &.  Why is it needed here as well 
void UnawareBST::AuxInsert(Node *& r, int v) {
	if (r == 0) {//insert node here
		r = new Node(v);
	}
	else {
		if (v <= r->val) AuxInsert(r->left, v);
		else AuxInsert(r->right, v);
	}
}

//Public method to insert a node into the tree
void UnawareBST::Insert(int v)
{
	AuxInsert(root, v);
}

// Private recursive method to print the tree
void UnawareBST::AuxPrint(Node * r) {//Preorder
	if (r == 0)return;
	else {
		cout << r->val << " ";
		AuxPrint(r->left);
		AuxPrint(r->right);
	}
}

void UnawareBST::AuxGetSize(Node * r, int &size)
{
	if (r == 0)return;
	else {
		size++;
		AuxGetSize(r->left, size);
		AuxGetSize(r->right, size);
	}
}

int UnawareBST::GetSize()
{
	int size = 0; 
	AuxGetSize(root, size);
	return size;
}

//Public print method
void UnawareBST::Print() {
	AuxPrint(root);
	cout << endl << endl;
}

//Public Delete method
void UnawareBST::Delete(int val)
{
	AuxDelete(root, val);
}


//The recursive successor delete for the public Delete() method
void UnawareBST::AuxDelete(Node *&r, int v)
{
	if (r == NULL) return;
	else {// lets keep looking
		if (v > r->val) {
			AuxDelete(r->right, v);
		}
		else if (v < r->val) {
			AuxDelete(r->left, v);
		}
		else {// We have found the node to delete
			if (r->left == NULL && r->right == NULL) {// r has no children
				delete r;// just delete it
				r = NULL;
				return;
			}
			else {//found the node with at least one child
				Node * ptr;
				if (r->left == NULL)// no left child but a right exists
				{
					Node* temp = r->right;
					delete r;
					r = temp;
					return;
				}
				else if (r->right == NULL)// left child but no right child.
				{// 
					Node* temp = r->left;
					delete r;
					r = temp;
					return;
				}
				else { // we have 2 children. Will replace with successor node
					Node * follower;
					ptr = r->right;// go right 1 node
					follower = ptr;
					if (ptr->left == NULL) {//splice out ptr
						r->right = ptr->right;
						r->val = ptr->val;
						delete ptr;
						return;
					}
					// we have a left node so
					while (ptr->left != 0) {// and then go left as far as you can go
						follower = ptr;
						ptr = ptr->left;
					}
					// Ptr points to successor. 
					// Move contents of successor to the root of the subtree
					// being examined and delete the successor node.
					r->val = ptr->val;
					// does this successor have a right node
					if (ptr->right != NULL) {
						follower->left = ptr->right;
						delete ptr; // delete sucessor
					}
					else {
						follower->left = NULL;
						delete ptr; // delete sucessor
					}
				}

			}
		}
	}
	return;
}