//lab 6 - LinkedList.cpp
//adapted from lab 6 TextClass.cpp
//Daniel Blasher


#include "LinkedList.h"

LinkedList::LinkedList() {
	head = tail = iter = nullptr;
}

LinkedList::~LinkedList() {
	while (!isEmpty()) {
		deleteHead();
	}
}


void LinkedList::insertHead(std::string val) {
	//create a link with std::string parameter
	if (head == nullptr)
		head = tail = new Link(val);
	else {
		//new link postd::strings to current head and has nothing before it
		Link *newHead = new Link(val, head, nullptr);
		head->setPrevious(newHead);
		head = newHead;
	}
}

void LinkedList::insertTail(std::string val) {
	if (tail == nullptr)
		head = tail = new Link(val);
	else {
		Link *newTail = new Link(val, nullptr, tail);
		tail->setNext(newTail);
		tail = newTail;
	}
}

std::string LinkedList::deleteHead() {
	if (isEmpty())
		throw std::underflow_error("List is empty");
	Link *temp = head;
	//need the std::string returning
	std::string value = temp->getValue();
	//head is now the next item in the list
	head = head->getNext();
	//is head now at the end of the list? If yes, then update tail
	if (head == nullptr) {
		tail = nullptr;
		//don't forget to check if this is iter
		if (temp == iter)
			iter = nullptr;
		delete temp;
		return value;
	}
	else {
		//otherwise head shouldn't postd::string back to anything
		head->setPrevious(nullptr);

		delete temp;
		return value;
	}
}

std::string LinkedList::deleteTail() {
	if (isEmpty())
		throw std::underflow_error("List is empty");

	Link *temp = tail;
	std::string value = temp->getValue();
	tail = tail->getPrevious();

	if (tail == nullptr) {
		head = nullptr;
		if (temp == iter)
			iter = nullptr;
		delete temp;
		return value;
	}
	else {
		tail->setNext(nullptr);

		delete temp;
		return value;
	}
}

bool LinkedList::isEmpty() {
	//could use tail, but either one should do if List is properly implemented
	if (head == nullptr)
		return true;
	else
		return false;
}

bool LinkedList::findKey(std::string key) {
	if (isEmpty())
		return false;
	Link *start = head;
	//have we already found this key? If yes we should resume searching after iter
	if (iter) {
		if (iter->getValue() == key)
			start = iter->getNext();
	}
	//starting at head or next after iter, loop through the list until we find the key or we reach a nullptr or we reach iter
	for (Link *current = start; current != iter; current = current->getNext()) {
		//wrap around back to beginning and keep looking
		if (current == nullptr)
			current = head;

		if (current->getValue() == key) {
			iter = current;
			return true;
		}
	}
	//did not find a single occurence of the std::string key anywhere in the list
	iter = nullptr;
	return false;

}

bool LinkedList::deleteKey(std::string key) {
	//don't forget to check if this is iter
	if (isEmpty())
		return false;

	for (Link *current = head; current; current = current->getNext()) {
		if (current->getValue() == key) {

			if (deleteHeadOrTail(current))
				return true;

			//reassign postd::stringers
			current->getPrevious()->setNext(current->getNext());
			current->setPrevious(current->getPrevious());
			if (current == iter)
				iter = nullptr;

			delete current;
			return true;
		}
	}
	return false;
}

bool LinkedList::insertKey(std::string key) {
	if (iter == nullptr)
		return false;

	Link  *newLink = new Link(key, iter, iter->getPrevious());
	iter->getPrevious()->setNext(newLink);
	iter->setPrevious(newLink);
	return true;

}

bool LinkedList::deleteIter() {
	if (iter == nullptr)
		return false;

	Link *temp = iter;
	//reassign postd::stringers
	if (deleteHeadOrTail(iter)) {

		delete temp;
		return true;
	}
	else {
		iter->getNext()->setPrevious(iter->getPrevious());
		iter->getPrevious()->setNext(iter->getNext());
		//need to eliminate this repetition of lines 155-157 in the final version
		delete temp;
		iter = nullptr;
		return true;
	}

}

std::string LinkedList::displayList() {

	std::string display;
	std::ostringstream s1;
	//check for empty list first
	if (isEmpty()) {
		display = "List is empty";
		return display;
	}
	//loop through the list, appending current->getValue() to a string stream.
	for (Link *current = head; current; current = current->getNext()) {
		s1 << current->getValue() << " ";
	}
	//assign string to the string stream and return it
	display = s1.str();
	return display;
}

bool LinkedList::deleteHeadOrTail(Link *key) {
	if (key == head) {
		deleteHead();
		return true;
	}
	if (key == tail) {
		deleteTail();
		return true;
	}
	else
		return false;

}
//part 2 of the lab
void LinkedList::appendList(LinkedList *list2) {
	Link *next = list2->head;
	while (next) {
		insertTail(next->getValue());
		next = next->getNext();
	}
}

//	Link (std::string l, Link *n = nullptr, Link * p = nullptr): letter(l), next (n), previous(p){}



