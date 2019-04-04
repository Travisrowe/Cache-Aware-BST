#pragma once
class MemoryUnitTuple
{
public: //we use this as a struct: All variables are public
	int first; //which vector does the child belong
	int second; //which index is the child in

	bool operator==(const MemoryUnitTuple&);
	bool operator!=(const MemoryUnitTuple&);
	MemoryUnitTuple(); //{ first = -1; second = -1; }
	MemoryUnitTuple(int, int); //{ first = f; second = s; }
	~MemoryUnitTuple();
};

