/*
 * slist.h
 * Header file for single linked list class library
 *  Created on: Jan 14, 2017
 *      Author: Harrison Tran
 */
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#ifndef SLIST_H
#define SLIST_H

// Need this patch here because otherwise I can't append integers or doubles to strings
namespace patch {
template<typename T> std::string to_string(const T& n) {
	std::ostringstream stm;
	stm << n;
	return stm.str();
}
}

struct node {
	char iata[5];
	double lat;
	double lon;
	node * next;
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void add(char iata[], double lat, double lon);
	void insert(int index, char iata[], double lat, double lon);
	void set(int index, char iata[], double lat, double lon);
	void exchg(int index1, int index2);

	node get(int index);

	void remove(int index);
	void clear();

	bool equals(LinkedList compare);
	LinkedList subList(int start, int sublength);
	bool isEmpty();
	int size();
	string toString();

	node * head;
	node * tail;
	int length;
};

#endif /*SLIST_H*/

// clear()					//Removes all elements from this list.
// equals(list)				//Returns true if the two lists contain the same elements in the same order.

//insert(index, value)		//Inserts the element into this list before the specified index.
//exchg(index1, index2)		//Switches the payload data of specified indexex.
// isEmpty()				//Returns true if this list contains no elements.
// remove(index)			//Removes the element at the specified index from this list.
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
// size()					//Returns the number of elements in this list.
// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
