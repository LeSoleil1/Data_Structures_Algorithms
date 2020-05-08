#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Sorted_single_list {
	private:
		Single_node<Type> *list_head;
		Single_node<Type> *list_tail;
		int list_size;

	public:
		Sorted_single_list();
		Sorted_single_list( Sorted_single_list const & );
		~Sorted_single_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Single_node<Type> *head() const;
		Single_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Sorted_single_list & );
		Sorted_single_list &operator=( Sorted_single_list const & );

		void insert( Type const & );

		Type pop_front();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Sorted_single_list<T> const & );
};

template <typename Type>
Sorted_single_list<Type>::Sorted_single_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// This empty constructor sets all member variables to 0 or nullptr, as appropriate. (O(1))
}

template <typename Type>
Sorted_single_list<Type>::Sorted_single_list( Sorted_single_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// The copy constructor creates a new instance of the linked list. (O(n) and note that using insert will result in an O(n^2) run-time)
}

template <typename Type>
Sorted_single_list<Type>::~Sorted_single_list() {
	// The destructor must delete each of the nodes in the linked list. (O(n))
}

template <typename Type>
int Sorted_single_list<Type>::size() const {
	// Returns the number of items in the list. (O(1))
	return 0;
}

template <typename Type>
bool Sorted_single_list<Type>::empty() const {
	// Returns true if the list is empty, false otherwise. (O(1))
	return true;
}

template <typename Type>
Type Sorted_single_list<Type>::front() const {
	// Retrieves the object stored in the node pointed to by the head pointer. This function throws a underflow if the list is empty. (O(1))
	return Type();
}

template <typename Type>
Type Sorted_single_list<Type>::back() const {
	// Retrieves the object stored in the node pointed to by the tail pointer. This function throws a underflow if the list is empty. (O(1))
	return Type();
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::head() const {
	// Returns the head pointer. (O(1))
	return nullptr;
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::tail() const {
	// Returns the tail pointer. (O(1))
	return nullptr;
}

template <typename Type>
int Sorted_single_list<Type>::count( Type const &obj ) const {
	// Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
	return 0;
}

template <typename Type>
void Sorted_single_list<Type>::swap( Sorted_single_list<Type> &list ) {
	// The swap function swaps all the member variables of this linked list with those of the argument. (O(1))
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Sorted_single_list<Type> &Sorted_single_list<Type>::operator=( Sorted_single_list<Type> const &rhs ) {
	// The assignment operator makes a copy of the argument and then swaps the member variables of this sorted singly linked with those of the copy. (O(nlhs + nrhs))
	Sorted_single_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Sorted_single_list<Type>::insert( Type const &obj ) {
	/* Creates a new Single_node<Type> storing the argument, placing it into the correct location in 
	the linked list such that the element in the previous node (if any) is less than or equal to 
	the element stored in the current node, and that element is less than or equal to the element 
	stored in the next node. The head and tail pointers may have be updated if the new node is placed at the head or tail of the linked list. (O(n)) */
}

template <typename Type>
Type Sorted_single_list<Type>::pop_front() {
	/* Delete the node at the front of the linked list and, as necessary, update the head and tail pointers. 
	Return the object stored in the node being popped. Throw an underflow exception if the list is empty. (O(1)) */
	return Type();
}

template <typename Type>
int Sorted_single_list<Type>::erase( Type const &obj ) {
	/* Delete the first node (from the front) in the linked list that contains the object equal to the argument 
	(use == to to test for equality with the retrieved element). As necessary, update the head and tail pointers 
	and the next pointer of any other node within the list. Return the number of nodes that were deleted. (O(n)) */
	return 0;
}



template <typename T>
std::ostream &operator<<( std::ostream &out, Sorted_single_list<T> const &list ) {
	for ( Single_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}
#endif
