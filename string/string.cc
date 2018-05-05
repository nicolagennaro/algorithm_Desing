#include <iostream>
#include <vector>
#include <LinkedList.h>


class LinkedList<size_t> Naive_SM( char* T, char* P, size_t lT, size_t lP){

  if( lT < lP )
    throw "invalid strings";
  
  LinkedList<size_t> shifts;
  size_t i;
  
  for( size_t s = 0; s<(lT - lP); s++ ){
    i = 1;
    while( i<lP && P[i]==T[s+i] )
      i++;
    if( i>=lP ){
      shifts.push_back(s);
    }
  }

  
  for( LinkedList<size_t>::Iterator it = shifts.begin(); it != shifts.end(); ++it )
    std::cout << *it << "\t";
  std::cout << std::endl;
  
  return shifts;
}


int main(){
  LinkedList<size_t> s;


  std::vector<char> t{'a','b','c','a','b','a','a','b','c','a','b','a','c'};
  std::vector<char> p{'a','b','a','a'};

  char* T = new char[t.size()];
  char* P = new char[p.size()];

  for( unsigned int i=0; i<t.size(); i++ )
    T[i] = t[i];

  for( unsigned int i=0; i<p.size(); i++ )
    P[i] = p[i];

  s = Naive_SM(T-1, P-1, t.size(), p.size() );

  
  for( LinkedList<size_t>::Iterator it = s.begin(); it != s.end(); ++it )
    std::cout << *it << "\t";
  std::cout << std::endl;
  
  return 0;
}
