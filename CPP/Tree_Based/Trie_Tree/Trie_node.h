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

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node
{
private:
	Trie_node **children;
	bool is_terminal;
	static int const CHARACTERS = 26;
	bool reverseFlag = false;

public:
	Trie_node();
	~Trie_node();
	Trie_node *child(int) const;

	bool member(std::string const &, int) const;

	bool insert(std::string const &, int);
	bool erase(std::string const &, int, Trie_node *&);
	void clear();

	friend class Trie;

	// if ptr is a pointer to a Trie_node object
	// in one of the friendly classes, you should:
	//    use   ptr->next_   to modify it
	//    use   ptr->next()      to access it
};

Trie_node::Trie_node() : children(nullptr),
						 is_terminal(false)
{
}
Trie_node::~Trie_node()
{
	delete children;
}

Trie_node *Trie_node::child(int n) const
{
	/* Return a pointer to the n-th child. If the children array is empty, return nullptr; 
	otherwise, just return children[i]. This member function will never be called with a value outside 0 to 25. (O(1)) */
	if (children == nullptr)
	{
		return nullptr;
	}
	else
	{
		return children[n];
	}
}

bool Trie_node::member(std::string const &str, int depth) const
{

	if (depth == str.size() && this->is_terminal == true)
		return true;
	else
	{
		if (this->child(str[depth] - 'a') == nullptr || (depth == str.size() && this->is_terminal == false))
			return false;
		else
		{
			this->children[str[depth] - 'a']->member(str, depth + 1);
		}
	}
}

bool Trie_node::insert(std::string const &str, int depth)
{
	if (this->children == nullptr)
	{
		children = new Trie_node *[CHARACTERS];
		for (int i = 0; i < CHARACTERS; i++)
		{
			children[i] = nullptr;
		}
	}
	if (this->children[str[depth] - 'a'] == nullptr)
	{
		this->children[str[depth] - 'a'] = new Trie_node();
	}
	if ((str.size()) == depth)
	{
		this->is_terminal = true;
		return true;
	}
	else
	{

		return this->children[str[depth] - 'a']->insert(str, depth + 1);
		;
	}
}

bool Trie_node::erase(std::string const &str, int depth, Trie_node *&ptr_to_this)
{
	int NoChildren = 0;

	for (int i = 0; i < 26; i++)
	{
		if (children[i] != nullptr)
			NoChildren++;
	}
	if (depth == str.size())
	{
		if (this->is_terminal == true)
		{
			if (NoChildren == 0)
			{
				this->is_terminal = false;
				/*if (this->children == nullptr)
				{
					delete children;
					ptr_to_this = nullptr;
				}*/
				if (this->children[str[depth] - 'a'] == nullptr)
				{
					delete this;
					ptr_to_this = nullptr;
				}
				reverseFlag = true;
				return true;
			}
			else
			{
				this->is_terminal = false;
				return true;
			}
		}
	}
	else if (reverseFlag == true)
	{
		if (NoChildren == 0)
		{
			/*if (this->children == nullptr)
			{
				delete children;
				ptr_to_this = nullptr;
			}*/
			if (this->children[str[depth] - 'a'] == nullptr)
			{
				delete this;
				ptr_to_this = nullptr;
			}
			//reverseFlag = true;
			return true;
		}
		else
		{
			this->is_terminal = false;
			return true;
		}
	}
	else
	{
		return this->children[str[depth] - 'a']->erase(str, depth + 1, children[str[depth] - 'a']);
		//return true;
	}
}

void Trie_node::clear()
{
	for (int i = 0; i < 26; i++)
	{
		if (this->is_terminal == true)
		{
			this->is_terminal = false;
			if (this->children[i] == nullptr)
			{
				//children[i] = nullptr;

				delete this;
			}
		}
		else
		{
			//this->children[i]->erase("test", i + 1, children[i]);
			this->children[i]->clear();
			if (this->children[i] == nullptr)
			{
				//children[i] = nullptr;
				delete this;
			}
		}
	}
}


#endif
