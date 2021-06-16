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
	// Returns the number of items in the quadtree. (O(1)) 
	return count;
}

template <typename Type>
bool Quadtree<Type>::empty() const {
	// Returns true if the quadtree is empty, false otherwise. (O(1))
	return (size() == 0);
}

template <typename Type>
Type Quadtree<Type>::min_x() const {
	// Returns the minimum x value within the quadtree. Throw an underflow exception if the tree is empty. (O(n) but O(√n) if balanced)
	if (size() == 0){
		throw underflow();
	}
	return tree_root->min_x();
}

template <typename Type>
Type Quadtree<Type>::min_y() const {
	// Returns the minimum y value within the quadtree. Throw an underflow exception if the tree is empty. (O(n) but O(√n) if balanced)
	if (size() == 0){
		throw underflow();
	}
	return tree_root->min_y();
}

template <typename Type>
Type Quadtree<Type>::max_x() const {
	// Returns the maximum x value within the quadtree. Throw an underflow exception if the tree is empty. (O(n) but O(√n) if balanced)
	if (size() == 0){
		throw underflow();
	}
	return tree_root->max_x();
}

template <typename Type>
Type Quadtree<Type>::max_y() const {
	// Returns the maximum y value within the quadtree. Throw an underflow exception if the tree is empty. (O(n) but O(√n) if balanced)
	if (size() == 0){
		throw underflow();
	}
	return tree_root->max_y();
}

template <typename Type>
Type Quadtree<Type>::sum_x() const {
	// Returns the sum of the x value within the quadtree, respectively. The sum of the nodes of an empty tree is 0. (O(n))
	if (size() == 0){
		return 0;
	}
	return tree_root->sum_x();
}

template <typename Type>
Type Quadtree<Type>::sum_y() const {
	// Returns the sum of the y value within the quadtree, respectively. The sum of the nodes of an empty tree is 0. (O(n))
	if (size() == 0){
		return 0;
	}
	return tree_root->sum_y();
}

template <typename Type>
Quadtree_node<Type> *Quadtree<Type>::root() const {
	// Returns the address of the root node. If the tree is empty, the root node should be 0. (O(1))
	return tree_root;
}

template <typename Type>
bool Quadtree<Type>::member( Type const &x, Type const &y ) const {
	// Returns true if the pair (x,y) is stored in one of the nodes of the quadtree and false otherwise. (O(n) but O(ln(n)) if balanced)
	if (tree_root == 0){
		return false;
	}
	return tree_root->member(x,y);
}

template <typename Type>
void Quadtree<Type>::insert( Type const &x, Type const &y ) {
	// Inserts the pair (x, y) into the quadtree. If the root is 0, a new quadtree node is created; otherwise, the task of insertion is passed to the root node.
	if ( tree_root == 0 ) {
		tree_root = new Quadtree_node<Type>(x,y);
	} else{
		tree_root->insert(x,y);
	}	
	count += 1;
}

template <typename Type>
void Quadtree<Type>::clear() {
	// Calls clear on the root if necessary and sets the root and count to 0. (O(n))
	// TODO: To be completed
}



template <typename T>
std::ostream &operator<<( std::ostream &out, Quadtree<T> const &qt ) {
	return out;
}


#endif
