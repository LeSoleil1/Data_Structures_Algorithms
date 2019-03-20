#include "ece250.h"
#include "Double_list.h"
#include "Exception.h"

template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Double_list<Type>::~Double_list() {
}

template <typename Type>
int Double_list<Type>::size() const {
	return 0;
}

template <typename Type>
bool Double_list<Type>::empty() const {
	return true;
}

template <typename Type>
Type Double_list<Type>::front() const {
	return Type();
}

template <typename Type>
Type Double_list<Type>::back() const {
	return Type();
}

template <typename Type>
Double_node<Type> *Double_list<Type>::head() const {
	return nullptr;
}

template <typename Type>
Double_node<Type> *Double_list<Type>::tail() const {
	return nullptr;
}

template <typename Type>
int Double_list<Type>::count( Type const &obj ) const {
	return 0;
}

template <typename Type>
void Double_list<Type>::swap( Double_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_list<Type> &Double_list<Type>::operator=( Double_list<Type> const &rhs ) {
	Double_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Double_list<Type>::push_front( Type const &obj ) {
}

template <typename Type>
void Double_list<Type>::push_back( Type const &obj ) {
}

template <typename Type>
Type Double_list<Type>::pop_front() {
	return Type();
}

template <typename Type>
Type Double_list<Type>::pop_back() {
	return Type();
}

template <typename Type>
int Double_list<Type>::erase( Type const &obj ) {
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?
