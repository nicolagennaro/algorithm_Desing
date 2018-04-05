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


int next_pow_two(int n){
	int r=1;
	while( r<n )
		r *=2;
	return r;
}


template<typename T>
T* resize_matrix(T* mat, int size, int new_size){

	if( size == new_size )
		return mat;

	T* new_mat = new T[ new_size*new_size ];

	for( int i=0; i<new_size; i++){
		if( i<size ){
		for( int j=0; j<new_size; j++){
			if( j<size )
				new_mat[ i*new_size + j ] = mat[ i*size + j ];
			else
				new_mat[ i*new_size + j ] = 0.0;	
		}
		}
		else{
			for( int j=0; j<new_size; j++)
				new_mat[ i*new_size + j ] = 0.0; 
		}
	}

	return new_mat;
}


template<typename T>
void Strassen_real(T*, T*, T*, int);


template<typename T>
void Strassen(T* A, T* B, T* C, int size_in){
	if( next_pow_two( size_in ) == size_in ){
		Strassen_real(A, B, C, size_in);
		return;
	}
	
	// define three new pointers
	int new_size = next_pow_two(size_in);
	T  *A_resized, *B_resized, *C_resized;

	A_resized = resize_matrix( A, size_in, new_size );
	B_resized = resize_matrix( B, size_in, new_size );
	C_resized = resize_matrix( C, size_in, new_size );
	
	Strassen_real(A_resized, B_resized, C_resized, new_size);
	
	delete[] A_resized;
	delete[] B_resized;
	
	for( int i=0; i<size_in; i++ )
		for( int j=0; j<size_in; j++ )
			C[ i*size_in + j ] = C_resized[ i*new_size + j ];
			
	delete[] C_resized;
}








