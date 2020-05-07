#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H


#include "Exception.h"
#include "ece250.h"
#include <iostream>
using namespace std;

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
		int jumpSize;
		T initialArraySize;
		
		
        //	int mod;
		T *array;
		state *array_state;
		int hashFunction(T const &) const;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable(int m) :
	count(0), power(m), jumpSize(1),
	array_size(1 << power),initialArraySize(array_size),
	array(new T[array_size]),
	array_state(new state[array_size]) {

	for (int i = 0; i < array_size; ++i) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	/*The destructor deletes the memory allocated for the hash table. Notice that the hash table has been
	represented using two arrays, and they both need to be deleted.*/
	delete[] array;
	delete[] array_state;
}

template<typename T >
int LinearHashTable<T >::size() const {
	// Return the number of elements currently stored in the hash table. (O(1))
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	// Return the number of bins in the hash table. (O(1))
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	// Return the load factor of the hash table. (O(1))
	double loadFactor =  (double)count / array_size;
	return loadFactor;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
	// Return true if the hash table is empty, false otherwise. (O(1))
	return count == 0;
}

template<typename T >
int LinearHashTable<T >::hashFunction(T const &obj) const {
	/* The hash function of linear probing takes the form of h(k,i) = (h(k)+i) mod M where h is the
	primary hash function: h(k) = k mod M and i is the number of collisions */
	int position = 0; 
	position = (int)obj % array_size;
	if (position < 0)
	{
		position = position + array_size;
	}
	return position;
}

template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	// Return true if object obj is in the hash table and false otherwise. (O(1))
	int position = hashFunction(obj);							
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
		position = (position + jumpSize) % array_size;
	}
	return false;
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
	/* Return the entry in bin n. The behaviour of this function is undefined if the bin
	is not filled. It will only be used to test the class with the expected locations. (O(1)) */
	return array[n];
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	/* If load factor is less than or equal to 0.75, you have to insert the new
	object into the hash table in the appropriate bin as determined by the hash function and the rules
	of linear probing (O(1)). Otherwise, double the size of hash table, rehash all elements, and then
	insert the new element (O(n)). */
	if (count == array_size)
	{
		throw overflow();
	}
	double loadFactor = load_factor();
	if (loadFactor <= 0.75) {
		int position = hashFunction(obj);
		while (array_state[position] == OCCUPIED)
		{
			position = (position + jumpSize) % array_size;
		}
		array[position] = obj;
		array_state[position] = OCCUPIED;
		count++;
	}
	else
	{
		T lastAdd = obj;
		T *oldArray;
		T tempInput;
		oldArray = array;
		int oldSize = capacity();
		array_size = 2 * oldSize;
		array = new T[array_size];
		array_state=new state[array_size];
		count = 0;
		for (int i = 1; i < oldSize; i++)
		{
			tempInput = oldArray[i];
			insert(tempInput);
		}
		insert(lastAdd);
		delete[] oldArray;
	}
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	/* If the load factor is greater than 0.25, you have to remove the object
	from the hash table if it is in the hash table (returning false if it is not) by setting the
	corresponding flag of the bin to “DELETED”. (O(1)). Otherwise, if the load factor is less than
	0.25 and the current capacity of hash table is not equal to the initial capacity (that was assigned in
	the constructor), you have to shrink the capacity of the hash table to the half of its current size,
	rehash the elements, and remove the input from the table (O(n)). */
	if (empty())
	{
		return false;
	}
	else
	{
		if (member(obj))
		{
			double loadFactor = load_factor();
			if (loadFactor <= 0.25 && array_size!=initialArraySize) 
			{
				T lastRemove = obj;
				T *oldArray;
				T tempInput;
				oldArray = array;
				int oldSize = capacity();
				array_size = oldSize/2;
				array = new T[array_size];
				array_state = new state[array_size];
				count = 0;
				for (int i = 1; i < oldSize; i++)
				{
					tempInput = oldArray[i];
					insert(tempInput);
				}
				remove(lastRemove);
				delete[] oldArray;				
			}
			else
			{				
				int position = hashFunction(obj);
				while (array_state[position] != OCCUPIED || array[position] != obj)
				{
					position = (position + jumpSize) % array_size;
				}
				array_state[position] = DELETED;
				count--;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

template<typename T >
void LinearHashTable<T >::clear() {
	// Remove all the elements in the hash table. (O(M))
	for (int i = 0; i < array_size; i++)
	{
		array_state[i] = EMPTY;
	}
	count = 0;
}

template<typename T >
void LinearHashTable<T >::print() const{
	// A function which you can use to print the class in the testing environment. This function will not be tested.
	if (empty())
	{
		cout << "The hashtable is empty" << endl;
	}
	else
	{
		for (int i = 0; i < array_size; i++)
		{
			if (array_state[i] == OCCUPIED)
			{
				cout << i << " : " << array[i] << endl;
			}
			else if (array_state[i] == DELETED)
			{
				cout << i << " : deteled " << endl;
			}
			else
			{
				cout << i << " : empty " << endl;
			}
		}
	}
}

#endif
