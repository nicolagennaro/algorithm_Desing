#include <iostream>
#include <cstdlib>



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
      C[i*size + j] = 0;
      for( k=0; k<size; k++)
	C[i*size + j] += A[ i*size + k ]*B[ k*size + j ];
    }
  }
}


template<typename T>
void Strassen(T* A, T* B, T* C, int size_in){

  
    #ifdef DEBUG
     std::cout << "###################################################" << size_in << std::endl;
    #endif
  int size;
  if(size_in == 1){
    #ifdef DEBUG
     std::cout << "Strassen: size_in = " << size_in << std::endl;
    #endif
    C[0] = A[0]*B[0];
    #ifdef DEBUG
    std::cout << "Returning..." << std::endl;
    #endif
    return;
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
	    A12[ i*h_size + j ] = 0;
	    B12[ i*h_size + j ] = 0;
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
	for(j=0; j<h_size; j++){
	  if(i<=size_in/2-1 || j<=size_in/2-1){
	    A22[ i*h_size + j ] = A[ (i+h_size)*size_in + j + h_size ];
	    B22[ i*h_size + j ] = B[ (i+h_size)*size_in + j + h_size ];
	  }
	  else{
	    A22[ i*h_size + j ] = 0.0;
	    B22[ i*h_size + j ] = 0.0;
	  }
	}
      }


#ifdef DEBUG1
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
  
  #ifdef DEBUG1
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


 Strassen(A11, S1, P1, h_size);
 
 delete[] A11;
 delete[] S1;
 P2 = new T[h_size*h_size];

 Strassen(S2, B22, P2, h_size);
 
 delete[] S2;
 delete[] B22;
 P3 = new T[h_size*h_size];

 Strassen(S3, B11, P3, h_size);

 delete[] S3;
 delete[] B11;
 P4 = new T[h_size*h_size];

 Strassen(A22, S4, P4, h_size);
 
 delete[] S4;
 delete[] A22;
 P5 = new T[h_size*h_size];

 Strassen(S5, S6, P5, h_size);

 delete[] S5;
 delete[] S6;
 P6 = new T[h_size*h_size];

 Strassen(S7, S8, P6, h_size);

 delete[] S7;
 delete[] S8;
 P7 = new T[h_size*h_size];

 Strassen(S9, S10, P7 ,h_size);

 delete[] S9;
 delete[] S10;

 
  #ifdef DEBUG
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
 

 for(i=0; i<h_size; i++){
   for(j=0; j<h_size; j++){
     C[ i*size_in + j ] = P5[i*h_size + j] + P4[i*h_size + j] - P2[i*h_size + j] + P6[i*h_size + j];// C11

     if( j + h_size < size_in )
       C[ i*size_in + j + h_size ] = P1[i*h_size + j] + P2[i*h_size + j]; // C12

     if( i + h_size < size_in )
       C[ (i+h_size)*size_in + j] = P3[i*h_size + j] + P4[i*h_size + j]; // C21

     if( i + h_size < size_in && j + h_size < size_in )
       C[ (i+h_size)*size_in + j + h_size ] = P5[i*h_size + j] + P1[i*h_size + j] - P3[i*h_size + j] - P7[i*h_size + j];// C22
   }
 }

     delete[] P1;
     delete[] P2;
     delete[] P3;
     delete[] P4;
     delete[] P5;
     delete[] P6;
     delete[] P7;

} // strassen


int main(int argc, char* argv[]){
  int size;
  int *A, *B, *C, *CC;

  if( argc < 2 ){
    std::cout << "USAGE: " << argv[0] << "matrix_size" << std::endl;
    exit(1);
  }

  size = atoi(argv[1]);
  
  std::cout << "Allocated size: " << size << std::endl;
  
    A = new int[size*size];
    B = new int[size*size];
    C = new int[size*size];
    CC = new int[size*size];

    if( A==NULL || B==NULL || C==NULL){
      std::cout << "cannot alloc memory" << std::endl;
      exit(1);
    }

    
    #ifdef DEBUG
      std::cout  << "Randomly allocating the matrices" << std::endl;
    #endif

      int i, j;

      for(i = 0; i<size; i++){
        for(j=0; j<size; j++){
	  A[i*size + j] = rand() %(3*size);
	  B[i*size + j] = rand() %(3*size);
       	    C[i*size + j] = 0;
       	    CC[i*size + j] = 0;
	}
      }

      std::cout << "Matrix A\n" << std::endl;
      print_mat(A, size);

      std::cout << "Matrix B\n" << std::endl;
      print_mat(B, size);
      
      Strassen(A,B,C,size);

      std::cout << "\nResult of Strassen\n" << std::endl;
      print_mat(C, size);

      naive_mat_mult(A,B,CC,size);

      std::cout << "\nResult of naive_mat_mult\n" << std::endl;

      print_mat(CC,size);

      
      delete[] A;
      delete[] B;
      delete[] C;
      delete[] CC;


 /*     double *D1, *D2, *DS, *DD;
      D1 = new double[size*size];
      D2 = new double[size*size];
      DS = new double[size*size];
      DD = new double[size*size];

      for(i = 0; i<size; i++){
        for(j=0; j<size; j++){
	  D1[i*size + j] = double(rand())/RAND_MAX;
	  D2[i*size + j] = double(rand())/RAND_MAX;
       	  DS[i*size + j] = 0.0;
       	  DD[i*size + j] = 0.0;
	}
      }

      std::cout << "D1" << std::endl; 
      print_mat(D1,size);

      Strassen(D1,D2,DS,size);

      std::cout << "\nResult of Strassen\n" << std::endl;
      print_mat(DS, size);

      naive_mat_mult(D1,D2,DD,size);

      std::cout << "\nResult of naive_mat_mult\n" << std::endl;

      print_mat(DD,size);
*/

      
      return 0;
}
