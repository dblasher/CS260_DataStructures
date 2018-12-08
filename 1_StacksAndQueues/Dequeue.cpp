//
//  Dequeue.cpp
//  Lab_2
//
// By Daniel Blasher 10/5/2018

#include "Dequeue.h"
#include <iostream>
//#include <stdexcept>
#include <sstream>


Dequeue::Dequeue() {
	myarray = new int[size];
}

Dequeue::Dequeue(int n) {
	if (n < 1)
		myarray = new int[size];
	else {
		myarray = new int[n];
		size = n;
	}
}

Dequeue::~Dequeue() {
	delete[] myarray;
}
	
void Dequeue::addLeft(int item){
	if (isFull())
		resize();
	//wrap left around if we reached the end of the array
	if (left == size)
		left = 0;

	myarray[left++] = item;
	count++;
}

void Dequeue::addRight(int item){
	//if isFull(), call resize
	if (isFull()) {
		resize();
		// adjust left, count, right?
	}
	//wrap right to end of the array to keep adding
	if (right < 0)
		right = size - 1;

	myarray[right--] = item;
	count++;
}

int Dequeue::getLeft(){
	int item;
	//if isEmpty(), throw exception
	if (isEmpty())
		throw std::range_error("Deqeue is empty");
	//wrap left from index 0 to index size - 1
	if (left == 0) 
		left = size;
	
	item = myarray[--left];
	count--;
	return item;
}

int Dequeue::getRight(){
	int item;
	//if isEmpty(), throw exception 
	if (isEmpty())
		throw std::range_error("Deqeue is empty");
	//remove at one more than right
	//wrapping: if right == size -1, remove at 0, right = -1
	if (right == size - 1) 
		right = -1;
	
	item = myarray[++right];
	count--;
	return item;
}

bool Dequeue::isEmpty(){
	if (count <= 0)
		return true;
	else 
		return false;
} 

bool Dequeue::isFull(){
	if (count >= size) 
		return true;

	else
		return false;

}

void Dequeue::resize() {
	//same code as lab 1, simply doubles the array size
	int newSize = size * 2;
	int wrapCopy = 0;
	int *temp = new int[newSize];
	for (int i = 0; i < size; i++) {
		if (left + i >= size) {
			temp[i] = myarray[wrapCopy++];
			continue;
		}
		temp[i] = myarray[left + i];
	}
	delete[] myarray;
	myarray = temp;
	size = newSize;
	right = -1;
	left = count;
}

std::string Dequeue::listLeftRight() {
	std::ostringstream convert;
	std::string result;
	int item;
	//Did I follow the lab instructions correctly? First version I did not create a copy, so this method could only be called once!
	//I'll make a copy of the dequeue so we can call this method again
	int *temp = new int[size];
	for (int i = 0; i < size; i++) {
		temp[i] = myarray[i];
	}
	//now I can print out the dequeue
	if (isEmpty())
		result = "Queue	is	empty";
	while (!isEmpty()) {
		item = getLeft();
		convert << item << " ";
	}
	result = convert.str();
	delete[] myarray;
	myarray = temp;

	return result;
}
