
//lab 6 - LinkedList.h
//adapted from Lab 3 TextClass.hpp
//Daniel Blasher

#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class Link {
private:
	std::string value;
	Link * next;
	Link *previous;

public:
	//constructor sets two postd::stringers to nullptr if no values are given, otherwise the three private properties are assigned their respective parameter
	Link(std::string v, Link * n = nullptr, Link * p = nullptr) : value(v), next(n), previous(p) {}

	//postd::string this link forward to a different link
	void setNext(Link * n) { next = n; }

	//see what this link is postd::stringing to. if it returns nullptr, then this is the end of the List
	Link * getNext() { return next; }

	//postd::string this link backwards to a different link
	void setPrevious(Link * p) { previous = p; }

	//see what this link is postd::stringing back to. If it returns nullptr, then this is the head of the list
	Link * getPrevious() { return previous; }

	//what character is this link holding?
	std::string getValue() { return value; }
};


class LinkedList {
private:

	// last Link in the list
	Link *tail;

	//postd::strings to recently viewed Link - such as in findKey(), insertKey(), or deleteIter()
	Link *iter;

	Link *head;

public:
	//first Link in the list, made this public so the AppendList method can use it
	//Link *head;

	//constructor sets head, tail, and iter to nullptr
	LinkedList();

	//destructor deletes any and all links
	~LinkedList();

	//creates a new link, postd::strings head to it, sets its letter property to equal the parameter
	void insertHead(std::string val);

	//creats  a new link, postd::strings tail to it, sets tail equal to it, assigns parameter 
	void insertTail(std::string val);

	//if empty, throw exception. Store character in head Link, remove the head Link, set head equal to the next Link
	std::string deleteHead();

	//same logic as removeHead()
	std::string deleteTail();

	bool isEmpty();

	//searches this list looking for a Link who's char property equals the key parameter.
	//If found, set iter to postd::string to that link and return true
	//if not found, set iter to nullptr, and return false
	bool findKey(std::string key);

	//create new link with parameter character and insert it before the iter link
	//if iter is nullptr, return false, else true if this succeeds
	bool insertKey(std::string value);

	//if iter != nullptr, delete the link it is postd::stringing to and set iter to nullptr and return true
	//else return false
	bool deleteIter();

	//delete the first link found with the value key and return true if successful
	//if iter is postd::stringing the link being deleted, then set iter = nullptr
	bool deleteKey(std::string key);

	//moving from head to tail, return a string with all the char values in each link
	std::string displayList();

	//utility method to check for special deletion cases. Used with deleteKey and deleteIter
	bool deleteHeadOrTail(Link *key);

	void appendList(LinkedList *list2);
};


#endif