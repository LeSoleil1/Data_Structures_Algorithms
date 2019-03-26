#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Linked_list.h"

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/
class Weighted_graph {
	private:
		static const double INF;
		int total_vertex_number;
		int *vertex_degree;
		double **AdjMatrix;
		int count;
		bool *MST_set;

		// your choice

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );

		// Friends

		friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};


const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

Weighted_graph::Weighted_graph(int n){
	total_vertex_number=n;
	AdjMatrix=new double*[n];
	for (int i=0;i<n;i++){
		AdjMatrix[i]=new double[n]{INF};
	}
	vertex_degree=new int[n]{0};
	count=0;
	MST_set=new bool[n]{0};



}

Weighted_graph::~Weighted_graph(){
	for (int i=0;i<total_vertex_number;i++){
		delete [] AdjMatrix[i];
	}
	delete[] AdjMatrix;
	count=0;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Accessors                                                                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Returns the degree of the vertex n. Throw an illegal argument exception if the argument does not correspond to an existing vertex. (O(1))
int Weighted_graph::degree(int vertex) const{
	return vertex_degree[vertex];
}

//Returns the number of edges in the graph. (O(1))
int Weighted_graph::edge_count() const{
	return count;
}

//Returns the weight of the edge connecting vertices m and n. If the vertices are equal, return 0. If the vertices are not adjacent, return infinity. Throw an illegal argument exception if the arguments do not correspond to existing vertices.
double Weighted_graph::adjacent(int m, int n) const{
	return AdjMatrix[m][n];
}

//Determine if the graph is connected.
bool Weighted_graph::is_connected() const{
	for(int i=0;i<total_vertex_number;i++){
		if(vertex_degree[i]==0)
			return false;
	}
	return true;
}

//Return the size of the minimum spanning tree of those nodes which are connected to vertex m. Throw an illegal argument exception if the arguments do not correspond to existing vertices.
double Weighted_graph::minimum_spanning_tree(int start_vertex) const {
	

	return 0.0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Mutators                                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//If the weight w < 0 or w = ∞, throw an illegal argument exception. If the weight w is 0, remove any edge between m and n (if any). Otherwise, add an edge between vertices m and n with weight w. If an edge already exists, replace the weight of the edge with the new weight. If the vertices do not exist or are equal, throw an illegal argument exception.
void Weighted_graph::insert(int m, int n, double w){
	if(w<0 || w==INF)
		throw illegal_argument();
	if(w=0){
		if(AdjMatrix[m][n]!=INF){
			vertex_degree[m]--;
			vertex_degree[n]--;
			count--;
		}
		AdjMatrix[m][n]=AdjMatrix[n][m]=INF;
		return;
	}if(AdjMatrix[m][n]==INF){
		count++;
		vertex_degree[m]++;
		vertex_degree[n]++;
	}
	AdjMatrix[m][n]=AdjMatrix[n][m]=w;
	return;

}



std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}



#endif
