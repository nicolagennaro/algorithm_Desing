#ifndef __STRASSEN__
#define __STRASSEN__

#include <iostream>
#include <cstdlib>

#define MIN_MAT 2


template<typename T>
void print_mat(T* A, int size){
  int i,j;
  for(i=0; i<size; i++){
    for(j=0; j<size; j++)
      std::cout << A[ i*size + j ] << "\t";
    std::cout << std::endl;
  }
}




template<typename T>
void naive_mat_mult(T* A, T* B, T* C, int size){
  int i,j,k;
  for( i=0; i<size; i++){
    for( j=0; j<size; j++){
      C[i*size + j] = 0.0;
      for( k=0; k<size; k++)
	C[i*size + j] += A[ i*size + k ]*B[ k*size + j ];
    }
  }
}



template<typename T>
void compare(T* A, T* B, int size){
  int i,j;
  
  for( i=0; i<size; i++)
    for( j=0; j<size; j++)
      if( double(A[i*size + j] - B[i*size + j])*(A[i*size + j] - B[i*size + j]) > 0.0001 )
	std::cout << "diff: " << i << "\t" << j << std::endl;

}


template<typename T>
void Strassen(T* A, T* B, T* C, int size_in){

  
    #ifdef DEBUG_C
     std::cout << "###################################### size_in" << size_in << std::endl;
    #endif
  int size;
  if(size_in <= MIN_MAT){
    #ifdef DEBUG_C
     std::cout << "Strassen: size_in = " << size_in << std::endl;
     std::cout << "calling naive" << std::endl;
     print_mat(A, size_in);
     print_mat(B, size_in);
    #endif
    naive_mat_mult(A, B, C, size_in);
    #ifdef DEBUG_C
    std::cout << "Returning..." << std::endl;
    #endif
    return;
    //    std::cout << "after...." << std::endl;
  }
  else if( size_in % 2 == 1){
  #ifdef DEBUG
    std::cout << "Strassen: size_in = " << size_in << "is ODD" << std::endl;
  #endif

    size = size_in + 1;

  #ifdef DEBUG
    std::cout << "size changed to " << size << std::endl;
  #endif
  }
  else{
    size = size_in;

  #ifdef DEBUG
    std::cout << "Strassen: size = " << size << std::endl;
  #endif
    }


     int i, j;
     int h_size = size/2;

     #ifdef DEBUG
     std::cout << "size_in/2 = " << size_in/2 << std::endl;
     #endif
     
     T *A11, *A12, *A21, *A22, *B11, *B12, *B21, *B22;
     A11 = new T[h_size*h_size];
     A12 = new T[h_size*h_size];
     A21 = new T[h_size*h_size];
     A22 = new T[h_size*h_size];
     B11 = new T[h_size*h_size];
     B12 = new T[h_size*h_size];
     B21 = new T[h_size*h_size];
     B22 = new T[h_size*h_size];

     // fill this matrices, adding zeros if size_in is ODD

     // fill 11
     
      for(i=0; i<h_size; i++){
	for(j=0; j<h_size; j++){
	  A11[ i*h_size +j ] = A[ i*size_in + j ];
	  B11[ i*h_size +j ] = B[ i*size_in + j ];
	}
      }

      // fill 12

      for(i=0; i<h_size; i++){
	for(j=0; j<h_size; j++){
	  if( j<=size_in/2-1){
	    A12[ i*h_size + j ] = A[ i*size_in + j + h_size ];
	    B12[ i*h_size + j ] = B[ i*size_in + j + h_size ];
	  }
	  else{
	    A12[ i*h_size + j ] = 0.0;
	    B12[ i*h_size + j ] = 0.0;
	  }
	}
      }

      // fill 21
      
      for(i=0; i<h_size; i++){
	for(j=0; j<h_size; j++){
	  if(i<=size_in/2-1){
	    A21[ i*h_size + j ] = A[ (i+h_size)*size_in + j];
	    B21[ i*h_size + j ] = B[ (i+h_size)*size_in + j];
	  }
	  else{
	    A21[ i*h_size + j ] = 0.0;
	    B21[ i*h_size + j ] = 0.0;
	  }
	}
      }

      // fill 22
      for(i=0; i<h_size; i++){
	if( i<=size_in/2-1){
	  for(j=0; j<h_size; j++){
	    if( j<=size_in/2-1){
	    A22[ i*h_size + j ] = A[ (i+h_size)*size_in + j + h_size ];
	    B22[ i*h_size + j ] = B[ (i+h_size)*size_in + j + h_size ];
	    }
	    else{
	    A22[ i*h_size + j ] = 0.0;
	    B22[ i*h_size + j ] = 0.0;
	    }
	  }
	}
	else{
	for(j=0; j<h_size; j++){
	    A22[ i*h_size + j ] = 0.0;
	    B22[ i*h_size + j ] = 0.0;
	  }
	}
      }
	

#ifdef DEBUG_FILL
  std::cout << "A11" << std::endl;
  print_mat(A11, h_size);
  std::cout << "B11" << std::endl;
  print_mat(B11, h_size);

  std::cout << "A12" << std::endl;
  print_mat(A12, h_size);
  std::cout << "B12" << std::endl;
  print_mat(B12, h_size);
  
  std::cout << "A21" << std::endl;
  print_mat(A21, h_size);
  std::cout << "B21" << std::endl;
  print_mat(B21, h_size);
  
  std::cout << "A22" << std::endl;
  print_mat(A22, h_size);
  std::cout << "B22" << std::endl;
  print_mat(B22, h_size);
#endif


     // S matrices
     T *S1, *S2, *S3, *S4, *S5, *S6, *S7, *S8, *S9, *S10;
     S1 = new T[h_size*h_size];
     S2 = new T[h_size*h_size];
     S3 = new T[h_size*h_size];
     S4 = new T[h_size*h_size];
     S5 = new T[h_size*h_size];
     S6 = new T[h_size*h_size];
     S7 = new T[h_size*h_size];
     S8 = new T[h_size*h_size];
     S9 = new T[h_size*h_size];
     S10 = new T[h_size*h_size];
     
     
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = B12[ i*h_size + j ] - B22[ i*h_size + j ]; // B12 - B22
      S2[ i*h_size + j ] = A11[ i*h_size + j ] + A12[ i*h_size + j ]; // A11 + A12
      S3[ i*h_size + j ] = A21[ i*h_size + j ] + A22[ i*h_size + j ]; // A21 + A22
      S4[ i*h_size + j ] = B21[ i*h_size + j ] - B11[ i*h_size + j ]; // B21 - B11
      S5[ i*h_size + j ] = A11[ i*h_size + j ] + A22[ i*h_size + j ]; // A11 + A22
      S6[ i*h_size + j ] = B11[ i*h_size + j ] + B22[ i*h_size + j ]; // B11 + B22
      S7[ i*h_size + j ] = A12[ i*h_size + j ] - A22[ i*h_size + j ]; // A12 - A22
      S8[ i*h_size + j ] = B21[ i*h_size + j ] + B22[ i*h_size + j ]; // B21 + B22
      S9[ i*h_size + j ] = A11[ i*h_size + j ] - A21[ i*h_size + j ]; // A11 - A21
      S10[ i*h_size + j ] = B11[ i*h_size + j ] + B12[ i*h_size + j ]; // B11 + B12 
    }
  }

  // free A12, A21, B12, B21
  delete[] A12;
  delete[] A21;
  delete[] B12;
  delete[] B21;
  
  #ifdef DEBUG_S
  std::cout << "S1 = B12 - B22:" << std::endl;
  print_mat(S1, h_size);
  std::cout << "S2 = A11 + A12" << std::endl;
 print_mat(S2, h_size);
   std::cout << "S3 = A21 + A22" << std::endl;
 print_mat(S3, h_size);
  std::cout << "S4 = B21 - B11:" << std::endl;
  print_mat(S4, h_size);
  std::cout << "S5 = A11 + A22" << std::endl;
 print_mat(S5, h_size);
   std::cout << "S6 = B11 + B22" << std::endl;
 print_mat(S6, h_size);
  std::cout << "S7 = A12 - A22:" << std::endl;
  print_mat(S7, h_size);
  std::cout << "S8 = B21 + B22" << std::endl;
 print_mat(S8, h_size);
   std::cout << "S9 = A11 - A21" << std::endl;
 print_mat(S9, h_size);
  std::cout << "S10 = B11 + B12:" << std::endl;
  print_mat(S10, h_size);
