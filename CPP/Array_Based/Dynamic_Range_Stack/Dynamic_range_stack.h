#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

template <typename Type>
class Dynamic_range_stack {
private:
	int entry_count;
	int initial_capacity;
	int current_capacity;

	int *stack_array;
	int *maximum_array;
	int *minimum_array;

	int max_count;
	int min_count;
	
	
	int elementIndex;
	int elementIndexMax;
	int elementIndexMin;



	// You may wish to include a number of other helper functions
	// in order to abstract out some operations

	void halve_capacity();
	void double_capacity();

public:
	Dynamic_range_stack(int = 10);
	Dynamic_range_stack(Dynamic_range_stack const &);
	~Dynamic_range_stack();

	int top() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	int maximum() const;
	int minimum() const;

	void swap(Dynamic_range_stack &);
	Dynamic_range_stack &operator=(Dynamic_range_stack const &);
	void push(int const &);
	int pop();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack<T> const & );
};

template <typename Type>
Dynamic_range_stack<Type>::Dynamic_range_stack(int n) :
	// The constructor takes as an argument the initial size of the arrays and allocates memory for the three arrays.
	entry_count(0),
	min_count(0),
	max_count(0),
	initial_capacity(std::max(1, n)),
	current_capacity(initial_capacity),
	stack_array(new int[current_capacity]),
	maximum_array(new int[current_capacity]),
	minimum_array(new int[current_capacity]) {
	// empty constructor
}

template <typename Type>
Dynamic_range_stack<Type>::Dynamic_range_stack( Dynamic_range_stack const &stack ):
entry_count( stack.entry_count ),
initial_capacity( stack.initial_capacity ),
current_capacity( stack.current_capacity ),
max_count(stack.max_count),
min_count(stack.min_count),
stack_array( new Type[current_capacity] ),
minimum_array( new Type[current_capacity] ),
maximum_array( new Type[current_capacity] ) {
	// The copy constructor creates a new instance of the stack. (O(n))
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure;
	// however, you must still copy the stored objects.
	for (int i = 0; i < stack.entry_count; i++){
		stack_array[i] = stack.stack_array[i];
	}
	for (int i = 0; i < stack.max_count; i++){
		maximum_array[i] = stack.maximum_array[i];
	}
	for (int i = 0; i < stack.min_count; i++){
		minimum_array[i] = stack.minimum_array[i];
	}

}

template <typename Type>
Dynamic_range_stack<Type>::~Dynamic_range_stack() {
	// The destructor deletes the memory allocated for the arrays.
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
}

template <typename Type>
int Dynamic_range_stack<Type>::top() const {
	// Return the object at the top of the stack (stack_array). It may throw an underflow exception (O(1)).
	if (entry_count == 0)
		throw underflow();
	return stack_array[elementIndex];

}

template <typename Type>
int Dynamic_range_stack<Type>::maximum() const {
	// Return the maximum object currently in the stack. It may throw an underflow exception (O(1)).).
	if (entry_count == 0)
		throw underflow();
	return maximum_array[elementIndexMax];

}

template <typename Type>
int Dynamic_range_stack<Type>::minimum() const {
	// Return the minimum object currently in the stack. It may throw an underflow exception (O(1)).).
	if (entry_count == 0)
		throw underflow();
	return	minimum_array[elementIndexMin];

}

template <typename Type>
int Dynamic_range_stack<Type>::size() const {
	// Returns the number of elements currently stored in the stack (O(1)).).
	return entry_count;
}

template <typename Type>
bool Dynamic_range_stack<Type>::empty() const {
	// Check if the stack is empty. (O(1))
	if (entry_count == 0)
		return true;
	else
	{
		return false;
	}
}

template <typename Type>
int Dynamic_range_stack<Type>::capacity() const {
	// Return the current capacity of the arrays in (O(1)).).
	return current_capacity;
}

template <typename Type>
void Dynamic_range_stack<Type>::push(int const &obj) {
	/* If the stack array is full, create three new arrays which are double
	in size, copy over all the entries, and delete the old arrays. Push the argument onto the top
	of the stack_array, and update the other stacks if needed (in average O(1)). */
	if (size() == current_capacity)
	{
		int *oldStack_array;
		int *oldMaximum_array;
		int *oldMinimum_array;
		oldStack_array = stack_array;
		oldMaximum_array = maximum_array;
		oldMinimum_array = minimum_array;
		int oldSize = size();
		int oldMinSize = min_count;
		int oldMaxSize = max_count;
		current_capacity = 2 * current_capacity;
		stack_array = new int[current_capacity];
		maximum_array = new int[current_capacity];
		minimum_array = new int[current_capacity];

		for (int i = 0; i < oldSize; i++){
			stack_array[i] = oldStack_array[i];
		}
		for (int i = 0; i < oldMaxSize; i++){
			maximum_array[i] = oldMaximum_array[i];
		}
		for (int i = 0; i < oldMinSize; i++){
			minimum_array[i] = oldMinimum_array[i];
		}

		entry_count = oldSize;
		delete[] oldStack_array;
		delete[]oldMaximum_array;
		delete[]oldMinimum_array;
	}
	if (empty())
	{
		elementIndex = 0;
		elementIndexMax = 0;
		elementIndexMin = 0;
		stack_array[elementIndex] = obj;
		minimum_array[elementIndexMin] = obj;
		maximum_array[elementIndexMax] = obj;
		entry_count++;
		max_count++;
		min_count++;

	}
	else
	{
		elementIndex++;
		stack_array[elementIndex] = obj;
		entry_count++;
		if (obj >= maximum_array[elementIndexMax]) {
			elementIndexMax++;
			maximum_array[elementIndexMax] = obj;
			max_count++;
		}
		if (obj <= minimum_array[elementIndexMin]) {
			elementIndexMin++;
			minimum_array[elementIndexMin] = obj;
			min_count++;
		}
	}
	return;
}

template <typename Type>
int Dynamic_range_stack<Type>::pop() {
	/* Pop the top element off of the stack(s) by removing it from the stack array and
	updated other stacks if needed. This may throw an underflow exception (in average O(1)). */
	if (empty())
		throw underflow();
	else
	{
		int popReturn = top();
		
		if (maximum() == popReturn)
		{
			elementIndexMax--;
			max_count--;
		}
		if (minimum() == popReturn)
		{
			elementIndexMin--;
			min_count--;

		}
		elementIndex--;
		entry_count--;
		return popReturn;
	}
}

template <typename Type>
void Dynamic_range_stack<Type>::clear() {
	/* Empties the stacks by resetting the member variables. If the current array
	size does not equal the initial size, delete the arrays and create three new arrays equal to
	the initial size (O(1)). */
	elementIndex = 0;
	elementIndexMax = 0;
	elementIndexMin = 0;
	if (initial_capacity != current_capacity) {
		current_capacity = initial_capacity;
		delete[] stack_array;
		delete[] minimum_array;
		delete[]maximum_array;
		stack_array = new int[current_capacity];
		minimum_array = new int[current_capacity];
		maximum_array = new int[current_capacity];
	}
}

// You can modify this function however you want:  it will not be tested
template <typename Type>
std::ostream &operator<<(std::ostream &out, Dynamic_range_stack<Type> const &stack) {
	// Print out your stacks

	return out;
}


#endif
