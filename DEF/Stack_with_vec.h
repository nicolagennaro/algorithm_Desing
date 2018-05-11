#ifndef __MYSTACK_W_VEC__
#define __MYSTACK_W_VEC__

#include <iostream>

template<typename T>
class Stack{

  T* S_top;
  size_t max_size;
  size_t curr_size;
  
 public:
  
	// Stack(): _size{0}, S_top{nullptr} { std::cout << "Stack()" << std::endl; }

 	Stack( const size_t max ): max_size{max}, curr_size{0} {
 		std::cout << "Stack( const size_t max )" << std::endl;
    		S_top = new T[max_size];
  	}

  	void push( const T e ){
  		std::cout << "push" << std::endl;
  		if( curr_size + 1 > max_size )
  			throw std::out_of_range("stack limit reached, cannot push");
    		S_top[ curr_size ] = e;
    		curr_size++;
  	}
  	
  	T pop(){
  		if( curr_size == 0 )
  			throw std::runtime_error("stack empty");
  		curr_size--;
  		return S_top[curr_size];
  	}
  	
  	size_t size() const { return curr_size; }
  	size_t max_size() const { return max_size; }
  	
  	bool empty() const {
  		return curr_size==0;
  	}
  
}; // Stack

#endif // __MYSTACK__