#endif



  T *P1, *P2, *P3, *P4, *P5, *P6, *P7;
  P1 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P1[i*h_size + j] = 0;

 Strassen(A11, S1, P1, h_size);
 
 delete[] A11;
 delete[] S1;
 P2 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P2[i*h_size + j] = 0;

 
 Strassen(S2, B22, P2, h_size);
 
 delete[] S2;
 delete[] B22;
 P3 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P3[i*h_size + j] = 0;

 
 Strassen(S3, B11, P3, h_size);

 delete[] S3;
 delete[] B11;
 P4 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P4[i*h_size + j] = 0;

 
 Strassen(A22, S4, P4, h_size);

 delete[] A22;
 delete[] S4;
 P5 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P5[i*h_size + j] = 0;

 
 Strassen(S5, S6, P5, h_size);

 delete[] S5;
 delete[] S6;
 P6 = new T[h_size*h_size];

   for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P6[i*h_size + j] = 0;

 Strassen(S7, S8, P6, h_size);

 delete[] S7;
 delete[] S8;
 P7 = new T[h_size*h_size];

  for(i=0; i<h_size; i++)
    for(j=0; j<h_size; j++)
      P7[i*h_size + j] = 0;

 
 Strassen(S9, S10, P7, h_size);

 delete[] S9;
 delete[] S10;

 
  #ifdef DEBUG_P
  std::cout << "P1:" << std::endl;
  print_mat(P1, h_size);
  std::cout << "P2:" << std::endl;
  print_mat(P2, h_size);
  std::cout << "P3:" << std::endl;
  print_mat(P3, h_size);
  std::cout << "P4:" << std::endl;
  print_mat(P4, h_size);
  std::cout << "P5:" << std::endl;
  print_mat(P5, h_size);
  std::cout << "P6:" << std::endl;
  print_mat(P6, h_size);
  std::cout << "P7:" << std::endl;
  print_mat(P7, h_size);
