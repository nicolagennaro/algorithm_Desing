#include <Graph1.h>
#include <iostream>


class Weighted_Graph: public Graph{

public:
  std::vector<std::vector<unsigned int>> W;

  Weighted_Graph(std::vector<std::vector<int>>& adj, std::vector<std::vector<unsigned int>>& w): Adj{adj}, W{w} {}

  void print() const {
	  for( unsigned int i = 0; i<Adj.size(); i++){
	    std::cout << "Node " << i << std::endl;
	    for( unsigned int j = 0; j<Adj[i].size(); j++)
	      std::cout << Adj[i][j] << "\t";
	    std::cout << std::endl;
	    for( unsigned int j = 0; j<Adj[i].size(); j++)
	      std::cout << W[i][j] << "\t";
	    std::cout << std::endl;
	  }
  }

};



int main(){

  return 0;
}
