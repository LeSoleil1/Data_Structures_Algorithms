#ifndef QUADTREE_TESTER_H
#define QUADTREE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Quadtree.h"
#include "Quadtree_node.h"
#include "Quadtree_node_tester.h"

#include <iostream>

template <typename Type>
class Quadtree_tester:public Tester< Quadtree<Type> > {
	using Tester< Quadtree<Type> >::object;
	using Tester< Quadtree<Type> >::command;

	public:
		Quadtree_tester( Quadtree<Type> *obj = 0 ):Tester< Quadtree<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For quadtrees, these include:
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   empty b         empty           the result is the Boolean value b
 *
 *   min_x x         min_x           x is the smallest x value in the quadtree
 *   max_x x         max_x           x is the largest x value in the quadtree
 *   min_y y         min_y           y is the smallest y value in the quadtree
 *   max_y y         min_y           y is the smallest y value in the quadtree
 *
 *   sum_x x         sum_x           x is the sum of the x values in the quadtree
 *   sum_y y         sum_y           y is the sum of the y values in the quadtree
 *
 *   root            root            the root is not 0 and starts a Quadtree_node_tester on that
 *                                   node until the 'exit' command is typed
 *   root0           root            the root is 0
 *   member x y b    member          (x, y) is a member of the quadtree
 *
 *  Mutators
 *
 *   insert x y      insert          insert the pair (x, y) into the quadtree ignoring duplicates
 *   clear           clear           deletes all the children from the quadtree
 *
 *  Others
 *   cout            cout << list    print the list (for testing only)
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
void Quadtree_tester<Type>::process() {
	if ( command == "new") {
		object = new Quadtree<Type>();
		std::cout << "Okay" << std::endl;
	}
	else if ( command == "size" ) {
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
	} else if ( command == "min_x" ) {
		// checks if the smallest x value is that returned by this function

		Type expected_min_x;

		std::cin >> expected_min_x;

		Type actual_min_x = object->min_x();

		if ( actual_min_x == expected_min_x ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in min_x(): expecting the value '" << expected_min_x << "' but got '" << actual_min_x << "'" << std::endl;
		}
	} else if ( command == "min_y" ) {
		// checks if the smallest y value is that returned by this function

		Type expected_min_y;

		std::cin >> expected_min_y;

		Type actual_min_y = object->min_y();

		if ( actual_min_y == expected_min_y ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in min_y(): expecting the value '" << expected_min_y << "' but got '" << actual_min_y << "'" << std::endl;
		}
	} else if ( command == "max_x" ) {
		// checks if the largest x value is that returned by this function

		Type expected_max_x;

		std::cin >> expected_max_x;

		Type actual_max_x = object->max_x();

		if ( actual_max_x == expected_max_x ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in max_x(): expecting the value '" << expected_max_x << "' but got '" << actual_max_x << "'" << std::endl;
		}
	} else if ( command == "max_y" ) {
		// checks if the largest y value is that returned by this function

		Type expected_max_y;

		std::cin >> expected_max_y;

		Type actual_max_y = object->max_y();

		if ( actual_max_y == expected_max_y ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in max_y(): expecting the value '" << expected_max_y << "' but got '" << actual_max_y << "'" << std::endl;
		}
	} else if ( command == "sum_x" ) {
		// checks if the sum of the x values is that returned by this function

		Type expected_sum_x;

		std::cin >> expected_sum_x;

		Type actual_sum_x = object->sum_x();

		if ( actual_sum_x == expected_sum_x ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in sum_x(): expecting the value '" << expected_sum_x << "' but got '" << actual_sum_x << "'" << std::endl;
		}
	} else if ( command == "sum_y" ) {
		// checks if the sum of the y values is that returned by this function

		Type expected_sum_y;

		std::cin >> expected_sum_y;

		Type actual_sum_y = object->sum_y();

		if ( actual_sum_y == expected_sum_y ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in sum_y(): expecting the value '" << expected_sum_y << "' but got '" << actual_sum_y << "'" << std::endl;
		}
	} else if ( command == "root" ) {
		// checks that the root is not 0, and if it is not,
		// the next object gives the number of commands which should
		// be tested by the Quadtree_node_tester

		Quadtree_node<Type> *actual_root = object->root();

		if ( actual_root == 0 ) {
			std::cout << "Failure in root(): expecting a non-zero root pointer" << std::endl;
		} else {
			std::cout << "Okay" << std::endl;

			Quadtree_node_tester<Type> tester( actual_root );

			tester.run();
		}
	} else if ( command == "root0" ) {
		// check that the root pointer is 0

		if ( object->root() == 0 ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in root(): expecting a 0 root pointer" << std::endl;
		}
	} else if ( command == "member" ) {
		// check if the next object read in is in the linked list

		Type element_x;
		Type element_y;
		bool membership;

		std::cin >> element_x;
		std::cin >> element_y;
		std::cin >> membership;

		if ( object->member( element_x, element_y ) == membership ) {
			std::cout << "Okay" << std::endl;
		} else {
			if ( membership ) {
				std::cout << "Failure in member(): expecting the value (" << element_x << "," << element_y << ") to be in the quadtree" << std::endl;
			} else {
				std::cout << "Failure in member(): not expecting the value (" << element_x << "," << element_y << ") to be in the quadtree" << std::endl;
			}
		}
	} else if ( command == "insert" ) {
		// insert the next pair into the quadtree

		Type x, y;

		std::cin >> x;
		std::cin >> y;

		object->insert( x, y );
		std::cout << "Okay" << std::endl;
	} else if ( command == "clear" ) {
		// delete all the nodes in the tree

		object->clear();
		std::cout << "Okay" << std::endl;
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}

#endif
