//lab 3 - StudentList.cpp
//Daniel Blasher


#include "StudentList.hpp"


StudentList::StudentList(){
	head = tail = nullptr;
}

StudentList::~StudentList(){
	while (!isEmpty()) {
		deleteHead();
	}
}

void StudentList::insertHead(Student *s){
	if (head == nullptr)
		head = tail = new StudentLink(*s);

	else 
		head = new StudentLink(*s, head);
}

void StudentList::insertTail(Student *s){
	if (tail == nullptr)
		head = tail = new StudentLink(*s);
	else {
		StudentLink *temp = new StudentLink(*s);
		tail->setNext(temp);
		tail = temp;
	}
}

Student * StudentList::deleteHead(){
	if (head == nullptr)
		throw std::underflow_error("Student List is empty");

	StudentLink *temp = head;
	Student * value = new Student();
	value->setName (temp->getValue().getName());
	//when using a pointer, you use an arrow
	//when you have the object itself you use a dot
	value->setAge(temp->getValue().getAge());
	
	head = head->getNext();
	if (head == nullptr)
		tail = nullptr;
	delete temp;
	return value;
}

bool StudentList::isEmpty(){
	if (head == nullptr)
		return true;
	else
		return false;
}

bool StudentList::findKey(std::string name){
	if (isEmpty())
		return false;
	for (StudentLink *current = head; current; current = current->getNext()) {
		//have to use a dot instead of arrow. Arrows are for pointer types, dots are for object types
		if (current->getValue().getName() == name)
		return true;
	}
	return false;
}

bool StudentList::deleteKey(std::string name) {
	if (isEmpty())
		return false;
	if (head->getValue().getName() == name){
		deleteHead();
		return true;
	}
	StudentLink *previous = head;
	while(previous->getNext() != nullptr) {
		StudentLink *current = previous->getNext();
		if (current->getValue().getName() == name) {
			previous->setNext(current->getNext());
			if (tail == current)
				tail = previous;
			delete current;
			return true;
		}
		previous = previous->getNext();
	}
	return false;
}