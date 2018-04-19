#ifndef __LINKLIST__
#define __LINKLIST__

#include <memory>

template<typename T>
class LinkedList{
  struct Node{
    T elem;
    std::unique_ptr<Node> next;

  Node( const T e ): elem{e}, next{nullptr} {}
  }; // node

  std::unique_ptr<Node> start;
  size_t _size;

 public:

 LinkedList(): _size{0}, start{nullptr} { std::cout << "LL()" << std::endl; }

 LinkedList( const T e ): start{ new Node{e} }, _size{1} {
    std::cout << "LL(const)"<< std::endl;
  }

  ~LinkedList() { }

  void push_back( const T e ){
    Node* pt = start.get();
    std::cout << "LL(const)"<< std::endl;
    if( pt == nullptr ){
    	start.reset( new Node{e} );
    	return;
    }
    	
    while( pt->next != nullptr )
      pt = pt->next.get();
    pt->next.reset( new Node{e} );
    _size++;
  }
  
  size_t size() const { return _size; }

  class Iterator;
  
  Iterator begin(){ return Iterator{start.get()}; }
  Iterator end(){ return Iterator{nullptr}; }
  
}; // linkedlist

template<typename T>
class LinkedList<T>::Iterator{
	using Node = LinkedList<T>::Node;
	Node* current;
	
	public:
		Iterator( Node* pt ): current{pt} {}
		
		T& operator*() const { return current->elem; }
		
		Iterator& operator++(){
			if( current->next != nullptr ){
				current = current->next.get();
			}
			else
				current = nullptr;
			return *this;
		}
		
		bool operator==( const Iterator& other ){
			return this->current == other.current;
		}
		
		bool operator!=( const Iterator& other ){
			return !(*this == other);
		}
	
	
}; // Iterator

#endif // __LINKLIST__
