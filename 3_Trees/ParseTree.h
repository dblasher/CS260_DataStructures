//lab 5 - ParseTree.h
//Daniel Blasher
//CS 260 Fall 2018


#ifndef ParseTree_H
#define ParseTree_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip> 

class Node {
public:
	// constructor to build new node
	//Link(char l, Link * n = nullptr, Link * p = nullptr) : letter(l), next(n), previous(p) {}
	Node(char v, Node * l = nullptr, Node * r = nullptr) : value(v), left(l), right(r) {}

	char value;
	Node * left;
	Node * right;
};
//could use Tree example code
//or ParseTree example code

// ParseTree transforms a postfix algabraic expression into a parse tree
/* (a + b ) * (a + b) becomes ab + cd +* becomes:
	mulitply
	 /     \
	+       +
   /  \    /  \
  a    b  c    d

*/
class ParseTree {
private:
	Node * root;

	//helper properties taken from Jim's Parser.hpp
	static const char LPAREN = '(';
	static const char RPAREN = ')';
	static const char PLUS = '+';
	static const char MINUS = '-';
	static const char MULT = '*';
	static const char DIV = '/';
	static const char SPACE = ' ';

public:
	//create tree based on expression
	ParseTree(std::string expression);

	//clean up allocated memory
	~ParseTree();
	void recDestruct(Node * ptr);
	
	//pre-order traversal that returns the prefix expression
	std::string preOrder();
	std::string recPreOrder(Node * ptr);

	//in-order traversal that returns the infix expression, don't forget to wrap the output in parentheses
	std::string inOrder();
	std::string recInOrder(Node * ptr);
	

	//post-order traversal that returns the postfix expression
	std::string postOrder();
	std::string recPostOrder(Node * ptr);

	Node * doParse(std::string expression);
	//isalnum(value)?
	bool isOperand(char value);
	//is it an operator?
	bool isOperator(char value);



};

#endif