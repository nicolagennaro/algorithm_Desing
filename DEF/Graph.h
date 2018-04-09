#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <vector>

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
	
};


#endif // __GRAPH__
