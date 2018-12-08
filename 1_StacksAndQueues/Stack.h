//
//  Stack.h
//  Lab_2
//
// By Daniel Blasher 10/5/2018


#include "Dequeue.h"

#ifndef Stack_h
#define Stack_h

class Stack {

private:
	Dequeue *mystack;

public:
	Stack();
	Stack(int);
	~Stack();
	void push(int);
	int peek();
	int pop();
	//
};
#endif