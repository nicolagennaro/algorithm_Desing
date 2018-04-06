#include<Graph_struct.h>
#include<iostream>


int main(){

  // graph pag 116 dasgupta
  std::vector<std::vector<int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  for( std::vector<int> i : Adj )
    for( auto j : i )
      std::cout << j << std::endl;
  
  std::vector<std::vector<double>> Weights{ {4.0,2.0}, {3.0,2.0,3.0}, {1.0,4.0,5.0}, {}, {1.0} };


  Graph g1{Adj, Weights};
  g1.print();
  
  g1.dfs();

  std::vector<std::vector<int>> SCCs;

  SCCs = g1.Tarjan_SCC();
  for( unsigned int i=0; i<SCCs.size(); i++ ){
  	std::cout << "SCC number " << i << std::endl;
  	for( unsigned int j=0; j<SCCs[i].size(); j++ )
  		std::cout << SCCs[i][j] << "\t";
  	std::cout << std::endl << std::endl;
  }
  
  SCCs = g1.Tarjan_SCC();
  for( unsigned int i=0; i<SCCs.size(); i++ ){
  	std::cout << "SCC number " << i << std::endl;
  	for( unsigned int j=0; j<SCCs[i].size(); j++ )
  		std::cout << SCCs[i][j] << "\t";
  	std::cout << std::endl << std::endl;
  }
  
  g1.print();
  
  Graph collapsed;
  collapsed = g1.collapse();
  
  collapsed.print();
  
  std::vector<std::pair<int,int>> r;
  r = g1.topological_sort1();
  for( unsigned int i=0; i<r.size(); i++){
  	std::cout << "Node " << r[i].first << " S: " << r[i].second << std::endl;
  }
  
  g1.Fischer_Mayer();
    
  return 0;
}
