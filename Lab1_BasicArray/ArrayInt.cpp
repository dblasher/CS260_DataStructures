

#include "ArrayInt.hpp"
#include <iostream>
#include <stdexcept>

//constructor definition
//can combine these 2 constructors using a default parameter
/*
ArrayInt::ArrayInt(int size = DEFAULT){
	myarray = new int[size];
	size = size;
}
*/
ArrayInt::ArrayInt() {
	//std::cout << " Created new ArrayInt" << std::endl << std::endl;
	myarray = new int[size];
}

//overloaded constructor accepting parameter for array size
ArrayInt::ArrayInt(int n) {
	if (n < 1)
		myarray = new int[size];
	//need to delete this new array at some point
	//delete[] myarray;
	else {
		myarray = new int[n];
		//myarray[n]={0}
		size = n;
	}
}

int ArrayInt::getAt(int index) {

	if (index < 0 || index > size - 1) {
		throw std::out_of_range("out of range");
	}
	else {
		//std::cout << myarray[index] << std::endl;
		return myarray[index];
	}
	/*
			try {
			int output = myarray[index];
			std::cout << output << " is at index " << index << std::endl;
			return output;
		}
		catch(int e){
			std::cout << index << "is out of range" << std::endl;
			throw;
		}
	*/
}

void ArrayInt::setAt(int index, int value) {
	if (index < 0 || index > size - 1)
		throw std::out_of_range("out of range");
	else {
		myarray[index] = value;
		if (index >= count)
			count = index + 1; //count should always track the largest available index. This will be important the append method
		//std::cout << myarray[index] << std::endl;
	}
}

int ArrayInt::getSize() {
	//std::cout << "array size is: " << size << std::endl;
	return size;
}

void ArrayInt::setSize(int newSize) {
	//arrays in C++ are always a fixed size
	if (newSize > size) {
		int *temp = new int[newSize];
		for (int i = 0; i < size; i++)
			temp[i] = myarray[i];
		delete[] myarray;
		myarray = temp;
		//should I delete temp now?
		size = newSize;
	}
	//newSize is not greater than current size, do nothing

}

void ArrayInt::append(int value) {
	//is the last index occupied? If yes, double the array, append the value at count, iterate count
	if (count == size) {
		int newSize = size * 2;
		setSize(newSize);
		myarray[count] = value;
		count++;
	}
	else {
		myarray[count] = value;
		count++;
	}
}

void ArrayInt::insertAt(int index, int value) {
	//is index in range?
	if (index < 0 || index > size - 1)
		throw std::out_of_range("out of range");

	if (count != size) {
		//can fit the insert and subsequent shifts, shift values up, don't move the last item because it is empty
		for (int i = size - 1; i >= index; i--) {
			myarray[i] = myarray[i - 1];
		}
		myarray[index] = value;
		count++;
	}
	else {
		//create an unshifted copy with twice the size as myarray
		int newSize = size * 2;
		setSize(newSize);
		//then shift those values up by one starting right after then insertion index
		for (int i = size -1; i >=  index; i--)
			myarray[i] = myarray[i -1];

		myarray[index] = value;
		count++;
	}
}

int ArrayInt::removeAt(int index) {
	//is index in range or is the array empty with nothing to remove?
	if (index < 0 || index > size - 1 || count == 0)
		throw std::out_of_range("out of range");

	int item = myarray[index];

	for (int i = index; i < size; i++)
		myarray[i] = myarray[i + 1];

	count--;
	/* 
	Beta version below

	Not sure what I was thinking when I setup this loop, it will often terminate before ever running and completely empty myarray !
	int *temp = new int[size];
	for (int i = size - 2; i < index; i--) {
		temp[i] = myarray[i + 1];
	}
	delete[] myarray;
	myarray = temp;
	if (count > 0)
		count--;
	*/
	return item;
}
