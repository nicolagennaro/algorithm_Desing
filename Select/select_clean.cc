#include <iostream>
#include <cstdlib>

#define SELECT_SIZE 5

//
// Partition
// small class returned by select_partition
//

struct Partition{
  int k1;
  int k2;
  Partition(int n1, int n2): k1{n1}, k2{n2} {}
  Partition(): k1{1}, k2{2} {}
  friend std::ostream& operator<<(std::ostream& os, const Partition p){
    os << p.k1 << " " << p.k2;
    return os;
  }
}; 



//
// Function definitions
//

template<typename T>
void Insertion_Sort(T* A, int begin, int end);

template<typename T>
T Select_Pivot(T* A, int begin, int end);

template<typename T>
Partition Select_Partition(T* A, int begin, int end, T pivot);

template<typename T>
T Select(T* A, int j, int begin, int end);



//
// Main
//

int main(int argc, char* argv[]){
  
  int *A;
  int size, index;

  if( argc < 3 ){
    std::cout << "USAGE: " << argv[0] << "vec_size index" << std::endl;
    exit(1);
  }
  
  size = atoi(argv[1]);
  index = atoi(argv[2]);
    
  if(index > size){
    std::cout << "index > vec_size" << std::endl;
    exit(1);
  }
  
  A = new int[size];

  srand(time(NULL));
  int i;
  for(i=0; i<size; i++)
    A[i] = rand() % (size*2);
  
  Partition p;


  // index starting from 1
  int res = Select(A-1, index, 1, size);

  // index starting from 1
  Insertion_Sort(A-1, 1, size);

 std::cout << res << "\t" << A[index-1] << std::endl;

 delete[] A;
 
  return 0;
}




//
// INSERTION SORT
//

template<typename T>
void Insertion_Sort(T* A, int begin, int end){
  int i, j;
  T k;
  
  
  for( j=begin+1; j<=end; j++ ){
    k = A[j];
    i = j-1;
    while( i>begin-1 && A[i]>k ){
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = k;
  }

}





//
// SELECT PIVOT
//


template<typename T>
T Select_Pivot(T* A, int begin, int end){
  int blocks_num;
  T pivot;   
  if( (end-begin+1) % 5 == 0 )
    blocks_num = (end-begin+1)/5;
  else
    blocks_num = (end-begin+1)/5 + 1;
  
  T* Medians = new T[blocks_num];

  for( int i=0; i<blocks_num; i++ ){
    int cbegin = begin + 5*i;
    if( cbegin+4 > end ){
      Insertion_Sort(A, cbegin, end);
      Medians[i] = A[ cbegin + (end-cbegin)/2 ];
    }
    else{
      Insertion_Sort(A, cbegin, cbegin+4);
      Medians[i] = A[ cbegin + 2 ];
    }
  }


  
  pivot = Select(Medians-1, (blocks_num + 1) / 2, 1, blocks_num );
      
  return pivot;
}




//
// SELECT PARTITION
// returns a class partition containing two integers
//


template<typename T>
Partition Select_Partition(T* A, int begin, int end, T pivot){
  
  T k = pivot;

    Partition p{begin-1,end};
    T temp_k;
    int j;

    
    for(j=0; j<end-begin+1; j++){
      if( A[ begin + j ] < k ){
	p.k1++;
	temp_k = A[ p.k1 ];
	A[ p.k1 ] = A[ begin + j ];
	A[ begin + j ] = temp_k;
      }
    } // for


    p.k1++;
    p.k2 = p.k1;

    while( A[p.k2] == k )
      p.k2++;
    
    for( j=end; j>=p.k1 && j>p.k2; j--){
	if( A[j] == k ){
	  temp_k = A[j];
	  A[j] = A[p.k2];
	  A[p.k2] = temp_k;
	  while( A[p.k2] == k )
	    p.k2++;
	}
      }
    p.k2--;
  

    return p;
}


// 
// SELECT
//


template<typename T>
T Select(T* A, int j, int begin, int end){
  
  if( end - begin + 1 < SELECT_SIZE){
    Insertion_Sort(A, begin, end);
    return A[j];
  }


  T pivot;
  pivot = Select_Pivot(A, begin, end);
  
    Partition p;
    p = Select_Partition(A, begin, end, pivot);

  
  if( j < p.k1 ){
    return Select(A, j, begin, p.k1-1);
  }
  if( j > p.k2 ){
    return Select(A, j, p.k2+1, end);
  }

  return A[j];
}

