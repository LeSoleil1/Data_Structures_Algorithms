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

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie
{
private:
	Trie_node *root_node;
	int trie_size;

public:
	Trie();
	~Trie();

	// Accessors
	std::string lowerStr(std::string const &);
	int size() const;
	bool empty() const;
	bool member(std::string const &) const;
	Trie_node *root() const;
	// Mutators

	bool insert(std::string const &);
	bool erase(std::string const &);
	void clear();

	// Friends

	friend std::ostream &operator<<(std::ostream &, Trie const &);
};
// check that all elements are alpahbets
// convert all characters to lowercase

Trie::Trie() : root_node(nullptr),
			   trie_size(0)
{
	root_node = new Trie_node();
	// empty constructor
}

Trie::~Trie()
{
}

int Trie::size() const
{
	// Returns the number of words in the trie. (O(1))
	return trie_size;
}

bool Trie::empty() const
{
	// Return true if the trie is empty (the size is 0). (O(1))
	return (trie_size == 0);
}

Trie_node *Trie::root() const
{
	// Returns the number of words in the trie. (O(1))
	return root_node;
}

bool Trie::member(std::string const &str) const
{
	/* Return true if the word represented by the string is in the Trie and false otherwise. 
	If the string contains any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), 
	throw an illegal_argument exception. (O(n)) */
	if (empty())
	{
		return false;
	}
	else
	{
		std::string tempStr = str;
		for (int i = 0; i < tempStr.length(); i++)
		{
			if (!isalpha(tempStr[i]))
				throw illegal_argument();
			tempStr[i] = tolower(tempStr[i]);
		}
		return (root_node->member(tempStr, 0));
	}
}

bool Trie::insert(std::string const &str)
{
	// Insert the word represented by str into the tree. (O(n))
	std::string tempStr = lowerStr(str);
	if (member(tempStr))
	{
		return false;
	}
	else
	{
		bool insertResult = root_node->insert(tempStr, 0);
		if (insertResult == true)
			trie_size++;
		return insertResult;
	}
}

std::string Trie::lowerStr(std::string const &str)
{
	std::string tempStr = str;
	for (int i = 0; i < tempStr.length(); i++)
	{
		if (!isalpha(tempStr[i]))
			throw illegal_argument();
		tempStr[i] = tolower(tempStr[i]);
	}
	return tempStr;
}

bool Trie::erase(std::string const &str)
{
	// Erase the word represented by str from the tree. (O(n))
	std::string tempStr = lowerStr(str);
	if (member(tempStr))
	{
		bool eraseResult = root_node->erase(tempStr, 0, root_node);
		if (eraseResult == true)
			trie_size--;
		return eraseResult;
	}
	return member(str);
}

void Trie::clear()
{
	// Delete all the nodes in the tree. (O(N) where N is the number of words in the tree)
	if (empty())
	{
		return;
	}
	else
	{
		root_node->clear();
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<(std::ostream &out, Trie const &trie)
{
	return out;
}

#endif