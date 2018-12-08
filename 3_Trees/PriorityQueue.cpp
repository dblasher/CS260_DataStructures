//lab 5 - PriorityQueue.cpp
//Daniel Blasher
//CS 260 Fall 2018

#include "PriorityQueue.h"

	//construct myHeap with int size
PriorityQueue::PriorityQueue(int size) {
	myHeap = new Heap(size);
}

//delete myHeap
PriorityQueue::~PriorityQueue() {
	delete myHeap;
}

//add a value
void PriorityQueue::insert(int value) {
	myHeap->insert(value);
}

//see the largest value
int PriorityQueue::peek() {
	return myHeap->largest();
}

//remove and return the largest value
int PriorityQueue::remove() {
	return myHeap->remove();
}