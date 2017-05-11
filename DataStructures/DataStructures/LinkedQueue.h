#pragma once
#include <stdexcept>
#include "Queue.h"

template<typename T>
class LinkedQueue : public Queue<T> {
public:
	// Constructor
	LinkedQueue();
	// Copy constructor
	LinkedQueue(const LinkedQueue &);
	// Destructor
	~LinkedQueue();

	// Add an element to the queue
	void add(const T&) override;
	// Remove an element from the queue (if not empty)
	T remove() throw (std::logic_error) override;
	// Peek an element from the queue without removing it (if not empty)
	T peek() const throw (std::logic_error) override;

	// Get the size of the queue
	int size() const override;
	// Know if the queue is empty
	bool empty() const override;

	// Operator surcharges
	const LinkedQueue<T>& operator = (const LinkedQueue<T>&);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const LinkedQueue<U>& q);

private:

	class Node {
	public:
		T value;
		Node* next;
		Node(const T& data_item, Node* next_ptr = NULL) : value(data_item), next(next_ptr) { }
	};

	Node* head;
	Node* tail;
	int cpt;

	void _copy(Node* n);
	void _destroy();
	void _print(std::ostream& f) const;
};

/////////////////////////////////

// Constructor
template <typename T>
LinkedQueue<T>::LinkedQueue() {
	head = NULL;
	tail = NULL;
	cpt = 0;
}

// Copy constructor
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& queue) {
	cpt = queue.cpt;
	_copy();
}

// Destructor
template <typename T>
LinkedQueue<T>::~LinkedQueue() {
	_destroy();
}

/////////////////////////////////

// Add an element to the queue
template <typename T>
void LinkedQueue<T>::add(const T& elt) {
	Node* n = new Node(elt, NULL);
	if (empty()) {
		head = n;
		tail = n;
	} else {
		tail->next = n;
		tail = n;
	}

	cpt++;
}

// Remove an element from the queue (if not empty)
template <typename T>
T LinkedQueue<T>::remove() {
	if (empty()) {
		throw std::logic_error("Empty queue !");
	}

	T value = head->value;
	Node* old = head;
	head = head->next;
	delete old;

	cpt--;
	if (empty()) {
		tail = NULL;
	}

	return value;
}

// Peek an element from the queue without removing it (if not empty)
template <typename T>
T LinkedQueue<T>::peek() const {
	if (empty()) {
		throw std::logic_error("Empty queue !");
	}

	return head->value;
}

/////////////////////////////////

// Get the size of the queue
template <typename T>
int LinkedQueue<T>::size() const {
	return cpt;
}

// Know if the queue is empty
template <typename T>
bool LinkedQueue<T>::empty() const {
	return (cpt <= 0);
}

/////////////////////////////////

// Surcharging the = operator
template <typename T>
const LinkedQueue<T>& LinkedQueue<T>::operator = (const LinkedQueue<T>& q) {
	if (this != &s) {
		head = q.head;
		tail = q.tail;
		cpt = q.cpt;
		_copier(q.tab);
	}

	return *this;
}

// Surcharging the << operator
template <typename T>
std::ostream& operator << (std::ostream& f, const LinkedQueue<T>& s) {
	s._print(f);
	return f;
}

/////////////////////////////////

// Copy a queue
template <typename T>
void LinkedQueue<T>::_copy(Node* n) {
	if (n == NULL) {
		head = NULL;
		tail = NULL;
		cpt = 0;
		return;
	}

	head = new Node(n->value);
	tail = head;
	for (; n != NULL; n = n->next) {
		tail->next = new Node(n->value);
		tail = tail->next;
	}
}

// Destroy a queue
template <typename T>
void LinkedQueue<T>::_destroy() {
	Node* c = head;
	while (c != NULL) {
		Node* next = c->next;
		delete c;
		c = next;
	}
}

// Print a queue
template <typename T>
void LinkedQueue<T>::_print(std::ostream& f) const {
	for (Node* n = head; n != NULL; n = n->next) {
		f << n->value << " ";
	}
}