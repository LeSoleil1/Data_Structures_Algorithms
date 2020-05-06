#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"
#include <iostream>
#include <algorithm>
using namespace std;



class Dynamic_deque_as_array{
	private:
		int array_size; // capacity (C1)
		int *array;
		int ihead;
		int itail;
		int count; // actual number of elements in the array (C2)
		int wrap(int index);

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
		void print();
};


Dynamic_deque_as_array::Dynamic_deque_as_array(int n) :
		array_size(std::max(1, n)),
		array(new int[array_size]),
		count(0) {
		// empty 
}

Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	// The destructor deletes the memory allocated for the array.
	delete[] array;	
}

int Dynamic_deque_as_array::size() const {
	// Return the number of elements currently stored in the deque in O(1).
	return count;
}

int Dynamic_deque_as_array::capacity() const {
	// Return the capacity of deque in O(1).
	return array_size;
}

bool Dynamic_deque_as_array::empty() const {
	// Return true if deque is empty false otherwise in O(1).
	return (count == 0);
}

int Dynamic_deque_as_array::head() const {
	// Return the integer at the head of the data deque in O(1). It may throw an underflow exception.
	if (count == 0){
		throw underflow();
	} 
	return array[ihead];
}

int Dynamic_deque_as_array::tail() const {
	// Return the integer at the tail of the data deque in O(1). It may throw an underflow exception.
	if (count == 0){
		throw underflow();
	} 
	return array[itail];
}

int Dynamic_deque_as_array::wrap(int index) {

	int adj_index = index;

	if (index >= capacity()) adj_index = 0;

	if (index < 0) adj_index = index + capacity();

	return adj_index;

}

void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	/* Insert a new item at the head of the deque in O(1). If the array
	is full, create a new array with size 2n (where n is current size of the array) and copy the elements
	from the current array to the new array in O(n).*/
	if (size() == capacity()) {
		int *old_Array;
		old_Array = array;
		int old_Size = size();
		array_size = 2 * old_Size;
		array = new int[array_size];
		for (int i = 1; i < old_Size; i++)
			array[i] = old_Array[i];
		count = old_Size;
		delete[] old_Array;
		
	}

	if (count == 0) {
		// when  inserting the first element, both head and tail are pointing to this element         
		ihead = 0;
		itail = 0;
		array[ihead] = obj;
	}
	else {
		ihead++;
		//check for out of boundary
		ihead = wrap(ihead);
		array[ihead] = obj;
	}

	count++;
	return;

}

void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	/* Insert a new item at the tail of the deque in O(1). If the array is
	full, create a new array with size 2n (where n is current size of the array) and copy the elements
	from the current array to the new array in O(n). */
	if (size() == capacity()) {
		int *old_Array;
		old_Array = array;
		int old_Size = size();
		array_size = 2 * old_Size;
		array = new int[array_size];
		for (int i = 1; i < old_Size; i++)
			array[i] = old_Array[i];
		count = old_Size;
		delete[] old_Array;
	}

	if (count == 0) {
		// when  inserting the first element, both head and tail are pointing to this element   
		itail = 0;
		ihead = 0;
		array[itail] = obj;
	}
	else {
		itail--;
		//check for out of boundary
		itail = wrap(itail);
		array[itail] = obj;
	}

	count++;
	return;
}

int Dynamic_deque_as_array::dequeue_head() {
	// Remove the element at the head of the deque in O(1). This may throw an underflow exception.
	if (count == 0){
		throw underflow();
	} 


	int return_Value = array[ihead];

	array[ihead] = 999999;// deleted marker for now

	ihead--;

	ihead = wrap(ihead); // adjust ihead 

	count--;

	return return_Value;


}

int Dynamic_deque_as_array::dequeue_tail() {
	// Remove the element at the tail of the deque in O(1). This may throw an underflow exception.
	if (count == 0){
		throw underflow();
	} 

	int return_Value = array[itail];

	array[itail] = 999999;// deleted marker for now

	itail++;

	itail = wrap(itail); // adjust ihead 

	count--;

	return return_Value;

}

void Dynamic_deque_as_array::clear() {
	// Remove all elements from the deque in O(1).
	count = 0;
}

void Dynamic_deque_as_array::print() {
	cout << "---------------" << endl;
	cout << "size(): " << size() << endl;
	cout << "ihead: " << ihead << endl;
	cout << "itail: " << itail << endl;
	for (int i = 0; i < array_size; i++) {
		cout << "i: " << i << " " << array[i] << endl;

	}
}

#endif
