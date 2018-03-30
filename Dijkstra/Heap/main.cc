#include <Graph.h>
#include <MinHeap.h>
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

  std::vector<std::vector<int>> Adj;
  std::vector<int> temp;
  std::vector<std::vector<double>> Weights;
  std::vector<double> t;


  temp = {1,2};
  t = {4.0, 2.0};
  Adj.push_back(temp);
  Weights.push_back(t);
  
  temp = {2,3,4};
  t = {3.0,2.0,3.0};  
  Adj.push_back(temp);
  Weights.push_back(t);

  temp = {1,3,4};
  t = {1.0,4.0,5.0};
  Adj.push_back(temp);
  Weights.push_back(t);
  
  temp = {};
  t = {};
  Adj.push_back(temp);
  Weights.push_back(t);
  
  temp = {3};
  t = {1.0};
  Adj.push_back(temp);
  Weights.push_back(t);
  
    
  Graph g1{Adj, Weights};
  g1.print();


  std::cout << "MIN HEAP" << std::endl;
  std::vector<int> vf{1,5,3,7,8,3,2};

  // for(int i=0; i<10; i++){
  //   vf.push_back(rand() % 10);
  //   std::cout << vf[i] << " ";
  // }
  // std::cout << std::endl;
  
  MinHeap<int> heap{vf, &great};

  while( !heap.empty() ){
    	std::cout << heap.Top() << std::endl;
  	heap.Pop();
  }

  MinHeap<int> maxheap{vf, &less};

  while( !maxheap.empty() ){
    	std::cout << maxheap.Top() << std::endl;
  	maxheap.Pop();
  }  
  return 0;
}
