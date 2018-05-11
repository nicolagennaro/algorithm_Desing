#ifndef __MYQUEUE_W_VEC__
#define __MYQUEUE_W_VEC__

#include <iostream>

template<typename T>
class Queue{

  size_t max_size;
  size_t curr_size;
  T* head;
  T* tail;
  
 public:
  
	// Queue(): _size{0}, first{nullptr}, last{nullptr} { std::cout << "Queue()" << std::endl; }

 	Queue( const size_t max ): max_size{max}, curr_size{0} {
 		std::cout << "Queue( const size_t max )" << std::endl;
    		head = new T[max_size];
    		tail = head;
  	}

  	void push( const T e ){
  		std::cout << "push" << std::endl;
		
		
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
  	
  	size_t size() const { return curr_size; }
  	size_t max_size() const { return max_size; }
  	
  	bool empty() const { return curr_size==0; }
  
}; // Stack

#endif // __MYQUEUE__
