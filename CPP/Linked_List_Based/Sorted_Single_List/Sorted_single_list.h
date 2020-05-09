#ifndef SORTED_SINGLE_LIST_H
#define SORTED_SINGLE_LIST_H

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
	if (list.list_size != 0){
		Single_node<Type> *current_Node = list.list_head;
		Single_node<Type> *new_Node = new Single_node<Type>(current_Node->retrieve(),nullptr);
		Single_node<Type> *temp_Node;
		list_head = new_Node;
		list_size++;
		current_Node = current_Node->next();
		while (current_Node != nullptr){
			temp_Node = new_Node;
			new_Node = new Single_node<Type>(current_Node->retrieve(),nullptr);
			list_size++;
			temp_Node->next_node = new_Node;
			current_Node = current_Node->next();
		}
		list_tail = new_Node;
	}
}

template <typename Type>
Sorted_single_list<Type>::~Sorted_single_list() {
	// The destructor must delete each of the nodes in the linked list. (O(n))
	Single_node<Type> *current_Node = list_head;
	Single_node<Type> *next_Node = list_head->next();
	while (next_Node != nullptr){
		delete current_Node;
		current_Node = next_Node;
		next_Node = next_Node->next();
	}
	list_head = nullptr;
	list_tail = nullptr;
	list_size = 0;
}

template <typename Type>
int Sorted_single_list<Type>::size() const {
	// Returns the number of items in the list. (O(1))
	return list_size;
}

template <typename Type>
bool Sorted_single_list<Type>::empty() const {
	// Returns true if the list is empty, false otherwise. (O(1))
	return (list_size == 0);
}

template <typename Type>
Type Sorted_single_list<Type>::front() const {
	// Retrieves the object stored in the node pointed to by the head pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	return list_head->retrieve();
}

template <typename Type>
Type Sorted_single_list<Type>::back() const {
	// Retrieves the object stored in the node pointed to by the tail pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	return list_tail->retrieve();
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::head() const {
	// Returns the head pointer. (O(1))
	return list_head;
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::tail() const {
	// Returns the tail pointer. (O(1))
	return list_tail;
}

template <typename Type>
int Sorted_single_list<Type>::count( Type const &obj ) const {
	// Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
	if (list_size == 0){
		return 0;
	}
	Single_node<Type> *node = list_head;
	int counter = 0;
	while (node != nullptr){
		Type value = node->retrieve();
		if (value == obj){
			counter++;
		}
		else if (value > obj){
			break;
		}
		node = node->next();
	}
	return counter;
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
	Single_node<Type> *new_node = new Single_node<Type>(obj,nullptr);
	if(list_size == 0){
		list_tail = new_node;
		list_head = new_node;
		list_size++;
	}
	else if(list_size == 1){
		if (list_head->retrieve() > obj){
			new_node->next_node = list_head;
			list_head = new_node;
			list_size++;
		}else{
			list_head->next_node = new_node;
			list_tail = new_node;
			list_size++;
		}
	}else if (list_head->retrieve() > obj){
		new_node->next_node = list_head;
		list_head = new_node;
		list_size++;
	}else if (list_tail->retrieve() < obj){
		list_tail->next_node = new_node;
		list_tail = new_node;
		list_size++;
	}else{
		Single_node<Type> *current_Node = list_head;
		Single_node<Type> *next_Node = list_head->next();
		while (next_Node != nullptr){
			if (current_Node->retrieve() <= obj && next_Node->retrieve() >= obj){
				current_Node->next_node = new_node;
				new_node->next_node = next_Node;
				list_size++;
				break;
			}
			current_Node = next_Node;
			next_Node = next_Node->next();
		}
	}
}

template <typename Type>
Type Sorted_single_list<Type>::pop_front() {
	/* Delete the node at the front of the linked list and, as necessary, update the head and tail pointers. 
	Return the object stored in the node being popped. Throw an underflow exception if the list is empty. (O(1)) */
	if (list_size == 0){
		throw underflow();
	}else if (list_size == 1){
		Type result = list_head->retrieve();
		delete list_head;
		list_size = 0;
		list_tail = nullptr;
		list_head = nullptr;
	}else{
		Type result = list_head->retrieve();
		Single_node<Type> *temp_Node = list_head;
		list_head = list_head->next();
		delete temp_Node;
		list_size--;
		return result;
	}
	
}

template <typename Type>
int Sorted_single_list<Type>::erase( Type const &obj ) {
	/* Delete the first node (from the front) in the linked list that contains the object equal to the argument 
	(use == to to test for equality with the retrieved element). As necessary, update the head and tail pointers 
	and the next pointer of any other node within the list. Return the number of nodes that were deleted. (O(n)) */
	if (list_size == 0){
		return 0;
	}else if (list_size ==1){
		if (list_head->retrieve() != obj){
			return 0;
		}else{
			delete list_head;
			list_head = nullptr;
			list_tail = nullptr;
			list_size = 0;
			return 1;
		}
	}else if (list_head->retrieve() == obj){
		Single_node<Type> *temp_Node = list_head->next();
		delete list_head;
		list_size--;
		list_head = temp_Node;
		return 1;
	}else{
		Single_node<Type> *current_Node = list_head;
		Single_node<Type> *next_Node = list_head->next();
		while (next_Node != nullptr){
			if (next_Node->retrieve() == obj){
				current_Node->next_node = next_Node->next();
				delete next_Node;
				list_size--;
				return 1;
			}
			current_Node = next_Node;
			next_Node = next_Node->next();
		}
	}
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
