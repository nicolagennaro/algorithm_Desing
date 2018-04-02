#include <iostream>
#include <Graph.h>
#include <vector>


int main(){


  std::vector<std::vector<int>> Adj{ {1}, {2,4}, {3,6}, {2,7}, {0,5}, {6}, {5,7}, {7} };
std::vector<std::vector<double>> Weights{ {1.0}, {1.0,1.0}, {1.0,1.0}, {1.0,1.0}, {1.0,1.0}, {1.0}, {1.0,1.0}, {1.0} };


  Graph g1{Adj, Weights};

  g1.print();

  g1.Fischer_Mayer();
  
  return 0;
}
