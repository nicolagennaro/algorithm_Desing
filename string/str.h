#ifndef __STR__
#define __STR__

#include <iterator>

class str{
  char* stringa;
  size_t _size;

public:
  str( LinkedList<char>& ll ){
    _size = ll.size();
    std::cout << "_size " << _size << std::endl;
    stringa = new char[_size];
    size_t i=0;
    for( LinkedList<char>::Iterator it = ll.begin(); it != ll.end(); ++it )
      stringa[i++] = *it;
  }

  // str from container
  template<template <typename, typename> class C>
  str( const C<char, std::allocator<char>>& container ){
    _size = container.size();
    stringa = new char[_size];
    size_t i=0;
    for( typename C<char, std::allocator<char>>::const_iterator it = std::cbegin(container); it != std::cend(container); ++it)
      stringa[ i++ ] = *it;
  }
  
  ~str(){
    delete[] stringa;
  }
  str(const str& s): _size{s._size}{
    stringa = new char[_size];
    for( size_t i=0; i<_size; i++)
      stringa[i] = s.stringa[i];
  }

  str& operator=(const str& s){
    _size = s._size;
    delete[] stringa;
    for( size_t i=0; i<_size; i++)
      stringa[i] = s.stringa[i];
  }

  char& operator[](const size_t& i){
    return stringa[i];
  }

  const size_t size(){ return _size; }
  
  void reverse(){
    char* rev = new char[_size];
    for(size_t i=0; i<_size; i++)
      rev[i] = stringa[ _size - 1 - i ];
    
    delete[] stringa;
    stringa = rev;
  }

  void print(){
    for( size_t i=0; i<_size; i++)
      std::cout << stringa[i] << " ";
    std::cout << std::endl;
  }
};


#endif // __STR__
