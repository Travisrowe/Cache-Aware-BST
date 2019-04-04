This program compares three types of binary search trees in terms of efficiency.
	- UnawareBST: a BST which uses pointers and the New keyword when allocating space
	- AwareBST: A BST which uses a single vector to allocate space and which uses a series of integer indices to keep track of free space.
	- Multi_AwareBST: A BST which uses a 2D matrix to allocate space and which uses a series of tuple indices to keep track of free space.

To change experiments, you can comment out some of the definitions at the top of Main.cpp. For example, if you wanted to debug the program, the definitions might look like this:

	#define DEBUG true
	//#define TIME_TEST true
	//#define FIND_SEED true
	//#define TIME_TEST_NO_VECS true

where #define DEBUG true is the only line not commented. Then the section of main which is surrounded by 

	#ifdef DEBUG
		... 
	#endif //DEBUG

will run.