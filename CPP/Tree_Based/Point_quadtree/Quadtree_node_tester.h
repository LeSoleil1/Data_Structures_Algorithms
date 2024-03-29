#ifndef QUADTREE_NODE_TESTER_H
#define QUADTREE_NODE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Quadtree_node.h"

#include <iostream>

template <typename Type>
class Quadtree_node_tester:public Tester< Quadtree_node<Type> > {
	public:
		Quadtree_node_tester( Quadtree_node<Type> *obj = 0 ):Tester< Quadtree_node<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For quadtree nodes, these include:
 *
 *  Accessors
 *
 *   x n           retrieve_x()    the x value stored is n
 *   y n           retrieve_y()    the y value stored is n
 *
 *   nw            nw()            the north-west pointer can be followed
 *   nw0           nw()            the north-west pointer is 0
 *   sw            sw()            the south-west pointer can be followed
 *   sw0           sw()            the south-west pointer is 0
 *   ne            ne()            the north-east pointer can be followed
 *   ne0           ne()            the north-east pointer is 0
 *   se            se()            the south-east pointer can be followed
 *   se0           se()            the south-east pointer is 0
 *
 *  Others
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
void Quadtree_node_tester<Type>::process() {
	if ( Quadtree_node_tester<Type>::command == "nw" ) {
		Quadtree_node<Type> *actual_nw = Quadtree_node_tester<Type>::object->nw();

		if ( actual_nw != 0 ) {
			Quadtree_node_tester<Type>::object = actual_nw;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in nw(): expecting to follow a non-null nw pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "nw0" ) {
		if ( Quadtree_node_tester<Type>::object->nw() == 0 ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in nw(): expecting a null (0) nw pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "ne" ) {
		Quadtree_node<Type> *actual_ne = Quadtree_node_tester<Type>::object->ne();

		if ( actual_ne != 0 ) {
			Quadtree_node_tester<Type>::object = actual_ne;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in ne(): expecting to follow a non-null ne pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "ne0" ) {
		if ( Quadtree_node_tester<Type>::object->ne() == 0 ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in ne(): expecting a null (0) ne pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "sw" ) {
		Quadtree_node<Type> *actual_sw = Quadtree_node_tester<Type>::object->sw();

		if ( actual_sw != 0 ) {
			Quadtree_node_tester<Type>::object = actual_sw;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in sw(): expecting to follow a non-null sw pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "sw0" ) {
		if ( Quadtree_node_tester<Type>::object->sw() == 0 ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in sw(): expecting a null (0) sw pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "se" ) {
		Quadtree_node<Type> *actual_se = Quadtree_node_tester<Type>::object->se();

		if ( actual_se != 0 ) {
			Quadtree_node_tester<Type>::object = actual_se;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in se(): expecting to follow a non-null se pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "se0" ) {
		if ( Quadtree_node_tester<Type>::object->se() == 0 ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in se(): expecting a null (0) se pointer" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "x" ) {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = Quadtree_node_tester<Type>::object->retrieve_x();

		if ( expected_value == actual_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in retrieve_x(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	} else if ( Quadtree_node_tester<Type>::command == "y" ) {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = Quadtree_node_tester<Type>::object->retrieve_y();

		if ( expected_value == actual_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in retrieve_y(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	} else {
		std::cout << Quadtree_node_tester<Type>::command << ": Command not found." << std::endl;
	}
}
#endif
