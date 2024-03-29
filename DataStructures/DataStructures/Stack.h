#pragma once
#include <stdexcept>

template <typename T>
class Stack {
public:

	// Push an element in the stack
	virtual void push(const T& elt) = 0;
	// Pop an element from the stack (if not empty)
	virtual T pop() throw (std::logic_error) = 0;
	// Peek an element from the stack without removing it (if not empty)
	virtual T peek() const throw (std::logic_error) = 0;

	// Get the size of the stack
	virtual int size() const = 0;
	// Know if the stack is empty
	virtual bool empty() const = 0;
	// Print the stack
	virtual void print(std::ostream& f) const = 0;

	// Surcharging the << operator
	template <typename U> friend std::ostream& operator << (std::ostream& f, const Stack<U>& s);
};

// Surcharging the operator <<
template <typename T>
std::ostream& operator << (std::ostream& f, const Stack<T>& s) {
	s.print(f);
	return f;
}