#endif


  // filling C11  
 for(i=0; i<h_size; i++)
   for(j=0; j<h_size; j++)
     C[ i*size_in + j ] = P5[i*h_size + j] + P4[i*h_size + j] - P2[i*h_size + j] + P6[i*h_size + j];// C11


#ifdef DEBUG_C
     std::cout << "C" << std::endl;
     print_mat(C, size_in);
#endif

 
 // filling C12
 if( h_size*2 == size_in )
   for(i=0; i<h_size; i++)
     for(j=0; j<h_size; j++)
       C[ i*size_in + j + h_size ] = P1[i*h_size + j] + P2[i*h_size + j]; // C12
 else
   for(i=0; i<h_size; i++){
     for(j=0; j<h_size-1; j++){
       C[ i*size_in + j + h_size ] = P1[i*h_size + j] + P2[i*h_size + j]; // C12
#ifdef DEBUG
       std::cout << "#" << C[ i*size_in + j + h_size ] << "\t";
#endif
     }
#ifdef DEBUG
     std::cout << std::endl;
#endif
   }

#ifdef DEBUG_C
     std::cout << "C" << std::endl;
     print_mat(C, size_in);
#endif



 // filling C21
 if( h_size*2 == size_in )
 for(i=0; i<h_size; i++)
   for(j=0; j<h_size; j++)
     C[ (i+h_size)*size_in + j] = P3[i*h_size + j] + P4[i*h_size + j]; // C21
 else
 for(i=0; i<h_size-1; i++)
   for(j=0; j<h_size; j++)
     C[ (i+h_size)*size_in + j] = P3[i*h_size + j] + P4[i*h_size + j]; // C21


#ifdef DEBUG_C
     std::cout << "C" << std::endl;
     print_mat(C, size_in);
#endif


 
 // filling C22
 if( h_size*2 == size_in )
 for(i=0; i<h_size; i++)
   for(j=0; j<h_size; j++)
     C[ (i+h_size)*size_in + j + h_size ] = P5[i*h_size + j] + P1[i*h_size + j] - P3[i*h_size + j] - P7[i*h_size + j];// C22
else
 for(i=0; i<h_size-1; i++)
   for(j=0; j<h_size-1; j++)
     C[ (i+h_size)*size_in + j + h_size ] = P5[i*h_size + j] + P1[i*h_size + j] - P3[i*h_size + j] - P7[i*h_size + j];// C22 

#ifdef DEBUG_C
     std::cout << "C" << std::endl;
     print_mat(C, size_in);
#endif


     delete[] P1;
     delete[] P2;
     delete[] P3;
     delete[] P4;
     delete[] P5;
     delete[] P6;
     delete[] P7;
     
} // strassen


#endif // __STRASSEN__
