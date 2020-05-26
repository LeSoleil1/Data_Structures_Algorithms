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

#ifndef CYCLIC_LIST_H
#define CYCLIC_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"

template <typename Type>
class Cyclic_list {
	private:
		Single_node<Type> *list_head;
		Single_node<Type> *list_tail;
		int list_size;

	public:
		Cyclic_list();
		Cyclic_list( Cyclic_list const & );
		~Cyclic_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Single_node<Type> *head() const;
		Single_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Cyclic_list & );
		Cyclic_list &operator=( Cyclic_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();

		int erase( Type const & );

        // Friends

        template <typename T>
        friend std::ostream &operator<<( std::ostream &, Cyclic_list<T> const & );

};

template <typename Type>
Cyclic_list<Type>::Cyclic_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// This constructor sets all member variables to 0 or nullptr, as appropriate. (O(1))
}

template <typename Type>
Cyclic_list<Type>::Cyclic_list( Cyclic_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// The copy constructor must create a new cyclicly linked list with a copy of all of the nodes...
	// within the copied linked list stored in the same order. Once a copy is made, any change to ... 
	// the original linked list must not affect the copy. (O(n))
	int counter = 0;
	Single_node<Type> * node = list.list_head;
	while (counter != list.list_size){
		this->push_back(node->retrieve());
		node = node->next();
		counter += 1;
	}
}

template <typename Type>
Cyclic_list<Type>::~Cyclic_list() {
	// The destructor must delete each of the nodes in the linked list. (O(n))
	while (list_size != 0){
		this->pop_front();
	}
}

template <typename Type>
int Cyclic_list<Type>::size() const {
	// Returns the number of items in the list. (O(1))
	return list_size;
}

template <typename Type>
bool Cyclic_list<Type>::empty() const {
	// Returns true if the list is empty, false otherwise. (O(1))
	return list_size == 0;
}

template <typename Type>
Type Cyclic_list<Type>::front() const {
	// Retrieves the object stored in the node pointed to by the head pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	return list_head->retrieve();
}

template <typename Type>
Type Cyclic_list<Type>::back() const {
	// Retrieves the object stored in the node pointed to by the tail pointer. This function throws a underflow if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}
	return list_tail->retrieve();
}

template <typename Type>
Single_node<Type> *Cyclic_list<Type>::head() const {
	// Returns the head pointer. (O(1))
	return list_head;
}

template <typename Type>
Single_node<Type> *Cyclic_list<Type>::tail() const {
	// Returns the tail pointer. (O(1))
	return list_tail;
}

template <typename Type>
int Cyclic_list<Type>::count( Type const &obj ) const {
	// Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
	if (list_size == 0){
		return 0;
	}
	Single_node<Type> *node = list_head;
	int element_counter = 0;
	int obj_counter = 0;
	while (node != nullptr && element_counter < list_size ){
		if (node->retrieve() == obj){
			obj_counter++;
		}
		node = node->next();
		element_counter++;
	}
	return obj_counter;
}

template <typename Type>
void Cyclic_list<Type>::swap( Cyclic_list<Type> &list ) {
	// The swap function swaps all the member variables of this linked list with those of the argument. (O(1))
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Cyclic_list<Type> &Cyclic_list<Type>::operator=( Cyclic_list<Type> const &rhs ) {
	// The assignment operator makes a copy of the argument and then swaps the member variables of this cyclic ...
	// linked list with those of the copy. (O(nlhs + nrhs))
	Cyclic_list<Type> copy( rhs );

	swap( copy );

	return *this;
}

template <typename Type>
void Cyclic_list<Type>::push_front( Type const &obj ) {
	// Creates a new Single_node<Type> storing the argument, the next pointer of which is set to the current head ...
	// pointer. The next pointer of the last node in the list are also set to the new node. If list was originally ...
	// empty, the next pointer of the new node is set to itself as is the tail pointer. (O(1))
	if (list_size == 0){
		Single_node<Type> * new_node = new Single_node<Type>(obj);
		list_head = new_node;
		list_tail = new_node;
		new_node->next_node = list_head;
		list_size = 1;
	}else{
		Single_node<Type> * new_node = new Single_node<Type>(obj);
		new_node->next_node = list_head;
		list_head = new_node;
		list_tail->next_node = list_head;
		list_size++;
	}
}

template <typename Type>
void Cyclic_list<Type>::push_back( Type const &obj ) {
	// Similar to push_front, this places a new node at the back of the list. (O(1))
	if (list_size == 0){
		Single_node<Type> * new_node = new Single_node<Type>(obj);
		list_head = new_node;
		list_tail = new_node;
		new_node->next_node = list_head;
		list_size = 1;
	}else{
		Single_node<Type> * new_node = new Single_node<Type>(obj);
		list_tail->next_node = new_node;
		list_tail = new_node;
		new_node->next_node = list_head;
		list_size++;
	}

}

template <typename Type>
Type Cyclic_list<Type>::pop_front() {
	// Delete the node at the front of the linked list and, as necessary, update the head ...
	// and tail pointers and the next pointer of any other node within the list. Return the ...
	// object stored in the node being popped. Throw an underflow exception if the list is empty. (O(1))
	if (list_size == 0){
		throw underflow();
	}else if (list_size == 1){
		Type return_value = list_head->retrieve();
		delete list_head;
		list_head = nullptr;
		list_tail = nullptr;
		list_size--;
		return return_value;
	}else{
		Single_node<Type> *temp_node = list_head->next();
		Type return_value = list_head->retrieve();
		delete list_head;
		list_head = temp_node;
		list_size--;
		return return_value;
	}	
}

template <typename Type>
int Cyclic_list<Type>::erase( Type const &obj ) {
	// Delete the first node (from the front) in the linked list that contains the object equal to the ...
	// argument (use == to to test for equality with the retrieved element). As necessary, update the head ...
	// and tail pointers and the next pointer of any other node within the list. Return the number of nodes that were deleted. (O(n))
	if (list_size == 0){
		return 0;
	}
	if (list_size == 1){
		if (list_head->retrieve() != obj){
			return 0;
		}
		delete list_head;
		list_head = nullptr;
		list_tail = nullptr;
		list_size = 0;
		return 1;
	}
	if (list_head->retrieve() == obj){
		Single_node<Type> *temp_node = list_head->next();
		delete list_head;
		list_head = temp_node;
		list_tail->next_node = list_head;
		list_size--;
		return 1;
	}
	Single_node<Type> *previous_node = list_head;
	Single_node<Type> *current_node = list_head->next();
	int counter = 1;
	while( counter != list_size){
		if (current_node->retrieve() == obj){
			if(current_node == list_tail){
				list_tail = previous_node;
			}
			previous_node->next_node = current_node->next();
			delete current_node;
			list_size--;
			return 1;
		}
		previous_node = current_node;
		current_node = current_node->next();
		counter++;
	}
	return 0;
}

template <typename Type>
std::ostream &operator<<( std::ostream &out, Cyclic_list<Type> const &list ) {
		int counter = 0;
        for ( Single_node<Type> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
				counter++;
                out << "->" << ptr->retrieve();
				if (counter == list.list_size){
					break;
				}
        }

        out << "->0";

        return out;
}

#endif
