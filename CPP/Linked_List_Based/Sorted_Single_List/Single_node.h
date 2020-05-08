#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"

template <typename Type>
class Single_list;

template <typename Type>
class Cyclic_list;

template <typename Type>
class Sentinel_list;

template <typename Type>
class Cyclic_sentinel_list;

template <typename Type>
class Single_node {
	private:
		Type       element;
		Single_node *next_node;


	public:
		Single_node( Type const &e = Type(), Single_node *n = 0 );

		Type retrieve() const;
		Single_node *next() const;

		friend class Single_list<Type>;
		friend class Cyclic_list<Type>;
		friend class Sentinel_list<Type>;
		friend class Cyclic_sentinel_list<Type>;

		// if ptr is a pointer to a Single_node<Type> object
		// in one of the friendly classes, you should:
		//    use   ptr->next_node   to modify it
		//    use   ptr->next()      to access it
};

template <typename Type>
Single_node<Type>::Single_node( Type const &e, Single_node<Type> *n ):
element( e ),
next_node( n ) {
	// empty constructor
}

template <typename Type>
Type Single_node<Type>::retrieve() const {
	return element;
}

template <typename Type>
Single_node<Type> *Single_node<Type>::next() const {
	return next_node;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