template<typename T>
void Strassen_real(T* A, T* B, T* C, int size_in){

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
  }

     int i, j;
     int h_size = size_in/2;


  // make sure the entries of C are all zeros since we need to sum them 
  for(i=0; i<size_in; i++){
    for(j=0; j<size_in; j++){
    	C[ i*size_in + j ] = 0.0;
     }
    }

   
   
   
   
     // the only matrices needed
     T *S1, *S2, *P;
     
     S1 = new T[h_size*h_size];
     S2 = new T[h_size*h_size];
     P  = new T[h_size*h_size];


  ///////////////////////////////////////////////////

  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ i*size_in + j ]; //  A11
      S2[ i*h_size + j ] = B[ i*size_in + j + h_size ] - B[ (i+h_size)*size_in + j + h_size ]; //  S1 = B12 - B22
     }
  }
     
     Strassen(S1, S2, P, h_size);   // P1
     
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      C[ i*size_in + j + h_size ] += P[ i*h_size + j ];           // C12 = P1 + P2
      C[ (i+h_size)*size_in + j + h_size ] += P[ i*h_size + j ];  // C22 = P5 + P1 - P3 - P7
     }
  }  
     
     ////////////////////////////////////////////////
     
     
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ i*size_in + j ] + A[ i*size_in + j + h_size ]; // S2 = A11 + A12
      S2[ i*h_size + j ] = B[ (i+h_size)*size_in + j + h_size ]; // B22
     }
  }
     
     
      Strassen(S1, S2, P, h_size);  // P2
     
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){     
     C[ i*size_in + j ] -= P[i*h_size + j];                     // C11 = P4 + P5 + P6 - P2
     C[ i*size_in + j + h_size ] += P[ i*h_size + j ];           // C12 = P1 + P2
      }
  }    
     
     
     /////////////////////////////////////////////////
   
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ (i+h_size)*size_in + j ] + A[ (i+h_size)*size_in + j + h_size ]; // S3 = A21 + A22
      S2[ i*h_size + j ] = B[ i*size_in + j ]; // B11
     }
  }  
     
      Strassen(S1, S2, P, h_size);  // P3 = S3 * B11
     
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      C[ (i+h_size)*size_in + j] += P[i*h_size + j];              // C21 = P3 + P4
      C[ (i+h_size)*size_in + j + h_size ] -= P[ i*h_size + j ];  // C22 = P5 + P1 - P3 - P7
     }
  }  
  
  
  
  ////////////////////////////////////////////////////
  
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ (i+h_size)*size_in + j + h_size ]; // A22
      S2[ i*h_size + j ] = B[ (i+h_size)*size_in + j ] - B[ i*size_in + j ]; // S4 = B21 - B11
     }
  } 
  
  
  
   Strassen(S1, S2, P, h_size);  // P4 = A22 * S4
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      C[ (i+h_size)*size_in + j] += P[i*h_size + j];              // C21 = P3 + P4
      C[ i*size_in + j ] += P[i*h_size + j];                      // C11 = P4 + P5 + P6 - P2
     }
  }  
  
  
  ///////////////////////////////////////////////////
  
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ i*size_in + j ] + A[ (i+h_size)*size_in + j + h_size ]; // S5 = A11 + A22
      S2[ i*h_size + j ] = B[ i*size_in + j ] + B[ (i+h_size)*size_in + j + h_size ]; // S6 = B11 + B22
     }
  }   
  
  
   Strassen(S1, S2, P, h_size);  // P5 = S5 * S6
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      C[ (i+h_size)*size_in + j + h_size ] += P[ i*h_size + j ];  // C22 = P5 + P1 - P3 - P7
      C[ i*size_in + j ] += P[i*h_size + j];                      // C11 = P4 + P5 + P6 - P2
     }
  }    
  
  
  ////////////////////////////////////////////////////////
  
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ i*size_in + j + h_size ] - A[ (i+h_size)*size_in + j + h_size ]; // S7 = A12 - A22
      S2[ i*h_size + j ] = B[ i*size_in + j + h_size ] + B[ (i+h_size)*size_in + j + h_size ]; // S* = B12 + B22
     }
  }   

  
   Strassen(S1, S2, P, h_size);  // P6 = S7 * S8
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      C[ i*size_in + j ] += P[i*h_size + j];                      // C11 = P4 + P5 + P6 - P2
     }
  }    
  
  
  ///////////////////////////////////////////////////////
  
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){
      S1[ i*h_size + j ] = A[ i*size_in + j ] - A[ (i+h_size)*size_in + j ]; // S9 = A11 - A21
      S2[ i*h_size + j ] = B[ i*size_in + j ] + B[ i*size_in + j + h_size ]; // S10 = B11 + B12
     }
  }     
  
   Strassen(S1, S2, P, h_size); // P7 = S9 * S10
  
  
  for(i=0; i<h_size; i++){
    for(j=0; j<h_size; j++){  
  	C[ (i+h_size)*size_in + j + h_size ] -= P[ i*h_size + j ];  // C22 = P5 + P1 - P3 - P7
    }
  }
  
  

     delete[] S1;
     delete[] S2;
     delete[] P;

return;
     
} // strassen



double rand_d(double a, double b){
  return a + (b-a)*double( rand() )/ double(RAND_MAX);
}



int main(int argc, char* argv[]){
  int size;

  if( argc < 2 ){
    std::cout << "USAGE: " << argv[0] << "matrix_size" << std::endl;
    exit(1);
  }

  int i, j;
  size = atoi(argv[1]);
  

  	
  
  std::cout << "Allocated size: " << size << std::endl;


  double *A, *B, *C, *CC;

  A = new double[size*size];
  B = new double[size*size];
  C = new double[size*size];
  CC = new double[size*size];


int n = next_pow_two(size);
std::cout << n << std::endl;


  for(i = 0; i<size; i++){
         for(j=0; j<size; j++){
  	  A[i*size + j] = rand_d(0,1);
  	  B[i*size + j] = rand_d(0,1);
        C[i*size + j] = 0.0;
        CC[i*size + j] = 0.0;
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

      compare(C,CC,size);



       delete[] A;
       delete[] B;
       delete[] C;
       delete[] CC;

      return 0;
}
