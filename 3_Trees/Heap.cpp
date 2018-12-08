//lab 5 - Heap.cpp
//Daniel Blasher
//CS 260 Fall 2018
#include "Heap.h"

	//create an array of size, default is 16
Heap::Heap(int size) {
	this->size = size;
	counter = 0;
	maxHeap = new int[size];
}

//clean up, delete [] maxHeap
Heap::~Heap() {
	delete[] maxHeap;
}

//add value at the proper location, double maxHeap if needed
void Heap::insert(int value) {
	//if full, make a double and copy voer
	if (counter >= size) {
		int * temp = new int[size * 2];
		for (int i = 0; i < size; i++)
			temp[i] = maxHeap[i];
		delete[] maxHeap;
		maxHeap = temp;
		size *= 2;
	}
	maxHeap[counter++] = value;

	//move the new value up if needed
	bubbleUp(counter - 1);
}

//remove largest int, throw error if maxHeap is empty
int Heap::remove() {
	//is it empty?
	if (counter <= 0)
		throw std::length_error("Can't remove from an empty Heap");

	//save the item to be returned
	int removedValue = maxHeap[0];

	//move the last item to the start and decrement counter
	maxHeap[0] = maxHeap[--counter];

	//move the new root down if necessary
	trickleDown(0);

	return removedValue;
}

//return the largest value, throw error if maxHeap is empty
int Heap::largest() {
	//is it empty?
	if (counter <= 0)
		throw std::length_error("Can't remove from an empty Heap");
	return maxHeap[0];
}

//-- Helper Methods Definitions -- //
int Heap::getParent(int index)
{
	return (index - 1) / 2;
}
int Heap::getLeft(int index)
{
	return 2 * index + 1;
}
int Heap::getRight(int index)
{
	return 2 * index + 2;
}

// recursive method to restore heap after adding an item
void Heap::bubbleUp(int index)
{
	// if we are at the root, no more work to do
	if (index == 0)
		return;

	// now see if need to do a swap with parent
	int parent = getParent(index);

	//switch this to less than if you want a min heap bubble up
	if (maxHeap[parent] < maxHeap[index])
	{
		std::swap(maxHeap[parent], maxHeap[index]);

		// now go on up tree
		bubbleUp(parent);
	}

	// already in order, quit
	else
		return;
}

// recursive method to restore heap after removing an item
void Heap::trickleDown(int index)
{
	int left = getLeft(index);
	int right = getRight(index);

	// if no children, then a leaf node, quit
	if (right >= counter)
		return;

	// only a left child
	if (left >= counter)
	{
		// do we need to swap it?
		//switch this to less than if you want a min heap trickle down
		if (maxHeap[left] < maxHeap[index])
		{
			std::swap(maxHeap[left], maxHeap[index]);

			// and go on down
			trickleDown(left);
		}
		// do nothing otherwise

	}
	// two children
	else
	{
		// find out which is larger
		if (maxHeap[left] > maxHeap[right])
		{
			// do we need to swap it?
			//again, switch sign for min heap
			if (maxHeap[left] > maxHeap[index])
			{
				std::swap(maxHeap[left], maxHeap[index]);

				// and go on down
				trickleDown(left);
			}
		}
		else
		{
			// do we need to swap it?
			//again, switch sign for min heap
			if (maxHeap[right] > maxHeap[index])
			{
				std::swap(maxHeap[right], maxHeap[index]);

				// and go on down
				trickleDown(right);
			}
		}
	}


}