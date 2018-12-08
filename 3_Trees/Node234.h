//
//  Node234.h
//  Lab5
//
//  Created by Jim Bailey on 5/12/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef Node234_h
#define Node234_h

#include <string>

// Node for a 234 tree of integers
class Node234 {

public:
	// defines the max number of children
	static const int DEGREE = 4;

private:
	// current number of values present
	int numValues;

	// array holding the values
	int values[DEGREE - 1];

	// array holding pointers to children
	Node234 * children[DEGREE];

	// pointer to our parent
	Node234 * parent;

public:
	Node234();
	// add or remove a child node
	void addChild(int index, Node234 * child);
	Node234 * removeChild(int index);

	// given an index, return that child pointer
	Node234 * getChild(int index);
	// given an index, return that value
	int getValue(int index);

	// return the parent pointer
	Node234 * getParent();

	// information about this node
	bool isLeaf();
	int getNumValues();
	int getNumChildren();
	bool isFull();

	// add a new value, return where it was stored
	int insertValue(int value);
	// remove the largest value present
	int removeValue();
	// find an item, return -1 if not present, index otherwise
	int findValue(int value);

	//display method
	std::string displayNode();
};

#endif /* Node234_h */
