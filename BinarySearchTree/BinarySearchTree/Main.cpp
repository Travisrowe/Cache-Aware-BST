#include "AwareBST.h"
#include "UnawareBST.h"
#include <algorithm>
#include <time.h>
#include <iostream>

//L2CacheSize  L3CacheSize
//512 kb       3072 kb
//524,288 bytes
//12 bytes per Node
// 524,288 / 12 = 43,690 Nodes

#define NUM_NODES 43690 //number of nodes
#define ID_PAIRS 10000 //number of insert/delete pairs
#define SEED 2
//#define DEBUG true

//swap index a with index b inside vect
void Swap(vector<int> &vect, int a, int b)
{
	int temp = vect[a];
	vect[a] = vect[b];
	vect[b] = temp;
}

int main()
{
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

#else // Time-test program
	
#endif // Debug

}