#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <vector>



class Graph{

 public:
	std::vector<std::vector<int>> Adj;

        Graph(std::vector<std::vector<int>>& adj): Adj{adj};

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
