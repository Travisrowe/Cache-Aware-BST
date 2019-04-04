#include "AwareBST.h"
#include "UnawareBST.h"
#include "Multi_AwareBST.h"
#include <algorithm>
#include <time.h>
#include <iostream>
//#include <fstream> //for outfile
#include <Windows.h> //for sleep
//chrono used for time measurements
#include <chrono> 
using namespace std::chrono;



#define MODIFIER 100000
//#define NUM_NODES 256 //number of nodes
#define ID_PAIRS 1000000 //number of insert/delete pairs
#define SEED 99
#define SIZE_MULTIVECS 128 //size of vectors in Multi-Aware BST

//#define DEBUG true
#define TIME_TEST true
//#define FIND_SEED true
//#define TIME_TEST_NO_VECS true

//swap index a with index b inside vect
void Swap(vector<int> &vect, int a, int b)
{
	int temp = vect[a];
	vect[a] = vect[b];
	vect[b] = temp;
}

int main()
{
	srand(SEED);
#ifdef FIND_SEED
	int closestVal = MODIFIER;
	int closestSeed;
	for (int i = 0; i < 100; i++)
	{
		srand(i);
		int difference = abs((int)(MODIFIER / 2) - rand() % MODIFIER);
		if (difference < closestVal)
		{
			closestVal = difference;
			closestSeed = i;
		}
	}
	cout << "Seed: " << closestSeed << "val: " << closestVal << '\n';
#endif // SEED

#ifdef DEBUG

	AwareBST AT(NUM_NODES);
	UnawareBST UT;
	Multi_AwareBST MAT(NUM_NODES, SIZE_MULTIVECS);

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
		MAT.Insert(val);

		//we put the val we just selected on the end of the vector so we don't select it again
		Swap(insDelSelector, r, NUM_NODES - i - 1);
	} //our trees are built with values 0 - NUM_NODES in random order
	std::cout << "\nAT\n";
	AT.Print();
	std::cout << "\nUT\n";
	UT.Print();
	std::cout << "\nMAT\n";
	MAT.Print();


	cout << endl;

	for (int i = 0; i < ID_PAIRS; i++)
	{
		int r = rand() % NUM_NODES;
		int val = insDelSelector[r];
		AT.Delete(val);
		UT.Delete(val);
		MAT.Delete(val);
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
		MAT.Insert(randVal);
	}
	

	std::cout << "\nAT\n";
	AT.Print();
	std::cout << "\nUT\n";
	UT.Print();
	std::cout << "\nMAT\n";
	MAT.Print();

