#include <iostream>
#include <vector>
#include <Heap.h>


bool great(int a, int b){
  return a>b;
}

bool less(int a, int b){
  return a<b;
}



int main(){
  
  std::vector<int> vec;

    for(int i=0; i<10; i++){
    vec.push_back(rand() % 10);
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
  
  Heap<int> heap{vec, &great};
  for(int i=0; i<10; i++){
  	std::cout << heap.Top() << std::endl;
  	heap.Pop();
  }

  std::cout << "heap top" << std::endl;
  std::cout << heap.Top() << std::endl;
  heap.Pop();

  std::cout << "heap top" << std::endl;
  std::cout << heap.Top() << std::endl;


  
  std::cout << "heap" << std::endl;
  std::vector<int> v;
  v.push_back(3);
  std::cout << v[0] << std::endl;
    if( v.empty() )
  	std::cout << "empty" << std::endl;
  v.pop_back();
  if( v.empty() )
  	std::cout << "empty" << std::endl;
  std::cout << v[0] << std::endl;


  
  std::cout << "another heap" << std::endl;
  Heap<int> heap1{vec, &less};


  std::cout << "insert -12" << std::endl;
  heap1.Insert(-12);
  while( !heap1.empty() ){
    	std::cout << heap1.Top() << std::endl;
  	heap1.Pop();
  }

  
  std::cout << "insert 12" << std::endl;
  heap1.Insert(12);
    while( !heap1.empty() ){
    	std::cout << heap1.Top() << std::endl;
  	heap1.Pop();
  }


  
  return 0;
}
