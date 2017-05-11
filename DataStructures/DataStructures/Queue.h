#pragma once
#include <stdexcept>

template<typename T>
class Queue
{
public:
	// Add an element to the queue
	virtual void add(const T& elt) = 0;
	// Remove an element from the queue (if not empty)
	virtual T remove() throw (std::logic_error) = 0;
	// Peek an element from the queue without removing it (if not empty)
	virtual T peek() const throw (std::logic_error) = 0;

	// Get the size of the queue
	virtual int size() const = 0;
	// Know if the queue is empty
	virtual bool empty() const = 0;
};
