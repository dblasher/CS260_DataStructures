//
//  Dequeue.h
//  Lab_2
//
// By Daniel Blasher 10/5/2018

#include <string>

#ifndef Dequeue_h
#define Dequeue_h

class Dequeue {

private:
	//const int DEFAULT = 100;
	int size = 100;
	// left points to next location wehre we can add a value

	
	int count = 0; // tracks current total amount of items in the array
	

public:
	//making these properties public so that stack can peek at it
	int *myarray;
	//if left == size then left = 0, effectively 'wrapping' the array
	int left = 0;

	// right points to one location before we can remove the next value AND tracks total amount of items removed 
	int right = -1;

	Dequeue();
	Dequeue(int);
	~Dequeue();
	void addLeft(int);
	void addRight(int);
	int getLeft();
	int getRight();
	bool isEmpty();
	bool isFull();
	void resize();
	std::string listLeftRight();
};
#endif