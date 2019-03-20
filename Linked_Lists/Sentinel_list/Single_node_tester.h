/*************************************************
 * Single_node_tester<Type>
 * A class for testing nodes used in singly linked lists.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-2010 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef SINGLE_NODE_TESTER_H
#define SINGLE_NODE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Single_node.h"

#include <iostream>

template <typename Type>
class Single_node_tester:public Tester< Single_node<Type> > {
	using Tester< Single_node<Type> >::object;
	using Tester< Single_node<Type> >::command;

	public:
		Single_node_tester( Single_node<Type> *obj = nullptr ):Tester< Single_node<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For single nodes, these include:
 *
 *                 Member
 *   Flag         Function         Tests if ...
 *
 *  Accessors
 *
 *   next          next()          the next pointer can be followed
 *   next0         next()          the next pointer is 'nullptr'
 *   retrieve n    retrieve()      the stored value is n
 ****************************************************/

template <typename Type>
void Single_node_tester<Type>::process() {
	if ( command == "next" ) {
		Single_node<Type> *actual_next = Single_node_tester<Type>::object->next();

		if ( actual_next != nullptr ) {
			object = actual_next;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in next(): expecting to follow a non-null next pointer" << std::endl;
		}
	} else if ( command == "next0" ) {
		if ( object->next() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in next(): expecting a null (nullptr) next pointer" << std::endl;
		}
	} else if ( command == "retrieve" ) {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = object->retrieve();

		if ( expected_value == actual_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in retrieve(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif