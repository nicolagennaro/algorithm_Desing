#include <Graph.h>
#include <MinHeap.h>
#include <iostream>
#include <vector>



int main(){

  Graph g;
  g.print();

  g.Tarjan_SCC();
  g.print_SCC();
  

  return 0;
}
