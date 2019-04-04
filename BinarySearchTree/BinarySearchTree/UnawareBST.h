#pragma once

//UnawareBST.h
#pragma once
#include <iostream>
#include <math.h> // for natural log
using namespace std;
class UnawareBST
{
	// PRIVATE vars
	struct Node {
		int val;
		Node * left;
		Node * right;

		//Here is a constructor that works with a struct as we discussed.
		Node(int v) { val = v; left = right = 0; } // Node constructor!
	};
	Node * root;
	void AuxInsert(Node *&, int);
	void AuxDelete(Node *&, int);
	void AuxGetSize(Node *, int&);
	void AuxPrint(Node *);
	void RemoveTree(Node *& r);

public:
	UnawareBST(void);//Constructor
	~UnawareBST(void);//Desructor
	void Insert(int v);//Insert v into the tree
	void Delete(int val);//Delete val from the tree
	int GetSize();
	void Print();//Can you change this to have a parameter
				 // Print(PREORDER), Print(INORDER) and Print(Postorder) ?
				 // PREORDER etc enums
};

