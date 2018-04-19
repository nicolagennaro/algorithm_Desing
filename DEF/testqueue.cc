#include <Queue.h>
#include <iostream>


int main(){

  Queue<int> q;
  
  
  for(int i=0; i<10; i++)
    q.push(i);

std::cout << "here" << std::endl;

  while( !q.empty() )
	std::cout << q.pop() << std::endl;

  return 0;
}
