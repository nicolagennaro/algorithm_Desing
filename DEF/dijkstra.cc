#include <iostream>
#include <Graph.h>
#include <BinaryHeap.h>
#include <vector>
// #include <>


template<typename T>
class MyValueComparator{
public:
  static int CMP(const T& a, const T& b){
    if( b>a ) return 1;
    else if( a>b ) return -1;
    else return 0;
  }
};


void dijkstra(Graph& G, std::vector<std::vector<double>>& W, unsigned int s){


}




int main(){

  std::vector<int> v{5,4,3,2,1,43,44,45,64,24,12,44,44};

  BinaryHeap<int> max_heap{v};

  std::cout << "heap_ done" << std::endl;
  
  for( unsigned int i=0; i<v.size(); i++)
    std::cout << max_heap[i] << " ";
  std::cout << std::endl;

  std::cout << "\nnow print test" << std::endl;
  while( !max_heap.empty() ){
    std::cout << max_heap.delete_root() << std::endl;
  }


  BinaryHeap<int, MyValueComparator> min_heap{v};

    std::cout << "\nnow print test" << std::endl;
  while( !min_heap.empty() ){
    std::cout << min_heap.delete_root() << std::endl;
  }
  
  return 0;
}
