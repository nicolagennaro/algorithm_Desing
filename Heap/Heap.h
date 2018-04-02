#include <iostream>
#include <vector>
// #include <cstdlib>

#ifndef __HEAP__
#define __HEAP__


template<typename T>
class Heap{
  std::vector<T> v;
  void BubbleDown(unsigned int);
  void BubbleUp(unsigned int);
  bool (*compare)(T, T);  // true if greater

public:
  Heap(std::vector<T>&, bool (*)(T, T) );

  void Insert(T);
  T Top();
  void Pop();
  void Heapify();
  
  bool empty(){ return v.empty(); }
};


template<typename T>
Heap<T>::Heap(std::vector<T>& vec, bool(*c)(T, T) ){
  v = vec;
  compare = c;
  Heapify();
}


template<typename T>
void Heap<T>::Heapify(){
  for(unsigned int i=v.size()-1; i>=0 && i<v.size(); i--)
    BubbleDown(i);
}



template<typename T>
void Heap<T>::BubbleDown(unsigned int n){

  unsigned int left_child=2*n+1, right_child=2*n+2;

  if(left_child >= v.size() )
    return;

  unsigned int min_index = n;

  if( compare(v[n], v[left_child]) )
    min_index = left_child;

  if( right_child < v.size() && compare(v[min_index], v[right_child]) )
    min_index = right_child;

  if( min_index != n ){
    T temp = v[n];
    v[n] = v[min_index];
    v[min_index] = temp;
    BubbleDown(min_index);
  }
}

template<typename T>
void Heap<T>::BubbleUp(unsigned int n){
  if( n==0 )
    return;

  unsigned int parent=(n-1)/2;

  if( compare(v[parent], v[n]) ){
    T temp = v[parent];
    v[parent] = v[n];
    v[n] = temp;
    BubbleUp(parent);
  } 
}

template<typename T>
void Heap<T>::Insert(T new_value){
  v.push_back(new_value);
  BubbleUp(v.size()-1);
}


template<typename T>
T Heap<T>::Top(){
  return v[0];
}

template<typename T>
void Heap<T>::Pop(){
  if(v.size() == 0)
    return;

  v[0] = v[v.size()-1];
  v.pop_back();
  BubbleDown(0);
}

#endif // __HEAP__

