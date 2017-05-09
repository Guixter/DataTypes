#pragma once
#include <stdexcept>

template <typename T>
class Stack {
public:

	// setters
	virtual void push(const T& elt) = 0;
	virtual T pop() throw (std::logic_error) = 0;

	// getters
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& peek() const throw (std::logic_error) = 0;
};
