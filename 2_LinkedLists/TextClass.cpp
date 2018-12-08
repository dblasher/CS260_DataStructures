 //lab 3 - TextClass.cpp
//Daniel Blasher


#include "TextClass.hpp"

TextClass::TextClass() {
	head = tail = iter = nullptr;
}

TextClass::~TextClass(){
	while (!isEmpty()) {
		deleteHead();
	}
}


void TextClass::insertHead(char val){
	//create a link with char parameter
	if(head == nullptr)
		head = tail = new Link(val);
	else {
		//new link points to current head and has nothing before it
		Link *newHead = new Link(val, head, nullptr);
		head->setPrevious(newHead);
		head = newHead;
	}
}

void TextClass::insertTail(char val){
	if (tail == nullptr)
		head = tail = new Link(val);
	else {
		Link *newTail = new Link(val, nullptr, tail);
		tail->setNext(newTail);
		tail = newTail;
	}
}

char TextClass::deleteHead(){
	if (isEmpty())
		throw std::underflow_error("List is empty");
	Link *temp = head;
	//need the char returning
	char value = temp->getValue();
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
	else{
		//otherwise head shouldn't point back to anything
		head->setPrevious(nullptr);

		delete temp;
		return value;
	}
}

char TextClass::deleteTail(){
	if (isEmpty())
		throw std::underflow_error("List is empty");

	Link *temp = tail;
	char value = temp->getValue();
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

bool TextClass::isEmpty(){
	//could use tail, but either one should do if List is properly implemented
	if (head == nullptr)
		return true;
	else
		return false;
}

bool TextClass::findKey(char key){
	if (isEmpty())
		return false;
	Link *start = head;
	//have we already found this key? If yes we should resume searching after iter
	if (iter->getValue() == key)
		start = iter->getNext();
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
	//did not find a single occurence of the char key anywhere in the list
	iter = nullptr;
	return false;

}

bool TextClass::deleteKey(char key) {
	//don't forget to check if this is iter
	if (isEmpty())
		return false;

	for (Link *current = head; current; current = current->getNext()) {
		if (current->getValue() == key) {

			if (deleteHeadOrTail(current))
				return true;

			//reassign pointers
			current->getPrevious()->setNext(current->getNext());
			current->setPrevious(current ->getPrevious());
			if (current == iter)
				iter = nullptr;

			delete current;
			return true;
		}
	}
	return false;
}

bool TextClass::insertKey(char key) {
	if (iter == nullptr)
		return false;

	Link  *newLink = new Link(key, iter, iter->getPrevious());
	iter->getPrevious()->setNext(newLink);
	iter->setPrevious(newLink);
	return true;

}

bool TextClass::deleteIter(){
	if (iter == nullptr)
		return false;

	Link *temp = iter;
	//reassign pointers
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

std::string TextClass::displayList(){

	std::string display;
	std::ostringstream s1;
	//check for empty list first
	if (isEmpty()) {
		display = "List is empty";
		return display;
	}
	//loop through the list, appending current->getValue() to a string stream.
	for (Link *current = head; current; current = current->getNext()) {
		s1 << current->getValue(); //I assume we don't want to add any spaces?
	}
	//assign string to the string stream and return it
	display = s1.str();
	return display;
}

bool TextClass::deleteHeadOrTail(Link *key) {
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
void TextClass::appendList(TextClass *list2) {
	Link *next = list2->head;
	while (next) {
		insertTail(next->getValue());
		next = next->getNext();
	}
}

//	Link (char l, Link *n = nullptr, Link * p = nullptr): letter(l), next (n), previous(p){}



