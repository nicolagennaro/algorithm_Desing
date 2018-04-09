#include<iostream>
#include<Heap_casag.h>
#include<vector>

// opposite on that on the header
template<typename T>
class myValueComparator{
	public:
		static int CMP(const T& a, const T& b){
			if( a>b ) return -1;
			else if ( b<a ) return 1;
			else return 0; 
		}
};


int main(){

  std::vector<int> v{1,3,2,6,4,8,40,39,38,37,36};
  
  BinaryHeap<int,myValueComparator> min_heap{v};

  for(int i=0; i<v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
  

 while( !min_heap.empty() ){
 std::cout << "root_value(): " << min_heap.root_value() << std::endl;
 min_heap.delete_root();   
 }


  for(int i=0; i<v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;

 
 BinaryHeap<int> max_heap{v};

 while( !max_heap.empty() ){
 std::cout << "root_value(): " << max_heap.root_value() << std::endl;
 max_heap.delete_root();   
 }

 std::vector<int> vrand;
 
 for(int i=0; i<20; i++)
   vrand.push_back( rand() % 100 );
 
 BinaryHeap<int, myValueComparator> h{vrand};

 while( !h.empty() ){
   std::cout << h.root_value() << " ";
   h.delete_root();
 }

 std::cout << std::endl;
 
 BinaryHeap<int> h1{vrand};

 while( !h1.empty() ){
   std::cout << h1.root_value() << " ";
   h1.delete_root();
 }

 std::cout << std::endl;


 return 0;
}
