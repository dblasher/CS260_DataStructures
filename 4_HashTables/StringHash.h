//	StringHash.h
//	Daniel Blasher
//	CS260 Lab 6

#ifndef StringHash_h
#define StringHash_h

#include <string>

class StringHash {
	
	public:
		StringHash(int size = SIZE);
		~StringHash();

		void addValue(std::string value);
		bool findValue(std::string value);
		bool removeValue(std::string value);
		void rehash();

		std::string displayTable();

	private:
		int PRIMES[6] = { 23, 47, 97, 197, 397, 797 };
		int pCount = 0;
		const static int SIZE = 11;
		int size;
		int count;
		std::string *theTable;
		//Or
		// std::string **TheTable = new string *[size]
		//this creates a pointer to a pointer, allowing you to make an array of pointers
		//table[i] = new string("this")

		//const static int EMPTY = nullptr;
		static const std::string EMPTY;
		static const std::string DELETED;

		int hasher(std::string, int size);
};

#endif