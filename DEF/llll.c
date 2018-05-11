#include <LinkedList.h>
#include <iostream>


int main(){

  LinkedList<LinkedList<unsigned int>> ll;

  for( int i=0; i<3; i++){
    LinkedList<unsigned int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    ll.push_back(l1);
  }

  std::cout << "LL" << std::endl;
  for( LinkedList<LinkedList<unsigned int>>::Iterator it = ll.begin(); it != ll.end(); ++it ){


  }
  
  return 0;
}
