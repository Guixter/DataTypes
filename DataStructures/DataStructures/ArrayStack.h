#pragma once
#include <stdexcept>
#include "Stack.h"

template <typename T>
class ArrayStack : public Stack<T> {
public:

	// Constructor
	ArrayStack(int max = 100);
	// Copy constructor
	ArrayStack(const ArrayStack& stack);
	// Destructor
	~ArrayStack();

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
	const ArrayStack<T>& operator = (const ArrayStack<T>& s);

private:
	T* tab;
	int maxSize;
	int top;

	void _copy(T* tabS);
	void _resize();
};

/////////////////////////////////

// Constructor
template<typename T>
ArrayStack<T>::ArrayStack(int max) {
	tab = new T[max];
	top = 0;
	maxSize = max;
}

// Destructor
template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete[] tab;
}

// Copy constructor
template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack& s) {
	maxSize = s.maxSize;
	top = s.top;
	_copy(s.tab);
}

/////////////////////////////////

// Push an element in the stack
template <typename T>
void ArrayStack<T>::push(const T& e) {
	if (top == maxSize) {
		_resize();
	}

	tab[top] = e;
	top++;
}

// Pop an element from the stack (if not empty)
template <typename T>
T ArrayStack<T>::pop() {
	if (empty()) {
		throw std::logic_error("The stack is empty !");
	}

	top--;
	return tab[top];
}

// Peek an element from the stack without removing it (if not empty)
template <typename T>
T ArrayStack<T>::peek() const {
	if (empty()) {
		throw std::logic_error("The stack is empty !");
	}

	return tab[top - 1];
}

/////////////////////////////////

// Get the size of the stack
template <typename T>
int ArrayStack<T>::size() const {
	return top;
}

// Know if the stack is empty
template <typename T>
bool ArrayStack<T>::empty() const {
	return (top == 0);
}

// Print the stack
template <typename T>
void ArrayStack<T>::print(std::ostream& f) const {
	for (int i = 0; i < top; i++) {
		f << tab[i] << " ";
	}
}

/////////////////////////////////

// Surcharging the operator =
template <typename T>
const ArrayStack<T>& ArrayStack<T>::operator = (const ArrayStack<T>& s) {

	if (this != &s) {

		if (tab != 0) {
			delete[] tab;
		}

		maxSize = s.maxSize;
		top = s.top;
		_copy(s.tab);
	}

	return *this;
}

/////////////////////////////////

// Copy a table in the current table
template <typename T>
void ArrayStack<T>::_copy(T* tabS) {
	tab = new T[maxSize];
	for (int i = 0; i < maxSize; i++) {
		tab[i] = tabS[i];
	}
}

// Resize the stack
template <typename T>
void ArrayStack<T>::_resize() {
	// Allocate a bigger table
	int newSize = maxSize * 2;
	T* newTab = new T[newSize];

	// Copy the values in the new table
	for (int i = 0; i < maxSize; i++) {
		newTab[i] = tab[i];
	}

	// Delete the old tab
	delete[] tab;

	// Update the attributes
	tab = newTab;
	maxSize = newSize;
}