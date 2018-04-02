#include <Graph.h>
#include <Heap.h>
#include <iostream>
#include <vector>


bool great(int a, int b){
  return a>b;
}

bool less(int a, int b){
  return a<b;
}

int main(){

  // Graph g;
  // g.print();

  // g.Tarjan_SCC();
  // g.print_SCC();
  

  // g.dfs();

  // g.bfs();

 
  {
  // graph pag 116 dasgupta
  std::vector<std::vector<int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  for( std::vector<int> i : Adj )
    for( auto j : i )
      std::cout << j << std::endl;
  
  std::vector<std::vector<double>> Weights{ {4.0,2.0}, {3.0,2.0,3.0}, {1.0,4.0,5.0}, {}, {1.0} };


  Graph g1{Adj, Weights};
  g1.print();
  
  //g1.dfs();

  //g1.bfs();
  
  g1.Dijkstra(0);
  }
  
  {
  
  // graph pag 659 Introduction to Algorithms
  std::vector<std::vector<int>> Adj{ {1,2}, {2,3}, {1,4}, {4}, {0,3} };
  for( std::vector<int> i : Adj )
    for( auto j : i )
      std::cout << j << std::endl;
  
  std::vector<std::vector<double>> Weights{ {10.0,5.0}, {2.0,1.0}, {3.0,2.0}, {4.0}, {7.0,6.0} };


  Graph g1{Adj, Weights};
  g1.print();
  
  //g1.dfs();

  //g1.bfs();
  
  g1.Dijkstra(0);
  }
  return 0;
}
