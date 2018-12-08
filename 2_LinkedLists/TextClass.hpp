//lab 3 - TextClass.hpp
//Daniel Blasher

#ifndef TextClass_HPP
#define TextClass_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class Link {
private:
	char letter;
	Link * next;
	Link *previous;

public:
	//constructor sets two pointers to nullptr if no values are given, otherwise the three private properties are assigned their respective parameter
	Link (char l, Link * n = nullptr, Link * p = nullptr): letter(l), next (n), previous(p){}

	//point this link forward to a different link
	void setNext(Link * n) { next = n; }

	//see what this link is pointing to. if it returns nullptr, then this is the end of the List
	Link * getNext() { return next; }

	//point this link backwards to a different link
	void setPrevious(Link * p) { previous = p; }

	//see what this link is pointing back to. If it returns nullptr, then this is the head of the list
	Link * getPrevious() { return previous; }

	//what character is this link holding?
	char getValue() { return letter;}
};


class TextClass {
private:

	// last Link in the list
	Link *tail;

	//points to recently viewed Link - such as in findKey(), insertKey(), or deleteIter()
	Link *iter;

	Link *head;

public:
	//first Link in the list, made this public so the AppendList method can use it
	//Link *head;

	//constructor sets head, tail, and iter to nullptr
	TextClass();

	//destructor deletes any and all links
	~TextClass();

	//creates a new link, points head to it, sets its letter property to equal the parameter
	void insertHead(char val);

	//creats  a new link, points tail to it, sets tail equal to it, assigns parameter 
	void insertTail(char val);

	//if empty, throw exception. Store character in head Link, remove the head Link, set head equal to the next Link
	char deleteHead();

	//same logic as removeHead()
	char deleteTail();

	bool isEmpty();

	//searches this list looking for a Link who's char property equals the key parameter.
	//If found, set iter to point to that link and return true
	//if not found, set iter to nullptr, and return false
	bool findKey(char key);

	//create new link with parameter character and insert it before the iter link
	//if iter is nullptr, return false, else true if this succeeds
	bool insertKey(char value);

	//if iter != nullptr, delete the link it is pointing to and set iter to nullptr and return true
	//else return false
	bool deleteIter();

	//delete the first link found with the value key and return true if successful
	//if iter is pointing the link being deleted, then set iter = nullptr
	bool deleteKey(char key);

	//moving from head to tail, return a string with all the char values in each link
	std::string displayList();

	//utility method to check for special deletion cases. Used with deleteKey and deleteIter
	bool deleteHeadOrTail(Link *key);

	void appendList(TextClass *list2);
};


#endif