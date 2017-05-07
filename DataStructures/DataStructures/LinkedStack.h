#pragma once
#include <stdexcept>


template <typename T>
class LinkedStack {
public:

	// constructors and destructors
	LinkedStack();
	LinkedStack(const LinkedStack& stack);
	~LinkedStack();

	// setters
	void push(const T& elt);
	T pop() throw (std::logic_error);

	// getters
	bool empty() const;
	int size() const;
	const T& peek() const throw (std::logic_error);

	// operator surcharges
	const LinkedStack<T>& operator = (const LinkedStack<T>& s);
	template <typename U> friend std::ostream& operator<< (std::ostream& f, const LinkedStack<U>& s);

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
	void _print(std::ostream& f) const;
};

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

// Push an element
template <typename T>
void LinkedStack<T>::push(const T& elt) {
	top = new Node(elt, top);
	cpt++;
}

// Pop an element (if there is an element to pop)
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

// Know if the stack is empty
template <typename T>
bool LinkedStack<T>::empty() const {
	return (cpt <= 0);
}

// Know the size of the stack
template <typename T>
int LinkedStack<T>::size() const {
	return cpt;
}

// Peek the top element of the stack (if it exists)
template <typename T>
const T& LinkedStack<T>::peek() const {
	if (empty()) {
		throw std::logic_error("Empty stack !");
	}

	return top->value;
}

// Surcharging the = operator
template <typename T>
const LinkedStack<T>& LinkedStack<T>::operator = (const LinkedStack<T>& s) {
	if (this != &s) {

		delete 

		if (tab != 0) {
			delete[] tab;
		}

		tete = f.tete;
		queue = f.queue;
		tailleMax = f.tailleMax;
		cpt = f.cpt;
		_copier(f.tab);
	}

	return *this;
}

// Copy a stack
template <typename T>
void LinkedStack<T>::_copy(Node* n) {
	if (n == NULL) {
		top = NULL;
		return;
	}

	top = new Node(n->value);
	Node* c = top;
	for (; n != NULL ; n = n->next) {
		c->next = new Node(n->value);
		c = c->next;
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

// Print a stack
template <typename T>
void LinkedStack<T>::_print(std::ostream& f) const {
	for (Node* n = top; n != NULL; n = n->next) {
		f << n->value << " ";
	}
}


// Surcharging the << operator
template <typename T>
std::ostream& operator << (std::ostream& f, const LinkedStack<T>& s) {
	s._print(f);
	return f;
}