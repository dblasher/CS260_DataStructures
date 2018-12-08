//
//  main.cpp
//  CS260Lab5
//
//  Created by Jim Bailey on 5/3/18.
//  Copyright © 2018 Jim Bailey. All rights reserved.
//

#include <iostream>

	// define which tests you want to run
#define TEST_PARSE_TREE
#define TEST_HEAP
#define TEST_PRIORITY_QUEUE
#define TEST_TREE234

	// include appropriate files for those tests
#ifdef TEST_PARSE_TREE
#include "ParseTree.h"
#endif

#ifdef TEST_HEAP
#include "Heap.h"
#endif

#ifdef TEST_PRIORITY_QUEUE
#include "PriorityQueue.h"
#endif

#ifdef TEST_TREE234
#include "Tree234.h"
#endif


int main(int argc, const char * argv[]) {
#ifdef TEST_PARSE_TREE
	std::cout << "Testing Parse Tree" << std::endl << std::endl;

	std::string expression1 = "AB+CD-*";
	std::string expression2 = "AB-C+DE/*";

	ParseTree ptree1(expression1);
	std::cout << "Input is AB+CD-* " << std::endl << "output should be ((A+B)*(C-D)) or (((A)+(B))*((C)-(D)))" << std::endl;
	std::cout << "Output is " << ptree1.inOrder() << std::endl << std::endl;

	ParseTree ptree2(expression2);
	std::cout << "Input is AB-C+DE/* " << std::endl << "output should be (((A-B)+C)*(D/E)) or ((((A)-(B))+(C))*((D)/(E)))" << std::endl;
	std::cout << "Output is " << ptree2.inOrder() << std::endl << std::endl;

	std::cout << "Done with Parse Tree test" << std::endl << std::endl;
#endif // TEST_PARSE_TREE


#ifdef TEST_HEAP
	std::cout << "Testing heap " << std::endl << std::endl;
	const int NUM_HEAP_VALS = 10;
	const int SMALL_HEAP = 5;
	int heap_values[NUM_HEAP_VALS] = { 10, 5, 30, 15, 20, 40, 60, 25, 50, 35 };

	Heap pile(SMALL_HEAP);

	// load the heap with first SMALL_HEAP values
	std::cout << "Loading it with 10, 5, 30, 15, 20" << std::endl;
	for (int i = 0; i < SMALL_HEAP; i++)
		pile.insert(heap_values[i]);

	// display the largest one
	std::cout << "Displaying largest value " << std::endl;
	std::cout << "Should be 30 and is " << pile.largest() << std::endl << std::endl;

	// now add more values, causing doubling
	std::cout << "Now adding 40, 60, 25, 50, 35, should have doubled size" << std::endl << std::endl;
	for (int i = SMALL_HEAP; i < NUM_HEAP_VALS; i++)
		pile.insert(heap_values[i]);

	// remove values, should be in descending order
	std::cout << "Removing from largest to smallest" << std::endl << "Expected results: 60 50 40 35 30 25 20 15 10 5" << std::endl;
	std::cout << "Actual results:   ";
	for (int i = 0; i < NUM_HEAP_VALS; i++)
		std::cout << pile.remove() << " ";
	std::cout << std::endl << std::endl;

	// now test removing from empty heap
	std::cout << "Removing from empty heap" << std::endl;
	try {
		pile.remove();
		std::cout << "Failed to catch error" << std::endl;
	}
	catch (std::length_error &ex) {
		std::cout << "Caught length error with message: " << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "Caught something unexpected" << std::endl;
	}

	std::cout << std::endl << "Done with Heap Testing" << std::endl << std::endl;
#endif // TEST_HEAP

#ifdef TEST_PRIORITY_QUEUE
	std::cout << "Testing Priority Queue of size 15" << std::endl << std::endl;

	const int PQ_NUM_VALUES = 15;
	int pq_values[PQ_NUM_VALUES] = { 1, 13, 21, 3, 5, 7, 9, 11, 15, 23, 17, 19, 25, 27, 29 };

	PriorityQueue theQueue(PQ_NUM_VALUES);

	// load the heap with values
	std::cout << "Loading the queue with first 15 odd numbers in scrambled order" << std::endl << std::endl;
	for (int i = 0; i < PQ_NUM_VALUES; i++)
		theQueue.insert(pq_values[i]);

	std::cout << "Displaying largest, should be 29 and it is " << theQueue.peek() << std::endl << std::endl;

	// remove values, should be in ascending order
	std::cout << "Now removing values, should be in descending order" << std::endl;
	std::cout << "Actual order: ";
	for (int i = 0; i < PQ_NUM_VALUES; i++)
		std::cout << theQueue.remove() << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Done with Priority Queue Test. " << std::endl << std::endl;
#endif // TEST_PRIORITY_QUEUE

#ifdef TEST_TREE234
	std::cout << "Testing 234 Tree " << std::endl << std::endl;

	const int T234_NUM_VALUES = 15;
	int t234_values[T234_NUM_VALUES] = { 24, 18, 2, 4, 6, 10, 8, 12, 16, 14, 20, 22, 26, 28, 30 };

	Tree234 the234Tree;

	std::cout << "Loading tree with even integers 2-30 " << std::endl << std::endl;
	for (int i = 0; i < T234_NUM_VALUES; i++)
		the234Tree.addValue(t234_values[i]);

	// testing find
	std::cout << "Now testing find " << std::endl;
	std::cout << "Looking for 20 " << (the234Tree.isThere(20) ? "found" : "not found") << std::endl;
	std::cout << "Looking for 15 " << (the234Tree.isThere(15) ? "found" : "not found") << std::endl;
	std::cout << "Looking for 0 " << (the234Tree.isThere(0) ? "found" : "not found") << std::endl;
	std::cout << "Looking for 30 " << (the234Tree.isThere(30) ? "found" : "not found") << std::endl << std::endl;

	// inorder traversal
	std::cout << "Now displaying tree in-order " << std::endl;
	std::cout << "Values are: " << the234Tree.inOrder() << std::endl << std::endl;

	std::cout << "Done with testing 234 Tree" << std::endl << std::endl;
#endif // TEST_TREE234

	return 0;
}
