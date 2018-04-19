#ifndef __MYSTACK__
#define __MYSTACK__

// #define MAX_STACK 100

#include <memory>
#include <iostream>

template<typename T>
class Stack{

  struct Node{
    T elem;
    std::unique_ptr<Node> prev;
    
    Node(const T e, Node* pt): elem{e}, prev{pt} {}
  }; // Node

  std::unique_ptr<Node> S_top;
  size_t _size;
  
 public:
  
	Stack(): _size{0}, S_top{nullptr} { std::cout << "Stack()" << std::endl; }

 	Stack( const T e ): _size{0} {
 		std::cout << "Stack( const T e )" << std::endl;
    		S_top.reset(new Node{e, nullptr});
    		_size++;
  	}

  	void push( const T e ){
  		std::cout << "push" << std::endl;
    		Node* nn = new Node{ e, S_top.get() };
    		S_top.reset(nn);
    		_size++;
  	}
  	
  	T pop(){
  		T ret = S_top->elem;
  		S_top.reset( S_top->prev.get() );
  		_size--;
  		return ret;
  	}
  	
  	size_t size() const { return _size; }
  	
  	bool empty() const {
  		return _size==0;
  	}
  
}; // Stack

#endif // __MYSTACK__
