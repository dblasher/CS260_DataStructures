//	StringHash.cpp
//	Daniel Blasher
//	CS260 Lab 6

#include "StringHash.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>


const std::string StringHash::EMPTY = "nullptr";
const std::string StringHash::DELETED = "xDELx";
//constructor, creates array of specified size or defaults to 11
StringHash::StringHash(int size) {
	
	this ->size = size;
	count = 0;
	theTable = new std::string[size];
	//populate with empty value
	for (int i = 0; i < size; i++)
			theTable[i] = EMPTY;

}

StringHash::~StringHash() {
	delete[] theTable;
}

void StringHash::addValue(std::string value) {
	//if table is full, rehash (doubles the size, rehashes all values)
	if (count >= size / 2)
		rehash();
	//save location is should go
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

bool StringHash::findValue(std::string value) {

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

bool StringHash::removeValue(std::string value) {
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

std::string StringHash::displayTable() {
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

void StringHash::rehash() {
	int newSize;

	//in case this HashTable has outgrown the prime sizes I provided
	if (pCount >= 6)
		newSize = size * 2;
	else
		newSize = PRIMES[pCount++];

	//populate new array with empties
	std::string *temp = new std::string[newSize];
	for (int i = 0; i < newSize; i++)
		temp[i] = EMPTY;

	//rehash old values into new array
	for (int i = 0; i < size; i++) {
		std::string item = theTable[i];
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

int StringHash::hasher(std::string value, int size) {
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