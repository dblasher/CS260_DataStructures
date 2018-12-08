//lab 5 - PriorityQueue.h
//Daniel Blasher
//CS 260 Fall 2018


#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Heap.h"

class PriorityQueue {
private:
	Heap * myHeap; 

public:
	//construct myHeap with int size
	PriorityQueue(int size);

	//delete myHeap
	~PriorityQueue();

	//add a value
	void insert(int value);

	//see the largest value
	int peek();

	//remove and return the largest value
	int remove();
};
#endif