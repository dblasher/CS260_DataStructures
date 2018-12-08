//lab 3 - StudentList.hpp
//Daniel Blasher

#ifndef StudentList_HPP
#define StudentList_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class Student {
private:
	std::string name;
	int age;
	
public:
	Student() { name = ""; age = 0; }
	Student(std::string n, int a) { name = n; age = a;}
	void setName(std::string n) { name = n;}
	std::string getName() { return name; }
	void setAge(int a) { age = a; }
	int getAge() { return age; }
};


//similar code as Link in TextClass.hpp, just singly-linked and holds a Student instead of a char
class StudentLink {
private:
	Student student;
	StudentLink * next;
	//StudentLink *previous;

public:
	//constructor sets two pointers to nullptr if no values are given, otherwise the three private properties are assigned their respective parameter
	StudentLink(Student s, StudentLink *n = nullptr) : student(s), next(n) {}

	//point this link forward to a different link
	void setNext(StudentLink * n) { next = n; }

	//see what this link is pointing to. if it returns nullptr, then this is the end of the List
	StudentLink * getNext() { return next; }

	//point this link backwards to a different link
	//void setPrevious(StudentLink * p) { previous = p; }

	//see what this link is pointing back to. If it returns nullptr, then this is the head of the list
	//StudentLink * getPrevious() { return previous; }

	//what character is this link holding?
	Student getValue() { return student; }
};


class StudentList {
private:
	StudentLink *head;
	StudentLink *tail;
public:
	StudentList();
	~StudentList();
	void insertHead(Student *s);
	void insertTail(Student *s);
	Student * deleteHead();
	bool isEmpty();
	bool findKey(std::string name);
	bool deleteKey(std::string name);
};
#endif