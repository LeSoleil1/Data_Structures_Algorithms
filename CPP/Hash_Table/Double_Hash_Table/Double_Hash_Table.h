#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <algorithm>

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
	int count;
	int power;
	int array_size;
	T *array;
	state *array_state;

	int h1(T const &) const;		
	int h2(T const &) const; 

public:
	DoubleHashTable(int = 5);
	~DoubleHashTable();
	int size() const;
	int capacity() const;
	bool empty() const;
	bool member(T const &) const;
	T bin(int) const;

	void print() const;

	void insert(T const &);
	bool remove(T const &);
	void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable(int m) :
	count(0), power(std::max(1, m)),
	array_size(1 << power),
	array(new T[array_size]),
	array_state(new state[array_size]) {
		for (int i = 0; i < array_size; ++i) {
			array_state[i] = EMPTY;
		}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// The destructor deletes the memory allocated for the hash table.
	delete[] array;
	delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	// Return the number of elements currently stored in the hash table. (O(1))
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	// Return the number of bins in the hash table. (O(1))
	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	// Return true if the hash table is empty, false otherwise. (O(1))
	return (count == 0);
}

template<typename T >
int DoubleHashTable<T >::h1(T const &obj) const {
	int position = (int)obj%array_size;
	if (position < 0) {
		return (position + array_size);
	}
	return position;
}

template<typename T >
int DoubleHashTable<T >::h2(T const &obj) const {

	int offset = ((int)obj / array_size) % array_size;
	if (offset % 2 == 0) {
		offset++;
	}
	if (offset < 0) {
		offset += array_size;
	}

	return offset;
}

template<typename T >
bool DoubleHashTable<T >::member(T const &obj) const {
	// Return true if object obj is in the hash table and false otherwise. (O(1))
	int position = h1(obj);
	int offset = h2(obj);

	for (int i = 0; i < array_size; i++)
	{
		if (array_state[position] == EMPTY)
		{
			return false;
		}
		else if (array_state[position] == OCCUPIED)
		{
			if (array[position] == obj)
			{
				return true;
			}
		}
		position = (position + offset) % array_size;
	}
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin(int n) const {
	/* Return the entry in bin n. The behaviour of this function is undefined
	if the bin is not filled. It will only be used to test the class with the expected locations. (O(1)) */
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert(T const &obj) {
	/* Insert the new object into the hash table in the appropriate
	bin as determined by the two aforementioned hash functions and the rules of double hashing. If
	the table is full, throw an overflow exception. (O(1)) */
	if (count == array_size)
	{
		throw overflow();
	}

	int position = h1(obj);
	int offset = h2(obj);

	while (array_state[position] == OCCUPIED)
	{
		position = (position + offset) % array_size;

	}
	array[position] = obj;
	array_state[position] = OCCUPIED;
	count++;
}

template<typename T >
bool DoubleHashTable<T >::remove(T const &obj) {
	/* Remove the object from the hash table if it is in the hash
	table (returning false if it is not) by setting the corresponding flag of the bin to deleted. (O(1)) */
	if (empty())
	{
		return false;
	}
	int position = h1(obj);
	int offset = h2(obj);

	for (int i = 0; i < array_size; i++)
	{
		if (array_state[position] == EMPTY)
		{
			return false;
		}
		if (array_state[position] == OCCUPIED)
		{
			if (array[position] == obj)
			{
				array_state[position] = DELETED;
				count--;
				return true;
			}
		}
		position = (position + offset) % array_size;
	}
	return false;

}

template<typename T >
void DoubleHashTable<T >::clear() {
	// Remove all the elements in the hash table. (O(M))
	for (int i = 0; i < array_size; i++) {
		array_state[i] = EMPTY;//or Deleted?
	}
	count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
	// A function you can use to print the class for debugging purposes. This function will not be tested.
	// TODO
	return;
}

#endif
