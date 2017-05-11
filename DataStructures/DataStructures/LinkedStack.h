#pragma once
#include <stdexcept>
#include "Stack.h"

template <typename T>
class LinkedStack : public Stack<T> {
public:

	// Constructor
	LinkedStack();
	// Copy constructor
	LinkedStack(const LinkedStack& stack);
	// Destructor
	~LinkedStack();

	// Push an element in the stack
	void push(const T& elt) override;
	// Pop an element from the stack (if not empty)
	T pop() throw (std::logic_error) override;
	// Peek an element from the stack without removing it (if not empty)
	T peek() const throw (std::logic_error) override;

	// Get the size of the stack
	int size() const override;
	// Know if the stack is empty
	bool empty() const override;
	// Print the stack
	void print(std::ostream& f) const override;

	// Operator surcharges
	const LinkedStack<T>& operator = (const LinkedStack<T>& s);

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
	void _print(Node* n, std::ostream& f) const;
};

/////////////////////////////////

// Constructor
template <typename T>
LinkedStack<T>::LinkedStack() {
	top = NULL;
	cpt = 0;
}

// Copy constructor
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack& stack) {
	cpt = stack.cpt;
	_copy();
}

// Destructor
template <typename T>
LinkedStack<T>::~LinkedStack() {
	_destroy();
}

/////////////////////////////////

// Push an element in the stack
template <typename T>
void LinkedStack<T>::push(const T& elt) {
	top = new Node(elt, top);
	cpt++;
}

// Pop an element from the stack (if not empty)
template <typename T>
T LinkedStack<T>::pop() {
	if (empty()) {
		throw std::logic_error("Empty stack !");
	}

	T value = top->value;
	Node* old = top;
	top = top->next;
	delete old;
	cpt--;
	return value;
}

// Peek an element from the stack without removing it (if not empty)
template <typename T>
T LinkedStack<T>::peek() const {
	if (empty()) {
		throw std::logic_error("Empty stack !");
	}

	return top->value;
}

/////////////////////////////////

// Get the size of the stack
template <typename T>
int LinkedStack<T>::size() const {
	return cpt;
}

// Know if the stack is empty
template <typename T>
bool LinkedStack<T>::empty() const {
	return (cpt <= 0);
}

// Print the stack
template <typename T>
void LinkedStack<T>::print(std::ostream& f) const {
	_print(top, f);
}

/////////////////////////////////

// Surcharging the = operator
template <typename T>
const LinkedStack<T>& LinkedStack<T>::operator = (const LinkedStack<T>& s) {
	if (this != &s) {
		top = s.top;
		cpt = s.cpt;
		_copier(s.tab);
	}

	return *this;
}

/////////////////////////////////

// Copy a stack
template <typename T>
void LinkedStack<T>::_copy(Node* n) {
	if (n == NULL) {
		top = NULL;
		cpt = 0;
		return;
	}

	top = new Node(n->value);
	Node* current = top;
	for (; n != NULL ; n = n->next) {
		current->next = new Node(n->value);
		current = current->next;
	}
}

// Destroy a stack
template <typename T>
void LinkedStack<T>::_destroy() {
	Node* c = top;
	while (c != NULL) {
		Node* next = c->next;
		delete c;
		c = next;
	}
}

// Print a node
template <typename T>
void LinkedStack<T>::_print(Node* n, std::ostream& f) const {
	if (n != NULL) {
		_print(n->next, f);
		f << n->value << " ";
	}
}