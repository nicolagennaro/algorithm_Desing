#include<Heap_casag.h>
#include<vector>
#include<iostream>


template<typename T>
class ReverseValueComparator{
	public:
		static int CMP(const T& a, const T& b){
			return ValueComparator::CMP(b,a);
		}
};


// takes a generic BinaryHeap, that's why the second template
template <typename T, template<typename, typename> class C>
C<T, std::allocator<T>> HeapSort(C< T, std::allocator<T> >& cont){
BinaryHeap<T, ReverseValueComparator> H(cont);

while( !H.size() > 0 ){
	// delete_root is non void here
	cont[H.size()] = H.delete_root();
}

// at the end of the while the elements are already sorted

return cont;

} // Heap sort




int main(){

return 0;
}
