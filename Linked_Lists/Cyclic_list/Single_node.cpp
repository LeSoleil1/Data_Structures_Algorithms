#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"

template <typename Type>
Single_node<Type>::Single_node( Type const &e, Single_node<Type> *n ):
element( e ),
next_node( n ) {
	// empty constructor
}

template <typename Type>
Type Single_node<Type>::retrieve() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type> *Single_node<Type>::next() const {
	// enter your implementation here
	return 0;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?