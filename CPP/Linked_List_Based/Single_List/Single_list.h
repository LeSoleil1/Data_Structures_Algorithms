/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

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
class Single_list {
	private:
		Single_node<Type> *list_head;
		Single_node<Type> *list_tail;
		int list_size;

	public:
		Single_list();
		Single_list( Single_list const & );
		~Single_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Single_node<Type> *head() const;
		Single_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Single_list & );
		Single_list &operator=( Single_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Single_list<T> const & );
};

template <typename Type>
Single_list<Type>::Single_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Single_list<Type>::Single_list( Single_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// The copy constructor creates a new instance of the linked list. (O(n))
	if (list.list_size == 0){
		return;
	}
	Single_node<Type> *current_Node = list.list_head;
	Single_node<Type> *new_Node = new Single_node<Type>(current_Node->element,nullptr);
	list_size++;
	list_head = new_Node;
	Single_node<Type> *previous_Node;
	while (current_Node->next() != nullptr){
		new_Node->element = current_Node->retrieve();
		previous_Node = new_Node;
		if (current_Node->next() != nullptr){
			Single_node<Type> *temp_Node = new Single_node<Type>();
			list_size++;
			new_Node = temp_Node;
			previous_Node->next_node = new_Node;
		}
		current_Node = current_Node->next();
	}
	list_tail = new_Node;
}

template <typename Type>
Single_list<Type>::~Single_list() {
	// The destructor must delete each of the nodes in the linked list. (O(n))
	if (list_size != 0){
		Single_node<Type> *current_Node = list_head;
		Single_node<Type> *temp_Node;
		while (current_Node != nullptr){
			temp_Node = current_Node;
			current_Node = current_Node->next();
			delete temp_Node;
		}
		list_size = 0;
		list_head = nullptr;
		list_tail = nullptr;
	}
}

template <typename Type>
int Single_list<Type>::size() const {
	// Returns the number of items in the list. (O(1))
	return list_size;
}

template <typename Type>
bool Single_list<Type>::empty() const {
	// Returns true if the list is empty, false otherwise. (O(1))
	return (list_size == 0);
}

template <typename Type>
Type Single_list<Type>::front() const {
	// Retrieves the object stored in the node pointed to by the head pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	Type return_Value = list_head->retrieve();
	return return_Value;
}

template <typename Type>
Type Single_list<Type>::back() const {
	// Retrieves the object stored in the node pointed to by the tail pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	Type return_Value = list_tail->retrieve();
	return return_Value;
}

template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {
	// Returns the head pointer. (O(1))
	return list_head;
}

template <typename Type>
Single_node<Type> *Single_list<Type>::tail() const {
	// Returns the tail pointer. (O(1))
	return list_tail;
}

template <typename Type>
int Single_list<Type>::count( Type const &obj ) const {
	// Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
	if (list_size == 0){
		return 0;
	}
	Single_node<Type> *current_Node = list_head;
	int counter = 0;
	while (current_Node != nullptr){
		if (current_Node->retrieve() == obj){
			counter++;
		}
		current_Node = current_Node->next();
	}
	return counter;
}

template <typename Type>
void Single_list<Type>::swap( Single_list<Type> &list ) {
	// The swap function swaps all the member variables of this linked list with those of the argument. (O(1))
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Single_list<Type> &Single_list<Type>::operator=( Single_list<Type> const &rhs ) {
	// he assignment operator makes a copy of the argument and then swaps the member variables of this singly linked list with those of the copy. (O(nlhs + nrhs))
	Single_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Single_list<Type>::push_front( Type const &obj ) {
	// Creates a new Single_node<Type> storing the argument, the next pointer of which is set to the current head pointer. The head pointer is set to this new node. If the list was originally empty, the tail pointer is set to point to the new node. (O(1))
	Single_node<Type> *new_Node = new Single_node<Type>(obj,nullptr);
	if (list_size == 0){
		list_size = 1;
		list_head = new_Node;
		list_tail = new_Node;
	}
	else{
		Single_node<Type> *temp_Node = list_head;
		list_size ++;
		list_head = new_Node;
		new_Node->next_node = temp_Node;
	}
}

template <typename Type>
void Single_list<Type>::push_back( Type const &obj ) {
	// Similar to push_front, this places a new node at the back of the list. (O(1))
	Single_node<Type> *new_Node = new Single_node<Type>(obj,nullptr);
	if (list_size == 0){
		list_size = 1;
		list_head = new_Node;
		list_tail = new_Node;
	}
	else{
		Single_node<Type> *temp_Node = list_tail;
		list_size ++;
		temp_Node->next_node = new_Node;
		list_tail = new_Node;
	}
}

template <typename Type>
Type Single_list<Type>::pop_front() {
	// Delete the node at the front of the linked list and, as necessary, update the head and tail pointers. Return the object stored in the node being popped. Throw an underflow exception if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	Type return_Value = list_head->retrieve();
	Single_node<Type> *new_Head = list_head->next();
	delete list_head;
	list_head = new_Head;
	list_size--;
	return return_Value;
}

template <typename Type>
int Single_list<Type>::erase( Type const &obj ) {
	// Delete the first node (from the front) in the linked list that contains the object equal to the argument (use == to to test for equality with the retrieved element). As necessary, update the head and tail pointers and the next pointer of any other node within the list. Return the number of nodes that were deleted. (O(n))
	if (list_size == 0){
		return 0;
	}
	if (list_size == 1){
		if (list_head->retrieve() == obj){
			list_size--;
			list_head = nullptr;
			list_tail = nullptr;
			return 1;
		}
		else{
			return 0;
		}

	}
	if (list_head->retrieve() == obj){
		list_size--;
		Single_node<Type> *temp_Node = list_head;
		list_head = list_head->next();
		delete temp_Node;
		return 1;
	}
	
	Single_node<Type> *prev_Node = list_head;
	Single_node<Type> *current_Node = prev_Node->next();
	Single_node<Type> *next_Node = current_Node->next();

	while (current_Node != nullptr){
		if (current_Node->retrieve() == obj){
			list_size--;
			prev_Node->next_node = next_Node;
			delete current_Node;
			if (next_Node == nullptr){
				list_tail = prev_Node;
			}
			return 1;

		}
		prev_Node = current_Node;
		current_Node = prev_Node->next();
		next_Node = current_Node->next();
	}
	return 0;

		
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Single_list<T> const &list ) {
	for ( Single_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
