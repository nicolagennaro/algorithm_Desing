#include <iostream>
#include <cstdlib>

#define SELECT_SIZE 5
#define MAX_PRINT   50


//
// Partition
//

struct Partition{
  int k1;
  int k2;
  Partition(int n1, int n2): k1{n1}, k2{n2} {}
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





// void sel_part_test(int size=10, int times=100){
//   //Partition p;
//   int *A = new int[size];

  

// }


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
  
#ifdef DEBUG
  std::cout << "Main: array size" << size <<std::endl;
  std::cout << "Main: index " << index << std::endl;
#endif
  
  if(index > size){
    std::cout << "index > vec_size" << std::endl;
    exit(1);
  }
  
  A = new int[size];

  srand(time(NULL));
  int i;
  for(i=0; i<size; i++)
    A[i] = rand() % (size*2);


#ifdef DEBUG
  for(i=0; i<size && i<=20; i++)
    std::cout << A[i] << " ";

  std::cout << std::endl;
#endif
  Partition p{2,3};


  // index starting from 1
  int res = Select(A-1, index, 1, size);

  #ifdef DEBUG
  for(i=0; i<size && i<=MAX_PRINT; i++)
    std::cout << A[i] << " ";

  std::cout << std::endl;
  
  std::cout << "Main: A[" << index << "] = " << res << std::endl; 
#endif

  // index starting from 1
  Insertion_Sort(A-1, 1, size);

#ifdef DEBUG
  for(i=0; i<size && i<=MAX_PRINT; i++)
    std::cout << A[i] << " ";

  std::cout << std::endl;

std::cout << "Main: A[" << index << "] = " << A[index-1] << std::endl; 
#endif

 std::cout << res << "\t" << A[index-1] << std::endl;

 delete[] A;
 
  return 0;
}





template<typename T>
void Insertion_Sort(T* A, int begin, int end){
  int i, j;
  T k;
  
  #ifdef DEBUG
    std::cout << "####################################################" << std::endl;
    std::cout << "Insertion_Sort: begin: " << begin << "  end: " << end << std::endl;
    std::cout << "Insertion_Sort: the vector BEFORE" << std::endl;
    for(i=0; i<end-begin+1 && i<MAX_PRINT; i++)
      std::cout << A[i+begin] << " ";
    std::cout << std::endl;
  #endif
  
  for( j=begin+1; j<=end; j++ ){
    k = A[j];
    i = j-1;
    while( i>begin-1 && A[i]>k ){
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = k;
  }

  #ifdef DEBUG
    std::cout << "Insertion_Sort: the vector AFTER" << std::endl;
    for(i=0; i<end-begin+1 && i<MAX_PRINT; i++)
      std::cout << A[i+begin] << " ";

    std::cout << std::endl;
    std::cout << "####################################################" << std::endl;
  #endif
}









template<typename T>
T Select_Pivot(T* A, int begin, int end){
  int blocks_num;
  T pivot;   
  if( (end-begin+1) % 5 == 0 )
    blocks_num = (end-begin+1)/5;
  else
    blocks_num = (end-begin+1)/5 + 1;
  
  #ifdef DEBUG
    std::cout << "####################################################" << std::endl;
    std::cout << "Select_Pivot: blocks_num: " << blocks_num << std::endl;
  #endif    

  T* Medians = new T[blocks_num];

  for( int i=0; i<blocks_num; i++ ){
    int cbegin = begin + 5*i;
    if( cbegin+4 > end ){
      Insertion_Sort(A, cbegin, end);
      Medians[i] = A[ cbegin + (end-cbegin)/2 ];
    }
    else{
      Insertion_Sort(A, cbegin, cbegin+4);
      Medians[i] = A[cbegin+2];
    }
  }


  #ifdef DEBUG
  std::cout << "Medians:" << std::endl;
    for(int i=0; i<blocks_num && i<=MAX_PRINT; i++)
      std::cout << Medians[i] << " ";
    std::cout << std::endl;      
  #endif

  
  pivot = Select(Medians-1, (blocks_num + 1) / 2, 1, blocks_num );
  #ifdef DEBUG
    std::cout << "Returning pivot: " << pivot << std::endl;
    std::cout << "####################################################" << std::endl;
  #endif
    
  return pivot;
}












template<typename T>
Partition Select_Partition(T* A, int begin, int end, T pivot){
  T k = pivot;

  #ifdef DEBUG
  int i;
  std::cout << "####################################################" << std::endl;
    std::cout << "Select_Partition: begin: " << begin << " end: " << end << std::endl;
    std::cout << "Select_Partition: pivo: " << k << std::endl;
    std::cout << "Select_Partition: the vector BEFORE" << std::endl;
    for(i=0; i<end-begin+1 && i<=MAX_PRINT; i++)
      std::cout << A[i+begin] << " ";
    std::cout << std::endl;
#endif

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
    #ifdef DEBUG
      std::cout << "Select_Partition: p: " << p << std::endl;
    std::cout << "Select_Partition: the vector AFTER FIRST CYCLE" << std::endl;
    for(i=0; i<end-begin+1 && i<=MAX_PRINT; i++)
      std::cout << i+1 << "\t";
    std::cout << std::endl;
    for(i=0; i<end-begin+1 && i<=20; i++)
      std::cout << A[i+begin] << "\t";
    std::cout << std::endl;      
    #endif

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
  #ifdef DEBUG
    std::cout << "Select_Partition: the vector AFTER" << std::endl;
    for(i=0; i<end-begin+1 && i<=MAX_PRINT; i++)
      std::cout << A[i+begin] << "\t";
    std::cout << std::endl;
    std::cout << "Select_Partition: returning: " << p << std::endl;
    std::cout << "####################################################" << std::endl;
  #endif

    return p;
}


template<typename T>
T Select(T* A, int j, int begin, int end){
  if( end - begin + 1 < SELECT_SIZE){
    #ifdef DEBUG
    std::cout << "####################################################" << std::endl;
    std::cout << "Select: size < " << SELECT_SIZE << ", sorting array" << std::endl;
    #endif
    Insertion_Sort(A, begin, end);
    return A[j];
  }

  #ifdef DEBUG
    std::cout << "####################################################" << std::endl;
    std::cout << "Select: size > " << SELECT_SIZE << ", selecting pivot" << std::endl;
  #endif  

  T pivot;
  pivot = Select_Pivot(A, begin, end);

  #ifdef DEBUG
    std::cout << "Select: pivot: " << pivot << std::endl;
  #endif  
  
    Partition p{1,1};
  p = Select_Partition(A, begin, end, pivot);

  #ifdef DEBUG
    std::cout << "Select: partition: " << p << std::endl;
  #endif  
  
  if( j < p.k1 ){
    return Select(A, j, begin, p.k1-1);
  }
  if( j > p.k2 ){
    return Select(A, j, p.k2+1, end);
  }

  return A[j];
}

