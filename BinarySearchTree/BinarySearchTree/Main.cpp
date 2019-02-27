#include "AwareBST.h"
#include "UnawareBST.h"
#include <algorithm>
#include <time.h>
#include <iostream>

#define NUM_NODES 128 //number of nodes
#define ID_PAIRS 100 //number of insert/delete pairs


int main()
{
	srand(2);
	AwareBST AT(NUM_NODES);
	UnawareBST UT;
	AT.Insert(1);
}