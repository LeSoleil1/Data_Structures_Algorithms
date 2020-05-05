#include "ece250.h"
#include "Single_list.h"
#include "Exception.h"

template <typename Type>
Single_list<Type>::Single_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Single_list<Type>::Single_list( Single_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
}

template <typename Type>
Single_list<Type>::~Single_list() {
	// enter your implementation here
}

template <typename Type>
int Single_list<Type>::size() const {
	// enter your implementation here
	return 0;
}

template <typename Type>
bool Single_list<Type>::empty() const {
	// enter your implementation here
	return true;
}

template <typename Type>
Type Single_list<Type>::front() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Type Single_list<Type>::back() const {
	// enter your implementation here
	return Type();
}

template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
Single_node<Type> *Single_list<Type>::tail() const {
	// enter your implementation here
	return nullptr;
}

template <typename Type>
int Single_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
	return 0;
}

template <typename Type>
void Single_list<Type>::swap( Single_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Single_list<Type> &Single_list<Type>::operator=( Single_list<Type> const &rhs ) {
	Single_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Single_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
void Single_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
}

template <typename Type>
Type Single_list<Type>::pop_front() {
	// enter your implementation here
	return Type();
}

template <typename Type>
int Single_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Single_list<T> const &list ) {
	for ( Single_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?
