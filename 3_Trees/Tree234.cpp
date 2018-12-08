//lab 5 - Tree234.h
//Daniel Blasher
//CS 260 Fall 2018

#include "Tree234.h"

Tree234::Tree234() {
	root = new Node234;
}

Tree234::~Tree234() {
	recDelete(root);
}

//add the value
void Tree234::addValue(int value) {

	Node234 * ptr = root;

	while (true) {
		//is the Node already full?
		if (ptr->isFull()) {
			//split it
			split(ptr);
			//move up to parent to check again
			ptr = ptr->getParent();
			//and back down to where we should be for inserting
			ptr = getNextChild(ptr, value);
		}
		//Node is not full, is it a leaf?
		else if (ptr->isLeaf())
			//stop looking and add the value here!
			break;
		//not full or a leaf, go down more since we want to fill any spots at the bottom first
		else
			ptr = getNextChild(ptr, value);
	}

	//break on line 33 brings us to the end of this action
	ptr->insertValue(value);
}

//return true if value is found
bool Tree234::isThere(int value) { 
	return recFind(value, root);
}

//display tree as shown in example code, where??
std::string Tree234::display() {
	return recDisplay(root, 0, 0);
}

//in order traversal, return resulting string
std::string Tree234::inOrder() {
	return recInOrder(root);
}

//--Helper Functions, courtesy of Jim --//

// assumes the node is full
void Tree234::split(Node234* ptr)
{
	int valueB, valueC;
	Node234 * parent;
	Node234 * child2;
	Node234 * child3;
	int valueIndex;

	// remove two largest values
	valueC = ptr->removeValue();
	valueB = ptr->removeValue();
	// remove two rightmost children
	child2 = ptr->removeChild(2);
	child3 = ptr->removeChild(3);

	// create a new node
	// and put rightmost stuff in it
	Node234 * newRight = new Node234;
	newRight->insertValue(valueC);
	newRight->addChild(0, child2);
	newRight->addChild(1, child3);

	// special case root
	if (ptr == root)
	{
		// make a new root and attach this node to it
		root = new Node234;
		parent = root;
		root->addChild(0, ptr);
	}
	else
		parent = ptr->getParent();

	// now modify parent
	// move second value up to it
	// and connect newRight appropriately
	valueIndex = parent->insertValue(valueB);

	// move child links to the right as needed
	for (int i = parent->getNumValues() - 1; i > valueIndex; i--)
	{
		Node234 * temp = parent->removeChild(i);
		parent->addChild(i + 1, temp);
	}

	// now add new link in remaining slot
	parent->addChild(valueIndex + 1, newRight);
}

Node234 * Tree234::getNextChild(Node234 * theNode, int value)
{
	for (int i = 0; i < theNode->getNumValues(); i++)
		if (value < theNode->getValue(i))
			return theNode->getChild(i);
	return theNode->getChild(theNode->getNumValues());
}

// recursive find, called by isThere
bool Tree234::recFind(int value, Node234* ptr)
{
	if (ptr == nullptr)
		return false;

	int num = ptr->getNumValues();
	// otherwise, look at the node
	for (int i = 0; i < num; i++)
	{
		if (ptr->getValue(i) == value)
			return true;
		if (ptr->getValue(i) > value)
			return recFind(value, ptr->getChild(i));
	}

	return recFind(value, ptr->getChild(num));
}

// recursive display, called by display
std::string Tree234::recDisplay(Node234 * thisNode, int level, int childNumber)
{
	std::stringstream output;

	output << "level=" << level << " child=" << childNumber << " ";

	output << thisNode->displayNode();               // display this node

	// call ourselves for each child of this node
	int numValues = thisNode->getNumValues();
	for (int j = 0; j < numValues + 1; j++)
	{
		Node234 * nextNode = thisNode->getChild(j);
		if (nextNode != NULL)
			output << recDisplay(nextNode, level + 1, j);
		else
			break;
	}
	return output.str();
}

void Tree234::recDelete(Node234 * ptr)
{
	// if done with this branch, stop
	if (ptr == nullptr)
		return;

	// delete children first
	for (int i = 0; i < Node234::DEGREE; i++)
		recDelete(ptr->getChild(i));

	delete ptr;
}

std::string Tree234::recInOrder(Node234* ptr) {
	std::string buffer = "";

	//base case
	if (!ptr)
		return buffer;

	//
	for (int i = 0; i <= ptr->getNumChildren(); i++) {
		//make sure we're not on a leaf
		if (!ptr->isLeaf()) {
			buffer += recInOrder(ptr->getChild(i));
			if (i < ptr->getNumChildren() - 1) {
				buffer += std::to_string(ptr->getValue(i));
				buffer += " ";
			}
			else
				break;

		}
		//we're at a leaf, loop through its values, adding them to buffer
		else {
			for (int j = 0; j < ptr->getNumValues(); j++) {
				buffer += std::to_string(ptr->getValue(j));
				buffer += " ";
			}
		}

	}
	return buffer;
}