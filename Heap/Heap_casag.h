#ifndef __HEAP_CASAG__
#define __HEAP_CASAG__

#include<cstdlib>

template<typename T>
class ValueComparator{
	public:
		static int CMP(const T& a, const T& b){
			if( a>b ) return 1;
			else if ( b<a ) return -1;
			else return 0; 
		}
};






template <typename T, template<typename> class Comparator=ValueComparator >
class BinaryHeap{

	protected:
		T* container;
		size_t max_size;
		size_t num_of_elem;
		
		static inline size_t right_son(const size_t i) { return 2*(i+1); }
		static inline size_t left_son(const size_t i) { return 2*i + 1; }
		static inline size_t father(const size_t i) { return (i-1)/2; }
		
		virtual void swap( const size_t i, const size_t j ){
			std::swap( container[i], container[j] );
		}
		
		void heapify( size_t i ){
		
			do{
			size_t min_son_id = left_son(i);
			if( min_son_id >= num_of_elem )
				return;
			if( (right_son(i) < num_of_elem) && Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) > 0)
				min_son_id = right_son(i);
			if( Comparator<T>::CMP(container[i], container[min_son_id] ) < 0)
				swap(i, min_son_id);
			else
				return;
				
			i = min_son_id;
			
			}while( true );
		}
		
		void build_heap(){
			for( size_t i = num_of_elem/2; i>0; i--)
				heapify(i);
			if( num_of_elem > 0 )
				heapify(0);
		}
		
		void fit_heap( size_t i ){
			size_t father_id = father(i);
			
			while( (i != 0) && (Comparator<T>::CMP(container[i], container[father_id]) > 0) ){
				swap( container[i], container[father_id] );
				i = father_id;
				father_id = father(i);
			}
		}
		
		// this method copy a generic std container in the heap data structure called container
		template< template<typename, typename> class C >
			void copy_in_heap( const C<T, std::allocator<T>> & container){
			num_of_elem = 0;
			max_size = container.size();
			this->container = new T[max_size];
			for( typename C<T, std::allocator<T>>::const_iterators it = std::cbegin(container); it != std::cend(container); ++it)
				this->container[ num_of_elem++ ] = *it;
		}


	public:
		template< template<typename, typename> class C >
		BinaryHeap( const C<T, std::allocator<T>> & container ){
			copy_in_heap(container);
			build_heap();
		}
		
		BinaryHeap(): container{nullptr}, max_size{0}, num_of_elem{0} {}
		
		~BinaryHeap() { delete[] container; }
		
		void insert( const T& value ){
			// check size !!! max_size > num_of_elem
			if( num_of_elem+1 > max_size )
				exit(1);
				
			container[num_of_elem] = value;
			fix_heap(num_of_elem);
			num_of_elem++; 
		
		}
		
		const T& root_value() const{
			// check size !!! max_size > num_of_elem
			return container[0];
		}
		
		void delete_root(){
			// check size !!! max_size > num_of_elem
			swap(0, num_of_elem-1);
			num_of_elem--;
			heapify(0);
		}
		
		void change_value( size_t i, const T& value ){
			if( Comparator<T>::CMP(container[i], value) > 0 ){
				return;
				// throw //exception;
				}
			container[i] = value;
			fix_heap(i);
		}
		
};


#endif
