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
	// enter your implementation here
}

template <typename Type>
Single_list<Type>::~Single_list() {
	// enter your implementation here
}

template <typename Type>
int Single_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Single_list<Type>::empty() const {
	// enter your implementation here
	return true;
}

template <typename Type>
Type Single_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Single_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
Single_node<Type> *Single_list<Type>::tail() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Single_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
	return 0;
}

template <typename Type>
void Single_list<Type>::swap( Single_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Single_list<Type> &Single_list<Type>::operator=( Single_list<Type> const &rhs ) {
	Single_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Single_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
void Single_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
Type Single_list<Type>::pop_front() {
	// enter your implementation here
	return Type();
}

template <typename Type>
int Single_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
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
