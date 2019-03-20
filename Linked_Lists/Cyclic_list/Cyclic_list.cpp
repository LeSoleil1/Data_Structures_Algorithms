#include "ece250.h"
#include "Cyclic_list.h"
#include "Exception.h"

template <typename Type>
Cyclic_list<Type>::Cyclic_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Cyclic_list<Type>::Cyclic_list( Cyclic_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Cyclic_list<Type>::~Cyclic_list() {
	// enter your implementation here
}

template <typename Type>
int Cyclic_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Cyclic_list<Type>::empty() const {
	// enter your implementation here
	return true;
}

template <typename Type>
Type Cyclic_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Cyclic_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type> *Cyclic_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
Single_node<Type> *Cyclic_list<Type>::tail() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Cyclic_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
	return 0;
}

template <typename Type>
void Cyclic_list<Type>::swap( Cyclic_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Cyclic_list<Type> &Cyclic_list<Type>::operator=( Cyclic_list<Type> const &rhs ) {
	Cyclic_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Cyclic_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
void Cyclic_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
Type Cyclic_list<Type>::pop_front() {
	// enter your implementation here
	return Type();
}

template <typename Type>
int Cyclic_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
	return 0;
}
