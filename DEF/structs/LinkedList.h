#ifndef __LINKLIST__
#define __LINKLIST__

#include <memory>

template<typename T>
class LinkedList{

 protected:
 
  struct Node{
    T elem;
    std::unique_ptr<Node> next;

  Node( const T e ): elem{e}, next{nullptr} {}
  }; // node


  std::unique_ptr<Node> start;
  Node* _end;
  size_t _size;

 public:

 LinkedList(): start{nullptr}, _end{nullptr}, _size{0} {}

 LinkedList( const T e ): start{ new Node{e} }, _size{1} {
 	_end = start.get();
 }

 ~LinkedList() { }


 LinkedList(const LinkedList& ll){
    LinkedList<T>::ConstIterator it = ll.cbegin();
    for( ; it != ll.cend(); ++it)
      this->push_back( *it );
  }

  LinkedList& operator=(const LinkedList& ll){
    _size = ll._size;
    for( LinkedList<T>::ConstIterator it=ll.cbegin(); it != ll.cend(); ++it )
      this->push_back( *it );
    return *this;
  }
  
  void push_back( const T e ){
    if( _end == nullptr ){
    	start.reset( new Node{e} );
    	_end = start.get();
    	return;
    }
    
    _end->next.reset( new Node{e} );
    _end = _end->next.get();
    _size++;
  }
  
  size_t size() const { return _size; }

  class Iterator;
  class ConstIterator;
  
  Iterator begin() const { return Iterator{start.get()}; }
  Iterator end() const { return Iterator{nullptr}; }

  ConstIterator cbegin() const { return ConstIterator{start.get()}; }
  ConstIterator cend() const { return ConstIterator{nullptr}; }
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


template<typename T>
class LinkedList<T>::ConstIterator: public LinkedList<T>::Iterator{

  using parent = LinkedList<T>::Iterator;
  
 public:
  using parent::Iterator;
  const T& operator*() const { return parent::operator*(); }

};


#endif // __LINKLIST__
