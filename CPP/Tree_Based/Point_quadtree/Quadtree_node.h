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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"

template <typename Type>
class Quadtree;

template <typename Type>
class Quadtree_node {
	private:
		Type       x_value;
		Type       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( Type const & = Type(), Type const & = Type() );

		Type retrieve_x() const;
		Type retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		Type min_x() const;
		Type min_y() const;

		Type max_x() const;
		Type max_y() const;

		Type sum_x() const;
		Type sum_y() const;

		bool member( Type const &, Type const & ) const;

		bool insert( Type const &, Type const & );
		void clear();

	friend class Quadtree<Type>;
};

template <typename Type>
Quadtree_node<Type>::Quadtree_node( Type const &x, Type const &y ):
x_value( x ),
y_value( y ),
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

template <typename Type>
Type Quadtree_node<Type>::retrieve_x() const {
	return x_value;
}

template <typename Type>
Type Quadtree_node<Type>::retrieve_y() const {
	return y_value;
}

template <typename Type>
Quadtree_node<Type> *Quadtree_node<Type>::nw() const {
	return north_west;
}

template <typename Type>
Quadtree_node<Type> *Quadtree_node<Type>::ne() const {
	return north_east;
}

template <typename Type>
Quadtree_node<Type> *Quadtree_node<Type>::sw() const {
	return south_west;
}

template <typename Type>
Quadtree_node<Type> *Quadtree_node<Type>::se() const {
	return south_east;
}

template <typename Type>
Type Quadtree_node<Type>::min_x() const {
	if (this != nullptr){
		if (this->nw() == nullptr && this->sw() == nullptr){
				return this->retrieve_x();
		}else if (this->nw() != nullptr && this->sw() != nullptr){
			return std::min(this->nw()->min_x(),this->sw()->min_x());
		}else if (this->nw() != nullptr){
			return this->nw()->min_x();
		}else{
			return this->sw()->min_x();
		}
	}
}

template <typename Type>
Type Quadtree_node<Type>::min_y() const {
	if (this != nullptr){
		if (this->sw() == nullptr && this->se() == nullptr){
				return this->retrieve_y();
		}else if (this->sw() != nullptr && this->se() != nullptr){
			return std::min(this->sw()->min_y(),this->se()->min_y());
		}else if (this->sw() != nullptr){
			return this->sw()->min_y();
		}else{
			return this->se()->min_y();
		}
	}
}

template <typename Type>
Type Quadtree_node<Type>::max_x() const {
	if (this != nullptr){
		if (this->ne() == nullptr && this->se() == nullptr){
				return this->retrieve_x();
		}else if (this->ne() != nullptr && this->se() != nullptr){
			return std::max(this->ne()->max_x(),this->se()->max_x());
		}else if (this->ne() != nullptr){
			return this->ne()->max_x();
		}else{
			return this->se()->max_x();
		}
	}
}

template <typename Type>
Type Quadtree_node<Type>::max_y() const {
	if (this != nullptr){
		if (this->nw() == nullptr && this->ne() == nullptr){
				return this->retrieve_y();
		}else if (this->nw() != nullptr && this->ne() != nullptr){
			return std::max(this->ne()->max_y(),this->nw()->max_y());
		}else if (this->ne() != nullptr){
			return this->ne()->max_y();
		}else{
			return this->nw()->max_y();
		}
	}
}

template <typename Type>
Type Quadtree_node<Type>::sum_x() const {
	if ( this == nullptr ) {
		return 0;
	} else {
		return this->retrieve_x() + this->sw()->sum_x() + this->se()->sum_x() + this->nw()->sum_x() + this->ne()->sum_x();
	}
}

template <typename Type>
Type Quadtree_node<Type>::sum_y() const {
	if ( this == nullptr ) {
		return 0;
	} else {
		return this->retrieve_y() + this->sw()->sum_y() + this->se()->sum_y() + this->nw()->sum_y() + this->ne()->sum_y();
	}
}

template <typename Type>
bool Quadtree_node<Type>::member( Type const &x, Type const &y ) const {
	if ( this == 0 ) {
		return false;
	}
	if (this->retrieve_x() == x && this->retrieve_y() == y){
		return true;
	}
	if (this->retrieve_x() <= x){
		if (this->retrieve_y() <= y){
			return this->ne()-member(x,y);
		} else {
			return this->se()->member(x,y);
		}
	}else{
		if (this->retrieve_y() <= y){
			return this->nw()-member(x,y);
		} else {
			return this->sw()->member(x,y);
		}
	}
	return false;
}

template <typename Type>
bool Quadtree_node<Type>::insert( Type const &x, Type const &y ) {
	if (this->retrieve_x() <= x){
		if (this->retrieve_y() <= y){
			if (this->ne() == nullptr){
				this->north_east = new Quadtree_node<Type>(x,y);
				return true;
			}
			return this->ne()->insert(x,y);
		} else {
			if (this->se() == nullptr){
				this->south_east= new Quadtree_node<Type>(x,y);
				return true;
			}
			return this->se()->insert(x,y);
		}
	}else{
		if (this->retrieve_y() <= y){
			if (this->nw() == nullptr){
				this->north_west = new Quadtree_node<Type>(x,y);
				return true;
			}
			return this->nw()->insert(x,y);
		} else {
			if (this->sw() == nullptr){
				this->south_west = new Quadtree_node<Type>(x,y);
				return true;
			}
			return this->sw()->insert(x,y);
		}
	}
}

template <typename Type>
void Quadtree_node<Type>::clear() {
}

#endif
