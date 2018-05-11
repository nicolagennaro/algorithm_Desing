#include <vector>
#include <iostream>
#include <LinkedList.h>

#define MAX(x,y) (x)>(y) ? x : y


template<typename T>
void print_mat(T* A, int nrow, int ncol){
  int i,j;
  for(i=0; i<ncol; i++){
    for(j=0; j<nrow; j++)
      std::cout << A[ i*nrow + j ] << "\t";
    std::cout << std::endl;
  }
}


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


struct Index{
  size_t r;
  size_t c;
  Index(): r{0}, c{0} {}
  Index(const size_t _r, const size_t _c): r{_r}, c{_c} {}
};

struct Node{
  size_t len;
  struct Index ind;
  Node(): len{0}, ind{} {}
  Node(const size_t _l, const size_t _r, const size_t _c): len{_l}, ind{_r, _c} {}
};


class str LCS(char* X, size_t lX, char* Y, size_t lY){

  size_t* Length = new size_t[ (lY+1)*(lX+1) ];
  int* direction = new int[ (lY+1)*(lX+1) ];
  // -1 = border, 0 = up, 1 = diagonal, 2 = left

  for( size_t i=0; i<lY+1; i++)
    for( size_t j=0; j<lX+1; j++)
      Length[ i*(lY+1) + j ] = 0;


  for( size_t i=0; i<lY+1; i++)
    for( size_t j=0; j<lX+1; j++)
      direction[ i*(lY+1) + j ] = -1;

  
  // Node* matrix = new Node[ lX*lY ];
  for( size_t i=0; i<lY; i++){
    for( size_t j=0; j<lX; j++){
      if( X[j] == Y[i] ){
	Length[ (i+1)*(lY+1) + j+1 ] = Length[ i*(lY+1) + j ] + 1;
	// diagonal
	direction[ (i+1)*(lY+1) + j+1 ] = 1;
      }
      else{
	Length[ (i+1)*(lY+1) + j+1 ] = MAX(Length[ (i)*(lY+1) + j+1 ], Length[ (i+1)*(lY+1) + j ]);

	if( Length[ (i+1)*(lY+1) + j+1 ] == Length[ (i)*(lY+1) + j+1 ] )
	  direction[ (i+1)*(lY+1) + j+1 ] = 0; // up
	else
	  direction[ (i+1)*(lY+1) + j+1 ] = 2; // left
      }
    }
  }

  std::cout << "L" << std::endl;
  print_mat(Length, lY+1, lX+1 );
  std::cout << "D" << std::endl;
  print_mat(direction, lY+1, lX+1 );

  std::cout << "max Length = " << Length[ lY*(lY+1) + lX ] << std::endl;

  size_t pos_x = lX;
  size_t pos_y = lY;

  std::cout << "max Length = " << Length[ pos_y*(lY+1) + pos_x ] << std::endl;


  // -1 = border, 0 = up, 1 = diagonal, 2 = left

  LinkedList<char> stri;
  int dir = direction[ pos_y*(lY+1) + pos_x ];

  while( dir != -1 ){
    if( dir == 0 ){
      // move up
      pos_y--;
    }
    if( dir == 1 ){
      // diagonal
      pos_x--;
      pos_y--;
    }
    if( dir == 2 ){
      // left
      pos_x--;
    }
    dir = direction[ pos_y*(lY+1) + pos_x ];
    std::cout << "dir " << dir << std::endl;
    if( X[pos_x] == Y[pos_y] )
      stri.push_back(X[ pos_x ]);
  }


  std::cout << "str" << std::endl;
  for( LinkedList<char>::Iterator it = stri.begin(); it != stri.end(); ++it )
    std::cout << *it <<  " ";
  std::cout << std::endl;

  

  str r{stri};
  std::cout << "fdsfds" << std::endl;
  r.print();
  r.reverse();
  r.print();
  return r;
}


int main(){

  std::vector<char> x{'c','a','c','a','o'};
  std::vector<char> y{'d','a','c','o','c'};

  char* X = new char[x.size()];
  char* Y = new char[y.size()];

  for(unsigned int i=0; i<x.size(); i++)
    X[i] = x[i];

  for(unsigned int i=0; i<y.size(); i++)
    Y[i] = y[i];

  str sol = LCS(X, x.size(), Y, y.size() );

  std::cout << "main" << std::endl;
  for(size_t i=0; i<sol.size(); i++)
    std::cout << sol[i] << " ";
  std::cout << std::endl;
  
  return 0;
}
