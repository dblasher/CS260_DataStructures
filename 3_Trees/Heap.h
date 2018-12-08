//lab 5 - Heap.h
//Daniel Blasher
//CS 260 Fall 2018


#ifndef Heap_H
#define Heap_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class Heap {
	//see starter code in moodle
private:
	static const int DEFAULT = 16;
	int *maxHeap;
	int size;
	int counter;

public:
	//create an array of size, default is 16
	Heap(int size = DEFAULT);

	//clean up, delete [] maxHeap
	~Heap();

	//add value at the proper location, double maxHeap if needed
	void insert(int value);

	//remove largest int, throw error if maxHeap is empty
	int remove();

	//return the largest value, throw error if maxHeap is empty
	int largest();

	//--helper methods from starter Code -- //
	int getParent(int index);
	int getLeft(int index);
	int getRight(int index);

	// recursively trickle down from root to proper place
	void trickleDown(int index);

	// recursively bubble up from last to proper place
	void bubbleUp(int index);
};
#endif