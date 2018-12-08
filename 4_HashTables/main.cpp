//
//  main.cpp
//  heap_example
//
//  Created by Jim Bailey on 5/15/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>

// uncomment the test you want to run
#define INT_HASH
//#define STRING_HASH
#define CHAIN_TEST

#ifdef INT_HASH
#include "HashTable.h"
#endif
#ifdef STRING_HASH
#include "StringHash.h"
#endif
#ifdef CHAIN_TEST
#include "ChainHash.h"
#endif

using namespace std;


int main(int argc, const char * argv[]) {

	const int NUM_VALUES = 10;
	int values[NUM_VALUES] = { 10, 5, 30, 15, 20, 40, 60, 25, 50, 35 };


#ifdef INT_HASH
	// this tests the starting hashing code, it will fail with
	// an overflow_error until you implement the re-hash method

	HashTable intHash(6);

	// place 10 items in a 6 item array, after rehashing
	// the array should expand and not throw an error
	try {

		for (int i = 0; i < NUM_VALUES; i++)
			intHash.addValue(values[i]);
	}
	catch (std::length_error & ex) {
		cout << "Inserting failed with exception: " << ex.what() << endl;
		exit(1);
	}

	// dump the array
	cout << "Displaying the array before find and delete" << endl;
	cout << intHash.displayTable() << endl;

	// now see if find works
	cout << "Looking for 4, should not find -- " << (intHash.findValue(4) ? "found" : "not found") << endl;
	cout << "Looking for 5, should find -- " << (intHash.findValue(5) ? "found" : "not found") << endl;

	// now delete 5 and see if still found
	cout << "Deleting 5, should work -- " << (intHash.removeValue(5) ? "found" : "not found") << endl;
	// now looking again
	cout << "Looking for 5 again, should not find -- " << (intHash.findValue(5) ? "found" : "not found") << endl;

	// dump the array
	cout << endl << "Displaying the array after deleting 5, s/b replaced with \"dele\"" << endl;
	cout << intHash.displayTable() << endl;

#endif //INT_HASH


	string string_values[NUM_VALUES] = { "dog", "god", "cat", "act", "horse", "cow", "elephant", "otter", "seal", "ales" };

#ifdef STRING_HASH

	// this tests the string hashing code


		// change this to your class name
	StringHash stringHash;

	// place 10 items in a hash table
	try {

		for (int i = 0; i < NUM_VALUES; i++)
			stringHash.addValue(string_values[i]);
	}
	catch (std::length_error & ex) {
		cout << "Inserting failed with exception: " << ex.what() << endl;
		exit(1);
	}

	// dump the array
	cout << "Displaying the array before find and delete" << endl;
	cout << stringHash.displayTable() << endl;

	// now see if find works
	cout << "Looking for pig, should not find -- " << (stringHash.findValue("pig") ? "found" : "not found") << endl;
	cout << "Looking for otter, should find -- " << (stringHash.findValue("otter") ? "found" : "not found") << endl;

	// now delete 5 and see if still found
	cout << "Deleting otter, should work -- " << (stringHash.removeValue("otter") ? "found" : "not found") << endl;
	// now looking again
	cout << "Looking for otter again, should not find -- " << (stringHash.findValue("otter") ? "found" : "not found") << endl;

	// dump the array
	cout << endl << "Displaying the array after deleting otter, s/b replaced with \"dele\"" << endl;
	cout << stringHash.displayTable() << endl;

#endif //STRING_HASH

#ifdef CHAIN_TEST
	// this tests the chained string hashing code


	// change this to your class name
	ChainHash chainHash;

	// place 10 items in a hash table
	try {

		for (int i = 0; i < NUM_VALUES; i++)
			chainHash.addValue(string_values[i]);
	}
	catch (std::length_error & ex) {
		cout << "Inserting failed with exception: " << ex.what() << endl;
		exit(1);
	}

	// dump the array
	cout << "Displaying the array before find and delete" << endl;
	cout << chainHash.displayTable() << endl;

	// now see if find works
	cout << "Looking for pig, should not find -- " << (chainHash.findValue("pig") ? "found" : "not found") << endl;
	cout << "Looking for otter, should find -- " << (chainHash.findValue("otter") ? "found" : "not found") << endl;

	// now delete 5 and see if still found
		//added test for finding items that aren't stored at head of the list
	cout << "Deleting elephant, should work -- " << (chainHash.removeValue("elephant") ? "found" : "not found") << endl;
	// now looking again
	cout << "Looking for elephant again, should not find -- " << (chainHash.findValue("elephant") ? "found" : "not found") << endl;

	cout << "Deleting otter, should work -- " << (chainHash.removeValue("otter") ? "found" : "not found") << endl;
	// now looking again
	cout << "Looking for otter again, should not find -- " << (chainHash.findValue("otter") ? "found" : "not found") << endl;

	// dump the array
	cout << endl << "Displaying the array after deleting otter, should no longer be there" << endl;
		cout << chainHash.displayTable() << endl;

#endif // CHAIN_TEST


	return 0;
}