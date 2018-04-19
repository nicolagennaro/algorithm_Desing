#include <iostream>
#include <LinkedList.h>


int main(){

  LinkedList<int> ll;

  std::cout << "eje" << std::endl;
  ll.push_back(3);
  
  ll.push_back(7);
  
  std::cout << "new" << std::endl;
  LinkedList<int> l1{4};
  
  LinkedList<int>::Iterator it = ll.begin();

  
  for( ; it!=ll.end(); ++it )
  	std::cout << *it << std::endl;

  return 0;
}
