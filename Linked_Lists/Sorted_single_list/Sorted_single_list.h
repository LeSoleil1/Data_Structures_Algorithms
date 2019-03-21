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

#include "Exception.h"
#include <iostream>

template <typename Type>
class Single_node {
		public:
			Type       element;
			Single_node *next_node;

			Single_node(Type const &e = Type(), Single_node *n = 0);
			Type retrieve() const;
			Single_node *next() const;
		};

template <typename Type>
class Sorted_single_list {
	public:

		Sorted_single_list();
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


		void insert( Type const & );

		Type pop_front();

		int erase( Type const & );

private:
	Single_node<Type> *list_head;
	Single_node<Type> *list_tail;
	int list_size;
};

template <typename Type>
Single_node<Type>::Single_node(Type const &e, Single_node<Type> *n) :
	element(e),
	next_node(n) {
	// empty constructor
}

template <typename Type>
Type Single_node<Type>::retrieve() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type>* Single_node<Type>::next() const {
	// enter your implementation here
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////
template <typename Type>
Sorted_single_list<Type>::Sorted_single_list() :
	list_head(nullptr),
	list_tail(nullptr),
	list_size(0) {
	// empty constructor
}



template <typename Type>
Sorted_single_list<Type>::~Sorted_single_list() {
	// enter your implementation here
}

template <typename Type>
int Sorted_single_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Sorted_single_list<Type>::empty() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
Type Sorted_single_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Sorted_single_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::tail() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Sorted_single_list<Type>::count(Type const &obj) const {
	// enter your implementation here
	return 0;
}

template <typename Type>
void Sorted_single_list<Type>::insert(Type const &obj) {
	// enter your implementation here
	return;
}

template <typename Type>
Type Sorted_single_list<Type>::pop_front() {
	// enter your implementation here
	return Type();
}

template <typename Type>
int Sorted_single_list<Type>::erase(Type const &obj) {
	// enter your implementation here
	return 0;
}


#endif
