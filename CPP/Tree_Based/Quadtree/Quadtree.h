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

#ifndef QUADTREE_H
#define QUADTREE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Quadtree {
	private:
		Quadtree_node<Type> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		Type min_x() const;
		Type min_y() const;

		Type max_x() const;
		Type max_y() const;

		Type sum_x() const;
		Type sum_y() const;

		Quadtree_node<Type> *root() const;
		bool member( Type const &, Type const & ) const;

		// Mutators

		void insert( Type const &, Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadtree<T> const & );
};

template <typename Type>
Quadtree<Type>::Quadtree():
tree_root( 0 ),
count( 0 ) {
	// empty constructor
}

template <typename Type>
Quadtree<Type>::~Quadtree() {
}

template <typename Type>
int Quadtree<Type>::size() const {
	return 0;
}

template <typename Type>
bool Quadtree<Type>::empty() const {
	return true;
}

template <typename Type>
Type Quadtree<Type>::min_x() const {
	return Type();
}

template <typename Type>
Type Quadtree<Type>::min_y() const {
	return Type();
}

template <typename Type>
Type Quadtree<Type>::max_x() const {
	return Type();
}

template <typename Type>
Type Quadtree<Type>::max_y() const {
	return Type();
}

template <typename Type>
Type Quadtree<Type>::sum_x() const {
	return Type();
}

template <typename Type>
Type Quadtree<Type>::sum_y() const {
	return Type();
}

template <typename Type>
Quadtree_node<Type> *Quadtree<Type>::root() const {
	return 0;
}

template <typename Type>
bool Quadtree<Type>::member( Type const &x, Type const &y ) const {
	return false;
}

template <typename Type>
void Quadtree<Type>::insert( Type const &x, Type const &y ) {
}

template <typename Type>
void Quadtree<Type>::clear() {
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Quadtree<T> const &qt ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
