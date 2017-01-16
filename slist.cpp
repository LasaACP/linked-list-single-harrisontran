#include "slist.h"

/*
 Class Library File
 */

/**
 * LinkedList()
 * Default constructor for our LinkedList. Since there's no content
 * the head is instantiated as a null pointer and the list is of
 * length zero, by my convention. We'll be using LIFO implementation
 * here. Index 0 is the head.
 */
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
	length = 0;
}
/**
 * ~LinkedList()
 * Delete the pointers in the linked list and free up everything
 */
LinkedList::~LinkedList() {
	node * lagging = head;
	node * leading = head;
	while(leading != nullptr) {
		delete lagging;
		leading = leading->next;
	}
	if(leading != nullptr) {
		delete leading;
	}
	if (lagging != nullptr) {
		delete lagging;
	}
	length = 0;
}
/**
 * add(char code[], double lat_val, double lon_val)
 * Takes these values and creates a new node in the linked list to add these values
 */
void LinkedList::add(char code[], double lat_val, double lon_val) {
	node * newNode = new node();
	for (int i = 0; i < 5; i++) {
		newNode->iata[i] = code[i];
	}
	newNode->lat = lat_val;
	newNode->lon = lon_val;
	newNode->next = nullptr;
	if (head != nullptr) {
		tail->next = newNode;
	}
	tail = newNode;
	if (head == nullptr) {
		head = newNode;
	}
	length++;
}
/**
 * clear()
 * Clears all elements from the list. If you want to actually delete the data you use
 * the destructor. This doesn't free up data.
 */
void LinkedList::clear() {
	head = nullptr;
	tail = nullptr;
	length = 0;
}
/**
 * equals(LinkedList compare)
 * Checks if this list and compare have the same elements in the same order.
 * Returns false if either list is empty.
 */
