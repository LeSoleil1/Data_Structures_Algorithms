#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/
class Linked_list{
	private:
		class Linked_list_node{
			public:
				Linked_list_node* next_node;
				Linked_list_node* previous_node;
				int othervertex;
				double distance;
		};

		Linked_list_node *head;
		Linked_list_node *tail;
		int numberOfNodes;
	public:
		Linked_list();
		~Linked_list();
		void insert(int, double);
		bool deleteNode(Linked_list_node *);
		Linked_list_node* member(int);
		int size();




};

Linked_list::Linked_list(){
	head=nullptr;
	tail=nullptr;
	numberOfNodes=0;
}

Linked_list::~Linked_list(){
	Linked_list_node *pointer_to_node=head;
	Linked_list_node *next_to_delete;
	if(head!=tail)
		next_to_delete=head->next_node;
	for (int i=0;i<numberOfNodes;i++){
		deleteNode(pointer_to_node);
		pointer_to_node=next_to_delete;
		if(next_to_delete->next_node!=nullptr)
			next_to_delete=next_to_delete->next_node;
	}

	head=nullptr;
	tail=nullptr;
	numberOfNodes=0;

}

void Linked_list::insert(int vertex2,double inner_distance){
	Linked_list_node *node_existance=member(vertex2);
	if(node_existance==nullptr){
		Linked_list_node *new_node=new Linked_list_node;
		new_node->next_node=nullptr;
		if(numberOfNodes==0){
			head=new_node;
			tail=new_node;
		}
		else{
			tail->next_node=new_node;
			new_node->previous_node=tail;
		}
		new_node->othervertex=vertex2;
		new_node->distance=inner_distance;
		numberOfNodes++;
	}else{
		node_existance->distance=inner_distance;
	}

}

bool Linked_list::deleteNode(Linked_list_node  *node_to_delete){
	node_to_delete->previous_node->next_node=node_to_delete->next_node;
	node_to_delete->next_node->previous_node=node_to_delete->previous_node;
	if(head==node_to_delete){
		head=node_to_delete->next_node;
	}
	if(tail==node_to_delete){
		tail=node_to_delete->previous_node;
	}
	delete node_to_delete;
	numberOfNodes--;
	return true;

}

Linked_list::Linked_list_node * Linked_list::member(int checking_vertex){
	if(numberOfNodes==0)
		return nullptr;
	Linked_list_node* current_node=head;
	for (int i=0;i<numberOfNodes;i++){
		if(current_node->othervertex==checking_vertex)
			return current_node;
		current_node=current_node->next_node;

	}
	return nullptr;
}

#endif


