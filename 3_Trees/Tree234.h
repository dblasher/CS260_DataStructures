//lab 5 - Tree234.h
//Daniel Blasher
//CS 260 Fall 2018


#ifndef Tree234_H
#define Tree234_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "Node234.h"

class Tree234 {
	//see starter code in moodle
	Node234 * root;

public:

	Tree234();

	~Tree234();

	//add the value
	void addValue(int value);

	//return true if value is found
	bool isThere(int value);

	//display tree as shown in example code, where??
	std::string display();
 
	//in order traversal, return resulting string
	std::string inOrder();

	void split(Node234* ptr);

	Node234 * getNextChild(Node234 * theNode, int value);

	bool recFind(int value, Node234* ptr);

	std::string recDisplay(Node234 * thisNode, int level, int childNumber);

	void recDelete(Node234 * ptr);

	std::string recInOrder(Node234* ptr);

};
#endif