//
//  Stack.cpp
//  Lab_2
//
// By Daniel Blasher 10/5/2018

//Do this after writing Dequeue files
#include "Stack.h"
#include <iostream>
#include <stdexcept>


Stack::Stack() {
	mystack = new Dequeue();
}

Stack::Stack(int size) {
	mystack = new Dequeue(size);
}

Stack::~Stack() {
	delete mystack;
}

void Stack::push(int item) {
	//adds an item to the stack
	mystack->addLeft(item);
}

int Stack::peek() {
	//shows the last item added, which is located at myarray[left -1]
	int index = mystack->left;
	return mystack->myarray[index -1];
}

int Stack::pop() {
	//removes and returns last item added
	return mystack->getLeft();
}