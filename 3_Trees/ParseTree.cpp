//lab 5 - ParseTree.cpp
//Daniel Blasher
//CS 260 Fall 2018
//recursive order methods were taken from Jim's starter code

#include "ParseTree.h"
#include <stack>

ParseTree::ParseTree(std::string expression) {
	root = doParse(expression);
}

ParseTree::~ParseTree() {
	recDestruct(root);
}
void ParseTree::recDestruct(Node * ptr) {
	//base case
	if (!ptr)
		return;
	//destroy children
	recDestruct(ptr->left);
	recDestruct(ptr->right);
	//destroy self
	delete ptr;
}

//self, left, right
std::string ParseTree::preOrder(){
	return recPreOrder(root);
}

std::string ParseTree::recPreOrder(Node *ptr)
{
	std::string buffer = "";

	// if done with branch, return empty
	if (ptr == nullptr)
		return buffer;

	// get this nodes value
	std::stringstream temp;
	temp << ptr->value;

	// build buffer in proper order
	buffer += temp.str();
	buffer += recPreOrder(ptr->left);
	buffer += recPreOrder(ptr->right);

	return buffer;
}


std::string ParseTree::inOrder() {
	return recInOrder(root);
}
//left, self, right
std::string ParseTree::recInOrder(Node *ptr)
{
	std::string buffer = "";

	// if done with branch, return empty
	if (ptr == nullptr)
		return buffer;

	// get this nodes value
	std::stringstream temp;
	temp << ptr->value;

	// build buffer in proper order
	if (ptr->left)
		buffer += LPAREN;
	buffer += recInOrder(ptr->left);
	buffer += temp.str();
	buffer += recInOrder(ptr->right);
	if (ptr->right)
		buffer += RPAREN;

	return buffer;
}


std::string ParseTree::postOrder() {
	return recPostOrder(root);
}
//left, right, value
std::string ParseTree::recPostOrder(Node *ptr)
{
	std::string buffer = "";

	// if done with branch, return empty
	if (ptr == nullptr)
		return buffer;

	// get this nodes value
	std::stringstream temp;
	temp << ptr->value;

	// build buffer in proper order
	buffer += recPostOrder(ptr->left);
	buffer += recPostOrder(ptr->right);
	buffer += temp.str();

	return buffer;
}

//----Helper methods-----//

Node* ParseTree::doParse(std::string expression) {
	Node *ptr = root;
	//create a stack that holds pointers to nodes
	std::stack<Node*> myStack;

	//read the string, decide what to do with each char
	for (int i = 0; i < expression.length(); i++) {
		char next = expression[i];
		//operands become a  leaf node and get added to stack
		if (isOperand(next)) {
			ptr = new Node(next);
			myStack.push(ptr);
		}
		else
			if (isOperator(next)) {
				Node *right = myStack.top();
				myStack.pop();
				Node *left = myStack.top();
				myStack.pop();
				//I hope this compiles, not sure I declared/defined this Node constructor properly in the header
				ptr = new Node(next, left, right);
				myStack.push(ptr);
			}
		//operators become parent node of last two nodes in the stack
	}
	return myStack.top();

}

bool ParseTree::isOperand(char value) {
	return isalnum(value);
}

//is it an operator?
bool ParseTree::isOperator(char value) {
	switch (value) {
	case PLUS:
	case MINUS:
	case MULT:
	case DIV:
		return true;
	default:
		return false;
	}
}