bool LinkedList::equals(LinkedList compare) {
	node * a = head;
	node * b = compare.head;
	if (a == nullptr || b == nullptr) {
		return false;
	}
	while (a != nullptr || b != nullptr) {
		for (int i = 0; i < 5; i++) {
			if (a->iata[i] != b->iata[i]) {
				return false;
			}
		}
		if (a->lat != b->lat) {
			return false;
		}
		if (a->lon != b->lon) {
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return true;
}
/**
 * get(int index)
 * Fetch the item specified in this list. Indexing starts at 0 with the head being index 0
 */
node LinkedList::get(int index) {
	if (length <= 1) {
		// If the list is blank or there's only one item return the head
		return *head;
	} else {
		node * query = head;
		for (int i = 0; i < length; i++) {
			if (i == index) {
				return *query;
			} else {
				query = query->next;
			}
		}
	}
	return *head;
}
//insert(index, value)		//Inserts the element into this list before the specified index.
void LinkedList::insert(int index, char code[], double lat_val, double lon_val) {
	if(head == nullptr) {
		// If the list is empty use the add function in lieu of this one
		add(code, lat_val, lon_val);
	} else if (index >= length || index < 0) {
		cout << "Requested index is outside the bounds of the "
				"linked list. No insertion was made." << endl;
	} else {
		node * insertionNode = new node();
		node * pointer = head;
		for (int i = 0; i < 5; i++) {
			insertionNode->iata[i] = code[i];
		}
		insertionNode->lat = lat_val;
		insertionNode->lon = lon_val;
		for (int i = 0; i < length; i++) {
			if (index == 0 && i == 0) {
				insertionNode->next = head;
				head = insertionNode;
				length++;
				break;
			} else if (i == index - 1) {
				if (index == length - 1) {
					insertionNode->next = pointer->next;
					pointer->next = insertionNode;
					tail = pointer->next;
					length++;
					break;
				} else {
					insertionNode->next = pointer->next;
					pointer->next = insertionNode;
					length++;
					break;
				}

			}
			pointer = pointer->next;
		}
	}
}
//exchg(index1, index2)		//Switches the payload data of specified indexex.
void LinkedList::exchg(int index1, int index2) {
	node * pointer = head;
	node * one = new node();
	node * two = new node();
	if(index1 >= length || index1 < 0 || index2 >= length || index2 < 0) {
		cout << "No data could be exchanged as the provided parmeters fall out of bounds." << endl;
	} else if (index1 == index2) {
		//cout << "No data was exchanged as the provided parameters are equal." << endl;
	} else {
		for (int i = 0; i < length; i++) {
			if (i == index1) {
				for (int i = 0; i < 5; i++) {
					one->iata[i] = pointer->iata[i];
				}
				one->lat = pointer->lat;
				one->lon = pointer->lon;
			} else if (i == index2) {
				for (int i = 0; i < 5; i++) {
					two->iata[i] = pointer->iata[i];
				}
				two->lat = pointer->lat;
				two->lon = pointer->lon;
			}
			pointer = pointer->next;
		}
		pointer = head;
		for (int i = 0; i < length; i++) {
			if (i == index1) {
				for (int i = 0; i < 5; i++) {
					pointer->iata[i] = two->iata[i];
				}
				pointer->lat = two->lat;
				pointer->lon = two->lon;
			} else if (i == index2) {
				for (int i = 0; i < 5; i++) {
					pointer->iata[i] = one->iata[i];
				}
				pointer->lat = one->lat;
				pointer->lon = one->lon;
			}
			pointer = pointer->next;
		}
	}
}
// isEmpty()				//Returns true if this list contains no elements.
bool LinkedList::isEmpty() {
	if(length == 0) {
		return true;
	} else {
		return false;
	}
}
// remove(index)			//Removes the element at the specified index from this list.
void LinkedList::remove(int index) {
	if (head == nullptr) {
		// If the list is empty...
		cout << "The list is empty, so no node could be removed." << endl;
	} else if (index >= length || index < 0) {
		cout << "Requested index is outside the bounds of the "
				"linked list. No node was removed." << endl;
	} else {
		node * pointer = head;
		for(int i = 0; i < length; i++) {
			if(i == 0 && index == 0) {
				head = head->next;
				length--;
				break;
			} else if (i == index - 1) {
				pointer->next = pointer->next->next;
				length--;
				break;
			}
			pointer = head->next;
		}
	}
}
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
void LinkedList::set(int index, char code[], double lat_val, double lon_val) {
	if(head == nullptr) {
		// If the list is empty...
		cout << "The list is empty, so no node could be set." << endl;
	} else if (index >= length) {
		cout << "Requested index is outside the bounds of the "
				"linked list. No node was set." << endl;
	} else {
		node * pointer = head;
		for (int i = 0; i < length; i++) {
			if (i == index) {
				for (int i = 0; i < 5; i++) {
					pointer->iata[i] = code[i];
				}
				pointer->lat = lat_val;
				pointer->lon = lon_val;
			}
			pointer = pointer->next;
		}
	}
}
// size()					//Returns the number of elements in this list.
int LinkedList::size() {
	return length;
}
// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
LinkedList LinkedList::subList(int start, int sublength) {
	LinkedList sublist;
	if(start + sublength-1 > length || start < 0 || start > length || sublength <= 0) {
		cout << "A blank list was returned as the requested parameters have extraneous bounds." << endl;
		return sublist;
	} else {
		node * pointer = head;
		for(int i = 0; i < length; i++) {
			if(i >= start && i < start+sublength) {
				sublist.add(pointer->iata,pointer->lat,pointer->lon);
			}
			pointer = pointer->next;
		}
		return sublist;
	}
}
// toString()				//Converts the list to a printable string representation.
string LinkedList::toString() {
	string output = "";
	node * pointer = head;
	while (pointer != nullptr) {
		output.append(
				string(pointer->iata) + " " + patch::to_string(pointer->lat)
						+ " " + patch::to_string(pointer->lon) + "\n");
		pointer = pointer->next;
	}
	return output;
}
