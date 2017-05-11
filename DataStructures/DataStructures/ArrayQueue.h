#pragma once
#include <stdexcept>
#include "Queue.h"

template<typename T>
class ArrayQueue : public Queue<T> {
public:
	// Constructor
	ArrayQueue(int max = 100);
	// Copy constructor
	ArrayQueue(const ArrayQueue &);
	// Destructor
	~ArrayQueue();

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
	const ArrayQueue<T>& operator = (const ArrayQueue<T>&);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const ArrayQueue<U>& q);

private:
	T* tab;
	int head;
	int tail;
	int maxSize;
	int cpt;

	void _copy(T* tabS);
	void _resize();
};

/////////////////////////////////

// Constructor
template<typename T>
ArrayQueue<T>::ArrayQueue(int max) {
	tab = new T[max];
	head = 0;
	tail = 0;
	cpt = 0;
	maxSize = max;
}

// Destructor
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete[] tab;
}

// Copy constructor
template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& q) {
	head = q.head;
	tail = q.tail;
	maxSize = q.maxSize;
	cpt = q.cpt;
	_copy(q.tab);
}

/////////////////////////////////

// Add an element to the queue
template <typename T>
void ArrayQueue<T>::add(const T& e) {
	if (cpt == maxSize) {
		_resize();
	}
	tab[tail] = e;
	tail = (tail + 1) % maxSize;
	cpt++;
}

// Remove an element from the queue (if not empty)
template <typename T>
T ArrayQueue<T>::remove() {
	if (empty()) {
		throw std::logic_error("The queue is empty !");
	}

	T element = tab[head];
	head = (head + 1) % maxSize;
	cpt--;
	return element;
}

// Peek an element from the queue without removing it (if not empty)
template <typename T>
T ArrayQueue<T>::peek() const {
	if (empty()) {
		throw std::logic_error("The queue is empty !");
	}

	return tab[head];
}

/////////////////////////////////

// Get the size of the queue
template <typename T>
int ArrayQueue<T>::size() const {
	return cpt;
}

// Know if the queue is empty
template <typename T>
bool ArrayQueue<T>::empty() const {
	return (cpt == 0);
}

/////////////////////////////////

// Surcharging the operator =
template <typename T>
const ArrayQueue<T>& ArrayQueue<T>::operator = (const ArrayQueue<T>& q) {

	if (this != &q) {

		if (tab != 0) {
			delete[] tab;
		}

		head = q.head;
		tail = q.tail;
		maxSize = q.maxSize;
		cpt = q.cpt;
		_copy(q.tab);
	}

	return *this;
}

// Surcharging the operator <<
template <typename T>
std::ostream& operator << (std::ostream& f, const ArrayQueue<T>& q) {

	int current = 0;
	while (current < q.cpt) {
		int index = ((q.tail - 1) - current) % q.maxSize;

		if (index < 0) {
			index += q.maxSize;
		}
		f << q.tab[index] << " ";
		current++;
	}

	return f;
}

/////////////////////////////////

// Copy a table in the current table
template <typename T>
void ArrayQueue<T>::_copy(T* tabS) {
	tab = new T[maxSize];
	for (int i = 0; i < maxSize; i++) {
		tab[i] = tabS[i];
	}
}

// Resize the queue
template <typename T>
void ArrayQueue<T>::_resize() {
	// Allocate a bigger table
	int newSize = maxSize * 2;
	T* newTab = new T[newSize];

	// Copy the values in the new table
	int current = 0;
	while (current < cpt) {
		int index = (head + current) % maxSize;
		newTab[current] = tab[index];
		current++;
	}

	// Delete the old tab
	delete[] tab;

	// Update the attributes
	tab = newTab;
	maxSize = newSize;
	tail = cpt;
	head = 0;
}