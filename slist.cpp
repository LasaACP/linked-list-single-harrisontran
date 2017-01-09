/* Class Library File */
#include "slist.h"
#include <sstream>
#include <string>

namespace patch {
template<typename T> std::string to_string(const T& n) {
	std::ostringstream stm;
	stm << n;
	return stm.str();
}
}

// Constructor
LinkedList::LinkedList() {
	head = NULL;
}
// Destructor
LinkedList::~LinkedList() {
	Node *ptr = head;
	Node *temp;
	// Cycle through list and release all node data
	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		delete temp; // release the memory pointed to by temp
	}
}
// add(value)				//Adds a new value to the end of this list.
void LinkedList::add(Airport *a) {
	Node *n = new Node();
	n->locationID[0] = a->code[0];
	n->locationID[1] = a->code[1];
	n->locationID[2] = a->code[2];
	n->locationID[3] = a->code[3];
	n->locationID[4] = a->code[4];
	n->lat = a->latitude;
	n->lon = a->longitude;
	n->next = head;
	head = n;
}
// clear()					//Removes all elements from this list.
void LinkedList::clear() {
	Node *ptr = head;
	Node *temp;
	// Cycle through list and release all node data
	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		delete temp;
	}
}
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
bool LinkedList::equals(LinkedList l) {
	Node *ptr_one = head;
	Node *ptr_two = l.head;
	while (ptr_one->next != NULL) {
		if (std::string(ptr_one->locationID).compare(
				std::string(ptr_two->locationID))
				&& ptr_one->lat == ptr_two->lat
				&& ptr_one->lon == ptr_two->lon) {
			ptr_one = ptr_one->next;
			ptr_two = ptr_two->next;
		} else {
			return false;
		}
	}
	if (ptr_two->next != NULL) {
		return false;
	}
	return true;
}
Airport LinkedList::nodeToAirport(Node n) {
	Airport temp;
	temp.code[0] = n.locationID[0];
	temp.code[1] = n.locationID[1];
	temp.code[2] = n.locationID[2];
	temp.code[3] = n.locationID[3];
	temp.code[4] = n.locationID[4];
	temp.latitude = n.lat;
	temp.longitude = n.lon;
	return temp;
}
//get(index)				//Returns the element at the specified index in this list.
Airport LinkedList::get(int i) {
	int length = size();
	int increment = length - 1 - i;
	int counter = 0;
	Node *ptr = head;
	while (ptr->next != NULL && counter != increment) {
		counter++;
		ptr = ptr->next;
	}
	if (counter == increment) {
		return nodeToAirport(*ptr);
	}
}
//insert(index, value)		//Inserts the element into this list before the specified index.
void LinkedList::insert(int i, Airport *a) {
	int length = size();
	int increment = length - 1 - i;
	int counter = 0;
	Node *ptr = head;
	Node *newNode = new Node();
	newNode->locationID[0] = a->code[0];
	newNode->locationID[1] = a->code[1];
	newNode->locationID[2] = a->code[2];
	newNode->locationID[3] = a->code[3];
	newNode->locationID[4] = a->code[4];
	ptr->lat = a->latitude;
	ptr->lon = a->longitude;
	while (ptr->next != NULL && counter < increment - 1) {
		counter++;
		ptr = ptr->next;
	}
	if (counter == increment - 1) {
		ptr->next = newNode;
		ptr = ptr->next;
	}
}
//exchg(index1, index2)		//Switches the payload data of specified indexex.
void LinkedList::exchg(int index1, int index2) {

}
// isEmpty()				//Returns true if this list contains no elements.
bool LinkedList::isEmpty() {
	if (head == NULL) {
		return true;
	} else {
		return false;
	}
}
// remove(index)			//Removes the element at the specified index from this list.
void LinkedList::remove(int i) {
	int length = size();
	int increment = length - 1 - i;
	int counter = 0;
	Node *ptr = head;
	while (ptr->next != NULL && counter != increment - 1) {
		counter++;
		ptr = ptr->next;
	}
	if (counter == increment - 1) {
		ptr->next = ptr->next->next;
		delete ptr->next;
	}
}
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
void LinkedList::set(int i, Airport *a) {
	int length = size();
	int increment = length - 1 - i;
	int counter = 0;
	Node *ptr = head;
	while (ptr->next != NULL && counter != increment) {
		counter++;
		ptr = ptr->next;
	}
	if (counter == increment) {
		ptr->locationID[0] = a->code[0];
		ptr->locationID[1] = a->code[1];
		ptr->locationID[2] = a->code[2];
		ptr->locationID[3] = a->code[3];
		ptr->locationID[4] = a->code[4];
		ptr->lat = a->latitude;
		ptr->lon = a->longitude;
	}
}
// size()					//Returns the number of elements in this list.
int LinkedList::size() {
	int counter = 0;
	Node *ptr = head;
	while (ptr->next != NULL) {
		counter++;
		ptr = ptr->next;
	}
	counter++;
	return counter;
}
// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.

// toString()				//Converts the list to a printable string representation.
string LinkedList::toString() {
	string output;
	Node *ptr = head;
	while (ptr->next != NULL) {
		output += std::string(ptr->locationID) + " "
				+ patch::to_string(ptr->lat) + " " + patch::to_string(ptr->lon)
				+ "\n";
		ptr = ptr->next;
	}
	output += std::string(ptr->locationID) + " " + patch::to_string(ptr->lat)
			+ " " + patch::to_string(ptr->lon) + "\n";

	return output;
}
