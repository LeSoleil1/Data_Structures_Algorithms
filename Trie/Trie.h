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

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;
		std::string strToLower(std::string const &) const;
		bool strValidity(std::string const &) const;



	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();


		// Friends

		friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
	root_node( nullptr ),
	trie_size( 0 ) {
		// empty constructor
	}

Trie::~Trie() {
	if(!empty())
		root_node->clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	return (trie_size==0);
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	if (empty()){
		return false;
	}
	if(!strValidity(str))
		throw illegal_argument();

	return root_node->member(strToLower(str),0);
}

bool Trie::insert( std::string const &str ) {
	if (empty()){
		root_node=new Trie_node();
	}
	if(!strValidity(str))
		throw illegal_argument();
	if (member(str))
		return false;
	bool insertionResult=false;
	if(root_node->insert(strToLower(str),0)==true){
		trie_size++;
		insertionResult=true;
	}
	return insertionResult;
}

bool Trie::erase( std::string const &str ) {
	if(empty())
		return false;
	if(!member(str))
		return false;
	if(!strValidity(str))
		throw illegal_argument();

	if(root_node->erase(strToLower(str),0,root_node)){
		trie_size--;
		if(trie_size==0)
			delete root_node;
		return true;
	}

	return false;
}
std::string Trie::strToLower(std::string const &str) const{
	std::string returnString;
	for (int i=0;i<str.size();i++){
		returnString[i]=std::tolower(str[i]);
	}
	return returnString;


}
bool Trie::strValidity(std::string const &str) const{
	for (int i=0;i<str.size();i++){
		if(!std::isalpha(str[i]))
			return false;
	}
	return true;

}

void Trie::clear() {
	if(!empty()){
		root_node->clear();
		trie_size=0;
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
