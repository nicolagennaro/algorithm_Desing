#include <iostream>
#include <LinkedList.h>


int main(){

  LinkedList<int> ll;

  std::cout << "eje" << std::endl;
  ll.push_back(3);
  
  ll.push_back(7);


  for( LinkedList<int>::Iterator i = ll.begin(); i != ll.end(); ++i )
    std::cout << *i << " ";
  std::cout << std::endl;
  
  
  std::cout << "new" << std::endl;
  LinkedList<int> l1{4};
  
  LinkedList<int>::Iterator it = l1.begin();

  
  for( ; it!=l1.end(); ++it )
  	std::cout << *it << std::endl;


  LinkedList<int> l2{ll};

  for( LinkedList<int>::Iterator i = l2.begin(); i != l2.end(); ++i )
    std::cout << *i << " ";
  std::cout << std::endl;  


  std::cout << "LL of LL" << std::endl;

  LinkedList<LinkedList<unsigned int>> Graph;

  



  return 0;
}
