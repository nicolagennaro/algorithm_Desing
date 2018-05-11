#include <vector>
#include <iostream>
#include <LinkedList.h>
#include <str.h>

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




class str LCS(str X, str Y){

  size_t lX = X.size();
  size_t lY = Y.size();
  
  size_t* Length = new size_t[ (lY+1)*(lX+1) ];
  int* direction = new int[ (lY+1)*(lX+1) ];
  // -1 = border, 0 = up, 1 = diagonal, 2 = left

  for( size_t i=0; i<lY+1; i++)
    for( size_t j=0; j<lX+1; j++)
      Length[ i*(lY+1) + j ] = 0;


  for( size_t i=0; i<lY+1; i++)
    for( size_t j=0; j<lX+1; j++)
      direction[ i*(lY+1) + j ] = -1;

  
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

  str X{x};
  str Y{y};

  X.print();
  Y.print();

  str sol = LCS(X, Y );

  std::cout << "Longest Common Subsequence" << std::endl;
  sol.print();
  
  return 0;
}
