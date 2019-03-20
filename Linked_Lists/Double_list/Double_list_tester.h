/*************************************************
 * Double_list_tester<Type>
 * A class for testing doubly linked lists.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-2010 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef DOUBLE_LIST_TESTER_H
#define DOUBLE_LIST_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Double_list.h"
#include "Double_node.h"
#include "Double_node_tester.h"

#include <iostream>

template <typename Type>
class Double_list_tester:public Tester< Double_list<Type> > {
	using Tester< Double_list<Type> >::object;
	using Tester< Double_list<Type> >::command;

	public:
		Double_list_tester( Double_list<Type> *obj = nullptr ):Tester< Double_list<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For doubly linked lists, these include:
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   empty b         empty           the result is the Boolean value b
 *   front n         front           n is the first element in the linked list
 *   front!          front           the underflow exception is thrown
 *   back n          back            n is the last element in the linked list
 *   back!           back            the underflow exception is thrown
 *   head            head            the head is not 0 and starts a Double_node_tester on that
 *                                   node until the 'exit' command is typed
 *   head0           head            the head is 'nullptr'
 *   tail            tail            the tail is not 0 and starts a Double_node_tester on that
 *                                   node until the 'exit' command is typed
 *   tail0           tail            the tail is 'nullptr'
 *   count n m       count           the number of occurances of n is m
 *
 *  Mutators
 *
 *   push_front n    push_front      the element can be pushed onto the front (always succeeds)
 *   push_back n     push_back       the element can be pushed onto the back (always succeeds)
 *   pop_front n     pop_front       the front element can be popped and equals n
 *   pop_front!      pop_front       the underflow exception is thrown
 *   pop_back n      pop_back        the back element can be popped and equals n
 *   pop_back!       pop_back        the underflow exception is thrown
 *   erase n m       erase           the number of erased occurances of n is m
 *
 *  Others
 *   assign          operator =      assign this list to a new list
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

template <typename Type>
void Double_list_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Double_list<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "front" ) {
		// checks if the first object in the linked list equals the next object read

		Type expected_front;

		std::cin >> expected_front;

		Type actual_front = object->front();

		if ( actual_front == expected_front ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in front(): expecting the value '" << expected_front << "' but got '" << actual_front << "'" << std::endl;
		}
	} else if ( command == "front!" ) {
		// front of an empty list - catch an exception

		Type actual_front;

		try {
			actual_front = object->front();
			std::cout << "Failure in front(): expecting to catch an exception but got '" << actual_front << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in front(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "back" ) {
		// checks if the last object in the linked list equals the next object read

		Type expected_back;

		std::cin >> expected_back;

		Type actual_back = object->back();

		if ( actual_back == expected_back ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in back(): expecting the value '" << expected_back << "' but got '" << actual_back << "'" << std::endl;
		}
	} else if ( command == "back!" ) {
		// back of an empty list - catch an exception

		Type actual_back;

		try {
			actual_back = object->back();
			std::cout << "Failure in back(): expecting to catch an exception but got '" << actual_back << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in back(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "head" ) {
		// checks that the head is not 'nullptr', and if it is not,
		// the next object gives the number of commands which should
		// be tested by the Double_node_tester

		Double_node<Type> *actual_head = object->head();

		if ( actual_head == nullptr ) {
			std::cout << "Failure in head(): expecting a non-zero head pointer" << std::endl;
		} else {
			std::cout << "Okay" << std::endl;

			Double_node_tester<Type> tester( actual_head );

			tester.run();
		}
	} else if ( command == "head0" ) {
		// check that the head pointer is 'nullptr'

		if ( object->head() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in head(): expecting a nullptr head pointer" << std::endl;
		}
	} else if ( command == "tail" ) {
		// checks that the tail is not 'nullptr', and if it is not,
		// the next object gives the number of commands which should
		// be tested by the Double_node_tester

		Double_node<Type> *actual_tail = object->tail();

		if ( actual_tail == nullptr ) {
			std::cout << "Failure in tail(): expecting a non-zero tail pointer" << std::endl;
		} else {
			std::cout << "Okay" << std::endl;

			Double_node_tester<Type> tester( actual_tail );

			tester.run();
		}
	} else if ( command == "tail0" ) {
		// check that the tail pointer is 'nullptr'

		if ( object->tail() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in tail(): expecting a nullptr tail pointer" << std::endl;
		}
	} else if ( command == "count" ) {
		// check if the next object read in is in the linked list

		Type element;
		int expected_count;

		std::cin >> element;
		std::cin >> expected_count;

		if ( object->count( element ) == expected_count ) {
			std::cout << "Okay" << std::endl;
		} else {
			if ( expected_count == 1 ) {
				std::cout << "Failure in count(): expecting the value '" << element << "' to be in the linked list" << std::endl;
			} else {
				std::cout << "Failure in count(): not expecting the value '" << element << "' to be in the linked list" << std::endl;
			}
		}
	} else if ( command == "push_front" ) {
		// push the next object read to the front of the linked list

		Type n;

		std::cin >> n;

		object->push_front( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "push_back" ) {
		// push the next object read to the back of the linked list

		Type n;

		std::cin >> n;

		object->push_back( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "pop_front" ) {
		// pop the first object from the linked list

		Type expected_popped_element;

		std::cin >> expected_popped_element;

		Type actual_popped_element = object->pop_front();

		if ( actual_popped_element == expected_popped_element ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in pop_front(): expecting the value '" << expected_popped_element << "' but got '" << actual_popped_element << "'" << std::endl;
		}
	} else if ( command == "pop_front!" ) {
		// pop from an empty list - catch an exception

		Type actual_popped_element;

		try {
			actual_popped_element = object->pop_front();
			std::cout << "Failure in pop_front(): expecting to catch an exception but got '" << actual_popped_element << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in pop_front(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "pop_back" ) {
		// pop the last object from the linked list

		Type expected_popped_element;

		std::cin >> expected_popped_element;

		Type actual_popped_element = object->pop_back();

		if ( actual_popped_element == expected_popped_element ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in pop_back(): expecting the value '" << expected_popped_element << "' but got '" << actual_popped_element << "'" << std::endl;
		}
	} else if ( command == "pop_back!" ) {
		// pop from an empty list - catch an exception

		Type actual_popped_element;

		try {
			actual_popped_element = object->pop_back();
			std::cout << "Failure in pop_back(): expecting to catch an exception but got '" << actual_popped_element << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in pop_back(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "erase" ) {
		Type n;
		int expected_count;

		std::cin >> n;
		std::cin >> expected_count;

		int actual_count = object->erase( n );

		if ( actual_count == expected_count ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in erase( " << n << " ): expecting the value '" << expected_count << "', but got " << actual_count << std::endl;
		}
	} else if ( command == "assign" ) {
		Double_list<Type> *new_object = new Double_list<Type>();

		*new_object = *(object);

		std::cout << "Okay" << std::endl;

		Double_list_tester<Type> tester( new_object );

		tester.run();
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}

#endif
