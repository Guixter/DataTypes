#pragma once
#include <stdexcept>
#include "List.h"

template<typename T>
class LinkedList : public List<T> {
public:
	// Constructor
	LinkedList();
	// Copy constructor
	LinkedList(const LinkedList & l);
	// Destructor
	~LinkedList();

	// Add an element in the list
	void add(int index, const T& elt) override;
	// Set an element in the list (if the index is valid)
	void set(int index, const T& elt) override;
	// Remove an element from the list (if the index is valid)
	T& remove(int index) throw (std::logic_error) override;
	// Get an element from the list (if the index is valid)
	T& get(int index) const throw (std::logic_error) override;
	// Clear the list
	void clear() override;

	// Know if an element is in the list
	bool contains(T elt) const override;
	// Get the index of an element in the list (-1 if not in the list)
	int indexOf(T elt) const override;
	// Get the size of the list
	int size() const override;
	// Know if the list is empty
	bool empty() const override;
	// Print the list
	void print(std::ostream& f) const override;

	// Operator surcharges
	const LinkedList<T>& operator = (const LinkedList<T>&);

private:

	class Node {
	public:
		T value;
		Node* next;
		Node(const T& data_item, Node* next_ptr = NULL) : value(data_item), next(next_ptr) { }
	};

	Node* top;
	int cpt;

	void _copy(Node* n);
	void _destroy();
};

/////////////////////////////////

// Constructor
template <typename T>
LinkedList<T>::LinkedList() {
	top = NULL;
	cpt = 0;
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& l) {
	cpt = l.cpt;
	_copy(top);
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
	_destroy();
}

/////////////////////////////////

// Add an element in the list
template <typename T>
void LinkedList<T>::add(int index, const T& elt) {
	if (index < 0 || index > cpt) {
		throw std::logic_error("Bad index.");
	}

	if (empty()) {
		top = new Node(elt);
	} else {
		if (index == 0) {
			Node *n = new Node(elt, top);
			top = n;
		} else {
			// Find the node of index (index-1)
			Node* previous = top;
			for (int i = 0 ; i + 1 < index ; i++) {
				previous = previous->next;
				i++;
			}

			// Add the new node
			Node *n = new Node(elt, previous->next);
			previous->next = n;
		}
	}

	cpt++;
}

// Set an element in the list (if the index is valid)
template <typename T>
void LinkedList<T>::set(int index, const T& elt) {
	if (index < 0 || index >= cpt) {
		throw std::logic_error("Bad index.");
	}

	// Go to the ith element of the list
	Node *n = top;
	for (int i = 0; i < index; i++) {
		n = n->next;
	}

	// Update the value
	n->value = elt;
}

// Remove an element from the list (if the index is valid)
template <typename T>
T& LinkedList<T>::remove(int index) {
	if (index < 0 || index >= cpt) {
		throw std::logic_error("Bad index.");
	}

	T val;
	if (index == 0) {
		Node* old = top;
		top = top->next;
		val = old->value;
		delete old;
	} else {
		// Get the (i-1)th element
		Node *previous = top;
		for (int i = 0; i + 1 < index; i++) {
			previous = previous->next;
		}

		// Remove the ith element
		Node *old = previous->next;
		val = old->value;
		previous->next = old->next;
		delete old;
	}

	cpt--;
	return val;
}

// Get an element from the list (if the index is valid)
template <typename T>
T& LinkedList<T>::get(int index) const {
	if (index < 0 || index >= cpt) {
		throw std::logic_error("Bad index.");
	}

	// Get the ith element
	Node *n = top;
	for (int i = 0; i < index; i++) {
		n = n->next;
	}

	return n->value;
}

// Clear the list
template <typename T>
void LinkedList<T>::clear() {
	_destroy();
	top = NULL;
	cpt = 0;
}

/////////////////////////////////

// Know if an element is in the list
template <typename T>
bool LinkedList<T>::contains(T elt) const {
	return (indexOf(elt) != -1);
}

// Get the index of an element in the list (-1 if not in the list)
template <typename T>
int LinkedList<T>::indexOf(T elt) const {
	int i = 0;
	for (Node* n = top; n != NULL; n = n->next) {
		if (n->value == elt) {
			return i;
		}
		i++;
	}

	return -1;
}

// Get the size of the list
template <typename T>
int LinkedList<T>::size() const {
	return cpt;
}

// Know if the list is empty
template <typename T>
bool LinkedList<T>::empty() const {
	return (cpt == 0);
}

// Print the list
template <typename T>
void LinkedList<T>::print(std::ostream& f) const {
	for (Node *n = top; n != NULL; n = n->next) {
		f << n->value << " ";
	}
}

/////////////////////////////////

// Surcharging the = operator
template <typename T>
const LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& l) {
	if (this != &l) {
		cpt = l.cpt;
		_copy(l.top);
	}

	return *this;
}

/////////////////////////////////

// Copy a list
template <typename T>
void LinkedList<T>::_copy(Node* n) {
	if (n == NULL) {
		top = NULL;
		cpt = 0;
		return;
	}

	top = new Node(n->value);
	Node *c = top;
	for (; n != NULL; n = n->next) {
		c->next = new Node(n->value);
		c = c->next;
	}
}

// Destroy a list
template <typename T>
void LinkedList<T>::_destroy() {
	Node* c = top;
	while (c != NULL) {
		Node* next = c->next;
		delete c;
		c = next;
	}
}
