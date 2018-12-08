//	HashTable.cpp
//	Daniel Blasher
//	CS260 Lab 6

#include "HashTable.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>


//constructor, creates array of specified size or defaults to 11
HashTable::HashTable(int size) {
	size = size;
	count = 0;
	theTable = new int[size];
	//populate with empty value
	for (int i = 0; i < size; i++)
		theTable[i] = EMPTY;

}

HashTable::~HashTable() {
	delete[] theTable;
}

void HashTable::addValue(int value) {
	//if table is full, rehash (doubles the size, rehashes all values)
	if (count >= size / 2)
		rehash();
	//save location it should go in
	int index = hasher(value, size);

	//adjust index to an available location
	while (theTable[index] != EMPTY and theTable[index] != DELETED) {
		index++;
		//wrap around if we reached end of the array
		if (index >= size)
			index = 0;
	}
	theTable[index] = value;
	count++;
}

bool HashTable::findValue(int value) {
	
	int index = hasher(value, size);
	//start looking at the location it would be hashed too, check everything after that until EMPTY is reached
	while (theTable[index] != EMPTY) {

		if (theTable[index] == value)
			return true;
		
		index++;

		if (index >= size)
			index = 0;
	}
	//looped through all the locations the value should be at and did not find
	return false;
	
}

bool HashTable::removeValue(int value) {
	int index = hasher(value, size);
	//start looking at the location it would be hashed too, check everything after that until EMPTY is reached
	while (theTable[index] != EMPTY) {

		if (theTable[index] == value) {
			theTable[index] = DELETED;
			count--;
			return true;
		}
		index++;

		if (index >= size)
			index = 0;
	}
	//looped through all the locations the value should be at and did not find
	return false;
}

std::string HashTable::displayTable() {
	std::stringstream buffer;

	for (int i = 0; i < size; i++)
	{
		if (theTable[i] == EMPTY)
			buffer << "EMPTY" << std::endl;
		else
			if (theTable[i] == DELETED)
				buffer << "DELETED" << std::endl;
			else
				buffer << std::setw(6) << theTable[i] << std::endl;
	}
	buffer << std::endl;
	return buffer.str();
}

void HashTable::rehash() {
	int newSize;

	//in case this HashTable has outgrown the prime sizes I provided
	if (pCount >= 6)
		newSize = size * 2;
	else
		newSize = PRIMES[pCount++];

	//populate new array with empties
	int *temp = new int[newSize];
	for (int i = 0; i < newSize; i++)
		temp[i] = EMPTY;

	//rehash old values into new array
	for (int i = 0; i < size; i++) {
		int item = theTable[i];
		//skip empty and deleted locations
		if (item != EMPTY and item != DELETED) {
			int index = hasher(item, newSize);
			temp[index] = item;
		}
	}
	delete[] theTable;
	theTable = temp;
	size = newSize;
}

int HashTable::hasher(int value, int size) {
	//whoops, had these reversed before. Peer reviewer caught this
	return value % size;
}
