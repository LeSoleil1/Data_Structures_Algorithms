#include "ece250.h"
#include "Cyclic_double_list.h"
#include "Exception.h"

template <typename Type>
Cyclic_double_list<Type>::Cyclic_double_list():
list_head( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Cyclic_double_list<Type>::Cyclic_double_list( Cyclic_double_list<Type> const &list ):
list_head( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Cyclic_double_list<Type>::~Cyclic_double_list() {
	// enter your implementation here
}

template <typename Type>
int Cyclic_double_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Cyclic_double_list<Type>::empty() const {
	// enter your implementation here
	return true;
}

template <typename Type>
Type Cyclic_double_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Cyclic_double_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Double_node<Type> *Cyclic_double_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Cyclic_double_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
	return 0;
}

template <typename Type>
void Cyclic_double_list<Type>::swap( Cyclic_double_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Cyclic_double_list<Type> &Cyclic_double_list<Type>::operator=( Cyclic_double_list<Type> const &rhs ) {
	Cyclic_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Cyclic_double_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
void Cyclic_double_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
Type Cyclic_double_list<Type>::pop_front() {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Cyclic_double_list<Type>::pop_back() {
	// enter your implementation here
	return Type();
}

template <typename Type>
int Cyclic_double_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Cyclic_double_list<T> const &list ) {
	if ( list.empty() ) {
		out << "->0";
		return out;
	}

	Double_node<T> *ptr = list.head();

	for ( int i = 0; i <= list.size(); ++i ) {
		out << "->" << ptr->retrieve();
		ptr = ptr->next();
	}

	out << std::endl;

	ptr = list.head();

	for ( int i = 0; i <= list.size(); ++i ) {
		out << "->" << ptr->retrieve();
		ptr = ptr->previous();
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?
