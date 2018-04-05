#include<iostream>
#include<Heap_casag.h>


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

BinaryHeap<int,myValueComparator> h;



return 0;
}
