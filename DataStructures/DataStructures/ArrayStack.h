#pragma once
#include <stdexcept>
#include "Stack.h"

template <typename T>
class ArrayStack : public Stack<T> {
public:

	// constructors and destructors
	ArrayStack(int max = 100);
	ArrayStack(const ArrayStack& stack);
	~ArrayStack();

	// setters
	void push(const T& elt) override;
	T pop() throw (std::logic_error) override;

	// getters
	bool empty() const override;
	int size() const override;
	const T& peek() const throw (std::logic_error) override;

	// operator surcharges
	const ArrayStack<T>& operator = (const ArrayStack<T>& s);
	template <typename U> friend std::ostream& operator<< (std::ostream& f, const ArrayStack<U>& s);

private:
	T* tab;
	int maxSize;
	int top;

	void _copy(T* tabS);
	void _resize();
};

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

// Add an element to the stack
template <typename T>
void ArrayStack<T>::push(const T& e) {
	if (top == maxSize) {
		_resize();
	}

	tab[top] = e;
	top++;
}

// Remove an element from the stack, if there is at least one element
template <typename T>
T ArrayStack<T>::pop() {
	if (empty()) {
		throw std::logic_error("The stack is empty !");
	}

	top--;
	return tab[top];
}

//Get the top element of the stack, if there is at least one element
template <typename T>
const T& ArrayStack<T>::peek() const {
	if (empty()) {
		throw std::logic_error("The stack is empty !");
	}

	return tab[top - 1];
}

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

// Surcharging the operator <<
template <typename T>
std::ostream& operator << (std::ostream& f, const ArrayStack<T>& s) {
	for (int i = 0; i < top; i++) {
		f << s.tab[i] << " ";
	}

	return f;
}