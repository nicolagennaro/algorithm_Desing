#include <iostream>
#include <vector>
#include <cstdlib>




template<typename T>
class MinHeap{
  std::vector<T> v;
  void BubbleDown(unsigned int);
  void BubbleUp(unsigned int);
  void Heapify();

public:
  MinHeap(std::vector<T>&);

  void Insert(T);
  T Top();
  void Pop();
  
  bool empty(){ return v.empty(); }
};


template<typename T>
MinHeap<T>::MinHeap(std::vector<T>& vec){
  v = vec;
  Heapify();
}


template<typename T>
void MinHeap<T>::Heapify(){
  for(unsigned int i=v.size()-1; i>=0 && i<v.size(); i--){
    std::cout << "bubble down " << i << std::endl;
    BubbleDown(i);
    }
   std::cout << "finish heapify" << std::endl;
}

template<typename T>
void MinHeap<T>::BubbleDown(unsigned int n){

  //std::cout << "Down" << std::endl;
  //int kjf;
  //std::cin >> kjf;
  unsigned int left_child=2*n+1, right_child=2*n+2;

  if(left_child >= v.size() )
    return;

  unsigned int min_index = n;

  if(v[n] > v[left_child])
    min_index = left_child;

  if( right_child < v.size() && v[min_index] > v[right_child] )
    min_index = right_child;

  if( min_index != n ){
    T temp = v[n];
    v[n] = v[min_index];
    v[min_index] = temp;
    BubbleDown(min_index);
  }
}

template<typename T>
void MinHeap<T>::BubbleUp(unsigned int n){
  if( n==0 )
    return;

  unsigned int parent=(n-1)/2;

  if( v[parent] > v[n] ){
    T temp = v[parent];
    v[parent] = v[n];
    v[n] = temp;
    BubbleUp(parent);
  } 
}

template<typename T>
void MinHeap<T>::Insert(T new_value){
  v.push_back(new_value);
  BubbleUp(v.size()-1);
}


template<typename T>
T MinHeap<T>::Top(){
  return v[0];
}

template<typename T>
void MinHeap<T>::Pop(){
  if(v.size() == 0)
    return;

  v[0] = v[v.size()-1];
  v.pop_back();
  BubbleDown(0);
}

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
