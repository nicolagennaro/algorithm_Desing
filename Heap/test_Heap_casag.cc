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

  std::vector<int> v{1,3,2,6,4,8};

  int *pt = new int[3];

  pt[0] = 1;
  pt[1] = 2;
  pt[3] = 3;
  
  BinaryHeap<int,myValueComparator> min_heap{v};

  for(int i=0; i<v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
  
 // std::cout << "insert 0 " << std::endl;
 // h.insert(0);
 // h.insert(1);

 std::cout << "root_value(): " << min_heap.root_value() << std::endl;
 min_heap.delete_root();
 std::cout << "root_value(): " << min_heap.root_value() << std::endl;
 min_heap.delete_root();
 std::cout << "root_value(): " << min_heap.root_value() << std::endl;
 min_heap.delete_root();

 while( !min_heap.empty() ){
 std::cout << "root_value(): " << min_heap.root_value() << std::endl;
 min_heap.delete_root();
   
 }


 
return 0;
}
