#include <iostream>
#include <vector>
#include <MinHeap.h>

int main(){
  std::vector<int> vec;

    for(int i=0; i<10; i++){
    vec.push_back(rand() % 10);
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
  
  MinHeap<int> heap{vec};
  for(int i=0; i<10; i++){
  	std::cout << heap.Top() << std::endl;
  	heap.Pop();
  }
  
  std::cout << heap.Top() << std::endl;
  heap.Pop();
  std::cout << heap.Top() << std::endl;
  
  std::vector<int> v;
  v.push_back(3);
  std::cout << v[0] << std::endl;
    if( v.empty() )
  	std::cout << "empty" << std::endl;
  v.pop_back();
  if( v.empty() )
  	std::cout << "empty" << std::endl;
  std::cout << v[0] << std::endl;
  
  MinHeap<int> heap1{vec};
  heap1.Insert(-12);
  while( !heap1.empty() ){
    	std::cout << heap1.Top() << std::endl;
  	heap1.Pop();
  }
  
  heap1.Insert(12);
    while( !heap1.empty() ){
    	std::cout << heap1.Top() << std::endl;
  	heap1.Pop();
  }


  
  return 0;
}
