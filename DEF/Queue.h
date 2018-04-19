#ifndef __MYQUEUE__
#define __MYQUEUE__

// #define MAX_STACK 100

// #include <memory>
#include <iostream>

template<typename T>
class Queue{

  struct Node{
    T elem;
    Node* next;
    
    Node(const T e, Node* pt): elem{e}, next{pt} {}
  }; // Node

  Node* first;
  Node* last;
  size_t _size;
  
 public:
  
	Queue(): _size{0}, first{nullptr}, last{nullptr} { std::cout << "Queue()" << std::endl; }

 	Queue( const T e ): _size{0} {
 		std::cout << "Queue( const T e )" << std::endl;
    		first = new Node{e, nullptr};
    		last = first;
    		_size++;
  	}

  	void push( const T e ){
  		std::cout << "push" << std::endl;
    		Node* nn = new Node{e, nullptr};
    		
    		if( first == nullptr )
    			first = nn; 
    		
    		if( last != nullptr )
    			last->next = nn;
    		last = nn;
    		_size++;
  	}
  	
  	T pop(){
  		if( _size == 0 )
  			throw "queue empty";
  		T ret = first->elem;
  		first = first->next;
  		_size--;
  		return ret;
  	}
  	
  	size_t size() const { return _size; }
  	
  	bool empty() const {
  		return _size==0;
  	}
  
}; // Stack

#endif // __MYQUEUE__
