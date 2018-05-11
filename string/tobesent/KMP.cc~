#include <iostream>
#include <vector>
#include <LinkedList.h>


size_t* compute_prefix_function(char* P, size_t lP){
  size_t k=0;
  size_t* pi = new size_t[lP];

  pi--;
  
  for( unsigned int i=1; i<=lP; i++)
    std::cout << pi[i] << " ";
  std::cout << std::endl;

  for( size_t i=2; i<=lP; i++ ){
    while( k>0 && P[i] != P[k+1] )
      k = pi[k];
    if( P[i] == P[k+1] )
      k++;

    pi[i] = k;
  }


  for( unsigned int i=1; i<=lP; i++)
    std::cout << pi[i] << " ";
  std::cout << std::endl;

  return pi;
}


class LinkedList<size_t> KMP(char* T, char* P, size_t lT, size_t lP){

  if( lT < lP )
    throw "";

      
  size_t i=0;
  size_t s;
  size_t* pi;
  LinkedList<size_t> ll;
  
  pi = compute_prefix_function(P, lP);
  
  for( s=1; s<=lT; s++){
    while( i>0 && T[s] != P[i+1] )
      i = pi[i];

    if( P[i+1] == T[s] )
      i++;

    if( i == lP )
      ll.push_back(s-i);
  }
  
  delete[] (pi+1);
  return ll;
}



int main(){

  std::vector<char> t{'a','b','c','x','a','b','c','d','a','b','x','a','b','c','d','a','b','c','d','a','b','c','y'};

  std::vector<char> p{'a','b','c','d','a','b','c','y'};

  for( unsigned int i=0; i<t.size(); i++)
    std::cout << t[i] << " ";
  std::cout << std::endl;
  
  char* T = new char[t.size()];
  char* P = new char[p.size()];

  for(unsigned int i=0; i<t.size(); i++)
    T[i] = t[i];

  for(unsigned int i=0; i<p.size(); i++)
    P[i] = p[i];

  LinkedList<size_t> ll;

  ll = KMP(T-1, P-1, t.size(), p.size());
  
  return 0;
}