#endif //DEBUG
#ifdef TIME_TEST


	// Time-test program
	cout << "NUM_NODES\tUT Average\tAT Average\tMAT Average\tAll time in microseconds\n";
	for (int k = 1; k <= 15; k++)
	{
		srand(SEED);
		int pow = 1;
		for (int x = 0; x < k; x++)
			pow *= 2;
		int NUM_NODES = pow;
		int mutliVecSize = NUM_NODES / 2;
		//std::cout << "Let's begin!\n\n";
		//std::cout << "Generating initial values for trees and insert/delete pairs....\n";
		vector<int> initialTreeVals(NUM_NODES); //vals the tree has inserted initially
		vector<int> treeVals(NUM_NODES); //vals the tree has "currently" these are used to select Nodes to delete
		for (int i = 0; i < NUM_NODES; i++)
		{
			initialTreeVals[i] = treeVals[i] = rand() % MODIFIER;
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
			InsertVals[i] = rand() % MODIFIER;
			//replace "deleted" val with "inserted" val
			treeVals[index] = InsertVals[i];
		}
		//std::cout << "Finished generating random vals!\n";
		double durSumAT = 0;
		double durSumUT = 0;
		double durSumMAT = 0;
		for (int j = 0; j < 10; j++)
		{
			//std::cout << "Starting time for Control tree (Cache-unaware BST)....\n";

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
			auto duration = duration_cast<microseconds>(stop - start);  //1 second is 1,000,000 microseconds (654,773 microseconds is .654 seconds)
			durSumUT += duration.count();

			// To get the value of duration use the count() 
			// member function on the duration object 
			//cout << "Time for Control tree: " << duration.count() << " microseconds\n\n";

			/****************************************************************************
			 * Single Vector Aware BST timing *******************************************
			****************************************************************************/
			//std::cout << "Starting time for single vector tree...\n";
			auto start_AT = high_resolution_clock::now(); //start time

			AwareBST AT(NUM_NODES);
			//create initial tree
			for (int i = 0; i < NUM_NODES; i++)
			{
				/*if (i % 1000 == 0)
					cout << i << '\n';*/
				AT.Insert(initialTreeVals[i]);
			}
			for (int i = 0; i < ID_PAIRS; i++)
			{
				/*if (i % 100 == 0)
					cout << i << '\n';*/
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
			durSumAT += duration_AT.count();

			// To get the value of duration use the count() 
			// member function on the duration object 
			//cout << "Time for Single-Vector, Aware tree: " << duration_AT.count() << " microseconds\n\n";

			/****************************************************************************
			 * Multi-Vector BST timing **************************************************
			****************************************************************************/
			auto start_MAT = high_resolution_clock::now(); //start time

			Multi_AwareBST MAT(NUM_NODES, mutliVecSize);
			//create initial tree
			for (int i = 0; i < NUM_NODES; i++)
			{
				MAT.Insert(initialTreeVals[i]);
			}
			for (int i = 0; i < ID_PAIRS; i++)
			{
				//delete first, then insert
				MAT.Delete(DeleteVals[i]);
				MAT.Insert(InsertVals[i]);
			}

			auto stop_MAT = high_resolution_clock::now(); //stop time

			// Subtract stop and start timepoints and 
			// cast it to required unit. Predefined units 
			// are nanoseconds, microseconds, milliseconds, 
			// seconds, minutes, hours. Use duration_cast() 
			// function. 
			auto duration = duration_cast<microseconds>(stop_MAT - start_MAT);  //1 second is 1,000,000 microseconds (654,773 microseconds is .654 seconds)
			durSumMAT += duration.count();
		}
		/*cout << "Number of nodes for these trees: " << NUM_NODES << '\n';
		cout << "Average time for Unaware tree over 10 iterations: " << durSumUT / 10 << " microseconds\n";
		cout << "Average time for Aware tree over 10 iterations: " << durSumAT / 10 << " microseconds\n\n";*/

		cout << NUM_NODES << '\t' << durSumUT / 10 << '\t' << durSumAT / 10 << '\t' << durSumMAT / 10 << '\n';
	}
#endif// TIME_TEST
#ifdef TIME_TEST_NO_VECS
	//this is a Time test where RNG values are inserted directly into trees. I.E. no additional vectors are used in main
	//this means we only insert into the tree, as reliably deleting from tree seems to require additional vectors
	bool UseAwareTree = false;
	if (UseAwareTree)
	{
		//we test the aware tree and not the un-aware tree
		double durationSum = 0;
		AwareBST AT(NUM_NODES);
		for (int i = 0; i < NUM_NODES; i++)
		{
			//generate val to insert, then start the time
			int val = rand() % NUM_NODES;
			auto start = high_resolution_clock::now(); //start time

			//insert val
			AT.Insert(val);
			auto stop = high_resolution_clock::now(); //stop time
			auto duration = duration_cast<microseconds>(stop - start); //1 second is 1,000,000 microseconds (654,773 microseconds is .654 seconds)
			durationSum += duration.count();
		}
		std::cout << "Time to create Aware tree without the use of vectors in main: " << durationSum / 1000000 << " seconds\n\n";
	}
	else
	{
		//we test the un-aware tree and not the aware tree
		double durationSum = 0;
		UnawareBST UT;
		for (int i = 0; i < NUM_NODES; i++)
		{
			//generate val to insert, then start the time
			int val = rand() % NUM_NODES;
			auto start = high_resolution_clock::now(); //start time

			//insert val
			UT.Insert(val);
			auto stop = high_resolution_clock::now(); //stop time
			auto duration = duration_cast<microseconds>(stop - start); //1 second is 1,000,000 microseconds (654,773 microseconds is .654 seconds)
			durationSum += duration.count();
		}
		std::cout << "Time to create Un-aware tree without the use of vectors in main: " << durationSum / 1000000 << " seconds\n\n";
	}
#endif // TIME_TEST_NO_VECS

}