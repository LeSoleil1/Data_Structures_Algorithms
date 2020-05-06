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


#endif
