#include <iostream>
#include <vector>
#include <LinkedList.h>
#include <str.h>


class LinkedList<size_t> Naive_SM( str T, str P ){

  if( T.size() < P.size() )
    throw std::runtime_error("invalid strings");
  
  LinkedList<size_t> shifts;
  size_t i;
  
  for( size_t s = 0; s<(T.size() - P.size()); s++ ){
    i = 1;
    while( i<P.size() && P[i]==T[s+i] )
      i++;
    if( i>=P.size() ){
      shifts.push_back(s);
    }
  }

  
  for( LinkedList<size_t>::Iterator it = shifts.begin(); it != shifts.end(); ++it )
    std::cout << *it << "\t";
  std::cout << std::endl;
  
  return shifts;
}


int main(){

  std::vector<char> t{'a','b','c','a','b','a','a','b','c','a','b','a','c'};
  std::vector<char> p{'a','b','a','a'};

  str T{t};
  str P{p};

  T.print();
  P.print();

  LinkedList<size_t> s;
  
  s = Naive_SM(T, P);

  
  for( LinkedList<size_t>::Iterator it = s.begin(); it != s.end(); ++it )
    std::cout << *it << "\t";
  std::cout << std::endl;
  
  return 0;
}
