#include "AwareBST.h"
#include "UnawareBST.h"
#include <algorithm>
#include <time.h>
#include <iostream>
//chrono used for time measurements
#include <chrono> 
using namespace std::chrono;

//L2CacheSize  L3CacheSize
//512 kb       3072 kb
//524,288 bytes
//12 bytes per Node
// 524,288 / 12 = 43,690 Nodes

#define NUM_NODES 43690 //number of nodes
#define ID_PAIRS 100000 //number of insert/delete pairs
#define SEED 99
//#define DEBUG true
//#define FIND_SEED true

//swap index a with index b inside vect
void Swap(vector<int> &vect, int a, int b)
{
	int temp = vect[a];
	vect[a] = vect[b];
	vect[b] = temp;
}

int main()
{
#ifdef FIND_SEED
	int closestVal = NUM_NODES;
	int closestSeed;
	for (int i = 0; i < 100; i++)
	{
		srand(i);
		int difference = abs((int)(NUM_NODES / 2) - rand() % NUM_NODES);
		if (difference < closestVal)
		{
			closestVal = difference;
			closestSeed = i;
		}
	}
	cout << "Seed: " << closestSeed << "val: " << closestVal << '\n';
#endif // SEED

#ifdef DEBUG

	srand(SEED);

	AwareBST AT(NUM_NODES);
	UnawareBST UT;

	//the vector we will select vals from
	std::vector<int> insDelSelector(NUM_NODES);

	//fill insDelSelector with values 0 to NUM_NODES - 1
	for (int i = 0; i < NUM_NODES; i++)
		insDelSelector[i] = i; 

	//use the Yates Shuffle technique to randomly select vals from insDelSelector
	for (int i = 0; i < NUM_NODES; i++)
	{
		//notice that we select from NUM_NODES - i because we treat the last i digits of the vector as a dead zone
		int r;
		if (i != NUM_NODES - 1) //otherwise we divide by 0
			r = rand() % (NUM_NODES - i - 1);
		else
			r = 0;
		int val = insDelSelector[r];

		//we now have the random value to insert
		AT.Insert(val);
		UT.Insert(val);

		//we put the val we just selected on the end of the vector so we don't select it again
		Swap(insDelSelector, r, NUM_NODES - i - 1);
	} //our trees are built with values 0 - NUM_NODES in random order
	std::cout << "\nAT\n";
	AT.Print();
	std::cout << "\nUT\n";
	UT.Print();


	cout << endl;

	for (int i = 0; i < ID_PAIRS; i++)
	{
		int r = rand() % NUM_NODES;
		int val = insDelSelector[r];
		AT.Delete(val);
		UT.Delete(val);
		/*std::cout << "i: " << i << '\n';
		std::cout << "\nUT Size: " << UT.GetSize() << '\n';
		if (val == 45)
		{
			std::cout << "\nAT\n";
			AT.Print();
			std::cout << "\nAT Size: " << AT.GetSize() << '\n';
			std::cout << "\nUT\n";
			UT.Print();
			std::cout << "\nUT Size: " << UT.GetSize() << '\n';
		}*/

		//now we insert a new node into the tree. 
		int randVal = (rand() % NUM_NODES);
		insDelSelector[r] = randVal; //replace the deleted val with the new val in the selector
		AT.Insert(randVal);
		UT.Insert(randVal);
	}
	

	std::cout << "\nAT\n";
	AT.Print();
	std::cout << "\nUT\n";
	UT.Print();

#else// Time-test program
	srand(SEED);
	
	std::cout << "Let's begin!\n\n";
	std::cout << "Generating initial values for trees and insert/delete pairs....\n";
	vector<int> initialTreeVals(NUM_NODES); //vals the tree has inserted initially
	vector<int> treeVals(NUM_NODES); //vals the tree has "currently" these are used to select Nodes to delete
	for (int i = 0; i < NUM_NODES; i++)
	{
		initialTreeVals[i] = treeVals[i] = rand() % NUM_NODES;
	}
	vector<int> InsertVals(ID_PAIRS);
	vector<int> DeleteVals(ID_PAIRS);
	for (int i = 0; i < ID_PAIRS; i++)
	{
		//get index to delete, then replaces with new val
		int index = rand() % NUM_NODES;
		//store the val to delete
		DeleteVals[i] = treeVals[index];
		//generate new val to insert
		InsertVals[i] = rand() % NUM_NODES;
		//replace "deleted" val with "inserted" val
		treeVals[index] = InsertVals[i];
	}
	std::cout << "Finished generating random vals!\n";
	std::cout << "Starting time for Control tree (Cache-unaware BST)....\n";

	/****************************************************************************
	 * Unaware BST timing *******************************************************
	****************************************************************************/
	auto start = high_resolution_clock::now(); //start time

	UnawareBST UT;
	//create initial tree
	for (int i = 0; i < NUM_NODES; i++)
	{
		UT.Insert(initialTreeVals[i]);
	}
	for (int i = 0; i < ID_PAIRS; i++)
	{
		//delete first, then insert
		UT.Delete(DeleteVals[i]);
		UT.Insert(InsertVals[i]);
	}

	auto stop = high_resolution_clock::now(); //stop time

	// Subtract stop and start timepoints and 
	// cast it to required unit. Predefined units 
	// are nanoseconds, microseconds, milliseconds, 
	// seconds, minutes, hours. Use duration_cast() 
	// function. 
	auto duration = duration_cast<microseconds>(stop - start);

	// To get the value of duration use the count() 
	// member function on the duration object 
	cout << "Time for Control tree: " << duration.count() << "microseconds\n";

	/****************************************************************************
	 * Single Vector Aware BST timing *******************************************
	****************************************************************************/
	std::cout << "Starting time for single vector tree...\n";
	auto start_AT = high_resolution_clock::now(); //start time

	AwareBST AT(NUM_NODES);
	//create initial tree
	for (int i = 0; i < NUM_NODES; i++)
	{
		if (i % 1000 == 0)
			cout << i << '\n';
		AT.Insert(initialTreeVals[i]);
	}
	for (int i = 0; i < ID_PAIRS; i++)
	{
		if (i % 100 == 0)
			cout << i << '\n';
		//delete first, then insert
		AT.Delete(DeleteVals[i]);
		AT.Insert(InsertVals[i]);
	}

	auto stop_AT = high_resolution_clock::now(); //stop time

	// Subtract stop and start timepoints and 
	// cast it to required unit. Predefined units 
	// are nanoseconds, microseconds, milliseconds, 
	// seconds, minutes, hours. Use duration_cast() 
	// function. 
	auto duration_AT = duration_cast<microseconds>(stop_AT - start_AT);

	// To get the value of duration use the count() 
	// member function on the duration object 
	cout << "Time for Single-Vector, Aware tree: " << duration_AT.count() << "microseconds\n";
#endif // Debug

}