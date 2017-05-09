#pragma once
#include <stdexcept>

template<typename T>
class Queue
{
public:
	// setters
	virtual void add(const T&) = 0;
	virtual T remove() throw (std::logic_error) = 0;

	// getters
	virtual int size() const = 0;
	virtual bool empty() const = 0;
};
