#include <Stack.h>
#include <iostream>

int main(){


std::cout << "here" << std::endl;


Stack<int> s{};

std::cout << "here" << std::endl;

for( int i=0; i<2; i++)
	s.push(i);

std::cout << "here";

while( !s.empty() )
	std::cout << s.pop() << std::endl;
	

return 0;
}
