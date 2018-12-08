// lab 1 - ArrayInt by Daniel Blasher, CS260

#ifndef ArrayInt_hpp
#define ArrayInt_hpp

class ArrayInt
{
	//declare an array prop for the class
private:

	int *myarray;
	const  int DEFAULT = 10;
	int size = 10;
	int count = 0;
	//begin constructors
public:
	//member methods/constrcutors defined using scope resolution operator
	ArrayInt();
	ArrayInt(int);
	int getAt(int);
	void setAt(int index, int value);
	int getSize();
	void setSize(int size);
	void append(int value);
	void insertAt(int index, int value);
	int removeAt(int index);
};
#endif