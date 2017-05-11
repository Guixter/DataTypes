#pragma once
#include <stdexcept>

template <typename T>
class List {
public:
	// Add an element in the list
	virtual void add(int index, const T& elt) = 0;
	// Set an element in the list (if the index is valid)
	virtual void set(int index, const T& elt) = 0;
	// Remove an element from the list (if the index is valid)
	virtual T& remove(int index) throw (std::logic_error) = 0;
	// Get an element from the list (if the index is valid)
	virtual T& get(int index) const throw (std::logic_error) = 0;
	// Clear the list
	virtual void clear() = 0;

	// Know if an element is in the list
	virtual bool contains(T elt) const = 0;
	// Get the index of an element in the list (-1 if not in the list)
	virtual int indexOf(T elt) const = 0;
	// Get the size of the list
	virtual int size() const = 0;
	// Know if the list is empty
	virtual bool empty() const  = 0;
	// Print the list
	virtual void print(std::ostream& f) const = 0;

	// Surcharging the << operator
	template <typename U> friend std::ostream& operator << (std::ostream& f, const List<U>& l);
};

// Surcharging the operator <<
template <typename T>
std::ostream& operator << (std::ostream& f, const List<T>& l) {
	l.print(f);
	return f;
}