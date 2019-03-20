#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
Double_node<Type>::Double_node( Type const &e, Double_node<Type> *p, Double_node<Type> *n ):
element( e ),
previous_node( p ),
next_node( n ) {
	// empty constructor
}

template <typename Type>
Type Double_node<Type>::retrieve() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Double_node<Type> *Double_node<Type>::previous() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
Double_node<Type> *Double_node<Type>::next() const {
	// enter your implementation here
	return 0;
}

#endif
