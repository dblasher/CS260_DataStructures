//	HashTable.h
//	Daniel Blasher
//	CS260 Lab 6

#ifndef HashTable_h
#define HashTable_h

#include <string>

class HashTable {
public:
	HashTable(int size = SIZE);
	~HashTable();

	void addValue(int value);
	bool findValue(int value);
	bool removeValue(int value);
	

	std::string displayTable();

private:
	int PRIMES[6] = {23, 47, 97, 197, 397, 797 };
	int pCount = 0;
	const static int SIZE = 11;
	int size;
	int count;
	int * theTable;

	const static int EMPTY = -1;
	const static int DELETED = -2;

	//makes more sense to have rehash be private
	void rehash();
	int hasher(int value, int size);

};

#endif