#ifndef __MYSTACK__
#define __MYSTACK__

// #define MAX_STACK 100

#include <memory>
#include <iostream>

template<typename T>
class Stack{

  struct Node{
    T elem;
    Node* prev;
    
    Node(const T e, Node* pt): elem{e}, prev{pt} {}
  }; // Node

  Node* S_top;
  size_t _size;
  
 public:
  
	Stack(): _size{0}, S_top{nullptr} { std::cout << "Stack()" << std::endl; }

 	Stack( const T e ): _size{0} {
 		std::cout << "Stack( const T e )" << std::endl;
    		S_top = new Node{e, nullptr};
    		_size++;
  	}

  	void push( const T e ){
  		std::cout << "push" << std::endl;
    		Node* nn = new Node{e, S_top};
    		S_top = nn;
    		_size++;
  	}
  	
  	T pop(){
  		if( _size == 0 )
  			throw "stack empty";
  		Node* pt = S_top;
  		T ret = S_top->elem;
  		S_top = S_top->prev;
  		delete pt;
  		_size--;
  		return ret;
  	}
  	
  	size_t size() const { return _size; }
  	
  	bool empty() const {
  		return _size==0;
  	}
  
}; // Stack

#endif // __MYSTACK__
