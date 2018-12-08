//	ChainHash.cpp
//	Daniel Blasher
//	CS260 Lab 6

#include "ChainHash.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>


//constructor, creates array of specified size or defaults to 11
ChainHash::ChainHash(int size) {
	size = size;
	count = 0;
	theTable = new LinkedList[size];
	//Do I need to put anything in the LinkedLists?
	//for (int i = 0; i < size; i++)
		//theTable[i].insertHead();

}

ChainHash::~ChainHash() {
	delete[] theTable;
}

void ChainHash::addValue(std::string value) {
	//if table reaches a size *2, time to double it. Note, LinkedLists are not balancing
	if (count >= size * 2)
		rehash();
	//save location it should go in
	int index = hasher(value, size);

	//can it really be this simple?!
	theTable[index].insertHead(value);

}

bool ChainHash::findValue(std::string value) {
	//which LinkedList are we looking in?
	int index = hasher(value, size);

	//find the value in that list
	return theTable[index].findKey(value);
}

bool ChainHash::removeValue(std::string value) {
	//which LinkedList are we looking in?
	int index = hasher(value, size);

	//find the value in that list
	return theTable[index].deleteKey(value);
}

std::string ChainHash::displayTable() {

	//after each LinkedList add a new line: <<std::endl
	std::stringstream buffer;

	for (int i = 0; i < size; i++)
	{
		if (theTable[i].isEmpty())
			buffer << "EMPTY" << std::endl;
		else
			//<< std::setw(9) 
			buffer << theTable[i].displayList() << std::endl;
	}
	buffer << std::endl;
	return buffer.str();
}

void ChainHash::rehash() {
	int newSize;

	//in case this HashTable has outgrown the prime sizes I provided
	if (pCount >= 6)
		newSize = size * 2;
	else
		newSize = PRIMES[pCount++];

	//populate new array with empties
	LinkedList *temp = new LinkedList[newSize];
	//for (int i = 0; i < newSize; i++)
		//temp[i].insertHead();

	//rehash old values into new array
	for (int i = 0; i < size; i++) {
		while (!theTable[i].isEmpty()) {
			std::string item = theTable[i].deleteHead();
			//shouldn't have any empty items, not checking for DELETED or EMPTY
			int index = hasher(item, newSize);
			temp[index].insertHead(item);
		}
		
	}
	delete[] theTable;
	theTable = temp;
	size = newSize;
}

int ChainHash::hasher(std::string value, int size) {
	//using Jim's example code for now
	int index = 0;
	for (int i = 0; i < value.length(); i++)
	{
		index *= 26;
		index += value[i];
		index %= size;
	}
	return index;
}