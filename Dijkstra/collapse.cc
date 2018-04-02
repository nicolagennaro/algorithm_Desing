#include <Graph.h>
// #include <Heap.h>
#include <iostream>
#include <vector>



int main(){

  // Graph g;
  // g.print();

  // g.Tarjan_SCC();
  // g.print_SCC();
  

  // g.dfs();

  // g.bfs();
 
  // GRAPH dijkstra   
  // std::vector<std::vector<int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  // for( i : Adj )
  //   for( j : i )
  //     std::cout << j << std::endl;
  
  // std::vector<std::vector<double>> Weights{ {4.0,2.0}, {3.0,2.0,3.0}, {1.0,4.0,5.0}, {}, {1.0} };






  // GRAPH pag 616 b (this is the transposed)
  // std::vector<std::vector<int>> Adj{ {4}, {0}, {1,3}, {2}, {1}, {4,6}, {2,5}, {3,6,7} };
  // for( i : Adj )
  //   for( j : i )
  //     std::cout << j << std::endl;
  
  // std::vector<std::vector<double>> Weights{ {1.0}, {1.0}, {1.0,1.0}, {1.0}, {1.0}, {1.0,1.0}, {1.0,1.0}, {1.0,1.0,1.0} };


// graph pag 616 a 
  std::vector<std::vector<int>> Adj{ {1}, {2,4}, {3,6}, {2,7}, {0,5}, {6}, {5,7}, {7} };
std::vector<std::vector<double>> Weights{ {1.0}, {1.0,1.0}, {1.0,1.0}, {1.0,1.0}, {1.0,1.0}, {1.0}, {1.0,1.0}, {1.0} };


  Graph g1{Adj, Weights};

  g1.print();
  
  g1.Tarjan_SCC();


  Graph collapsed{Adj, Weights};

  collapsed = g1.collapse();

  collapsed.print();

  std::vector<int> sort;
  sort = collapsed.topological_sort();
  for(unsigned int i=0; i<sort.size(); i++)
    std::cout << sort[i] << " " << std::endl;
  std::cout << std::endl;
  
  return 0;
}
