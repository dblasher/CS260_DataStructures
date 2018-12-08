//	ChainHash.h
//	Daniel Blasher
//	CS260 Lab 6


#ifndef ChainHash_h
#define ChainHash_h

#include <string>
#include "LinkedList.h"

class ChainHash {
public:
	ChainHash(int size = SIZE);
	~ChainHash();

	void addValue(std::string value);
	bool findValue(std::string value);
	bool removeValue(std::string value);
	

	std::string displayTable();

private:
	int PRIMES[6] = { 23, 47, 97, 197, 397, 797 };
	int pCount = 0;
	const static int SIZE = 11;
	int size;
	int count;
	LinkedList * theTable;

	const static int EMPTY = -1;
	const static int DELETED = -2;
	//moved rehash to private per peer reviewer's recommendation
	void rehash();
	int hasher(std::string value, int size);

};


#endif