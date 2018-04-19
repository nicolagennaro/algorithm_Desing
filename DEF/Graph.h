#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <vector>
#include <limits>

enum class color{white, grey, black};

std::ostream& operator<<(std::ostream& os, color col){
	switch(col){
			case color::black:
						os << "black";
						break;
			case color::grey:
						os << "grey";
						break;
			case color::white:
						os << "white";
						break;
		}
	return os;
}


class Graph{

 public:
	std::vector<std::vector<unsigned int>> Adj;

        Graph(): Adj{} {}
	
        Graph(std::vector<std::vector<unsigned int>>& adj): Adj{adj} {};

	size_t size() const { return Adj.size(); }
	
	void print() const {
	  for( unsigned int i = 0; i<Adj.size(); i++){
	    std::cout << "Node " << i << std::endl;
	    for( unsigned int j = 0; j<Adj[i].size(); j++)
	      std::cout << Adj[i][j] << "\t";
	    
	    std::cout << std::endl;
	  }
	}
	
	unsigned int *adj_matrix() const;
	
};

unsigned int* Graph::adj_matrix() const{
	size_t size = this->size();
	unsigned int *adj_mat = new unsigned int[size*size];
	
	for( size_t i=0; i<size; i++)
		for( size_t j=0; j<size; j++)
			adj_mat[ i*size + j ] = 0;

	for( size_t i=0; i<Adj.size(); i++ ){
		for( size_t j=0; j<Adj[i].size(); j++ )
			adj_mat[ i*size + Adj[i][j] ] = 1;
	}
	
	return adj_mat;
}


#endif // __GRAPH__
