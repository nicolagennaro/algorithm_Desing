#ifndef __HEAP_CASAG__
#define __HEAP_CASAG__

#include<cstdlib>
#include<iterator>



struct Heap_Error{
	std::string message;
};


template<typename T>
class ValueComparator{
	public:
		static int CMP(const T& a, const T& b){
			if( a>b ) return 1;
			else if ( b>a ) return -1;
			else return 0; 
		}
};






template <typename T, template<typename> class Comparator=ValueComparator >
class BinaryHeap{

	protected:
		T* container;
		size_t max_size;
		size_t num_of_elem;
		
		
		// static means that the function can be called even if no objects of the class exist
		// Static member functions are not associated with any object. When called, they have no 'this' pointer.
		// they are not stored in the object but there is one function pointer to it
		// The address of a static member function may be stored in a regular pointer to function, but not in a 
		// pointer to member function.

		
		static inline size_t right_son(const size_t i) { return 2*(i+1); }
		static inline size_t left_son(const size_t i) { return 2*i + 1; }
		static inline size_t father(const size_t i) { return (i-1)/2; }
		
		virtual void swap( const size_t i, const size_t j ){
			std::swap( container[i], container[j] );
		}
		
		void heapify( size_t i ){
		
			do{
				size_t min_son_id = left_son(i);
				
				//std::cout << "min " << min_son_id << std::endl;
				
				if( min_son_id >= num_of_elem ){
					//std::cout << "   min >= num_of" << num_of_elem << std::endl;
					return;
					}
				// right_son
				if( (right_son(i) <= num_of_elem) && Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) < 0){
					min_son_id = right_son(i);
					//std::cout << "   Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) > 0" << std::endl;
					//std::cout << "   min_son " << min_son_id << std::endl;
					}
				if( Comparator<T>::CMP(container[i], container[min_son_id] ) < 0){
					//std::cout << "  swap " << i << " " << min_son_id << std::endl;
					swap(i, min_son_id);
					// heapify(min_son_id);
				}
				else
					return;
				
				i = min_son_id;
			
			}while( true );
			/*
			do{
				size_t min_son_id = i;
				std::cout << "min " << min_son_id << std::endl;
				if( left_son(i) >= num_of_elem ){
					std::cout << "   min >= num_of" << num_of_elem << std::endl;
					return;
					}
				
				std::cout << "i " << container[i] << " left " << container[left_son(i)] << std::endl;
				if( Comparator<T>::CMP(container[i], container[left_son(i)]) > 0 )
					min_son_id = left_son(i);
					
				if( (right_son(i) < num_of_elem) && Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) > 0){
					min_son_id = right_son(i);
					std::cout << "   Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) > 0" << std::endl;
					std::cout << "   min_son " << min_son_id << std::endl;
					}
				if( Comparator<T>::CMP(container[i], container[min_son_id] ) > 0 || Comparator<T>::CMP(container[i], container[min_son_id] ) < 0){
					std::cout << "  swap " << i << " " << min_son_id << std::endl;
					swap(i, min_son_id);
					// heapify(min_son_id);
				}
				else
					return;
				
				i = min_son_id;
			
			}while( true );
			*/
		}
		
		void build_heap(){
			// original for( size_t i = num_of_elem/2; i>0; i--)
			for( size_t i = num_of_elem/2; i>0; i--){
				std::cout << "heapify " << i << std::endl;
				heapify(i);
				}
			std::cout << "build_heap " << num_of_elem << std::endl;
			if( num_of_elem > 0 )
				heapify(0);
		}
		
		void fix_heap( size_t i ){
			size_t father_id = father(i);
			
			while( (i != 0) && (Comparator<T>::CMP(container[i], container[father_id]) > 0) ){
				swap( container[i], container[father_id] );
				i = father_id;
				father_id = father(i);
			}
		}
		
		// this method copy a generic std container in the heap data structure called container
		// std::allocator is the standard allocator for all types
		template< template<typename, typename> class C >
		void copy_in_heap( const C<T, std::allocator<T>> & container){
			num_of_elem = 0;
			max_size = container.size();
			this->container = new T[max_size];
			for( typename C<T, std::allocator<T>>::const_iterator it = std::cbegin(container); it != std::cend(container); ++it)
				this->container[ num_of_elem++ ] = *it;
		}


	public:
		template< template<typename, typename> class C >
		BinaryHeap( const C<T, std::allocator<T>> & container ){
			copy_in_heap(container);
			build_heap();
		}
		
		BinaryHeap(): container{nullptr}, max_size{0}, num_of_elem{0} {}
		
		virtual ~BinaryHeap() { delete[] container; }
		
		void insert( const T& value ){
			// check size !!!
			if( num_of_elem+1 > max_size )
				throw Heap_Error{"Heap: Reached max heap size " + std::to_string(max_size)};
				
			container[num_of_elem] = value;
			fix_heap(num_of_elem);
			num_of_elem++; 
		}
		
		// returns the first element of the Heap
		const T& root_value() const{
			return container[0];
		}
		
		// delete the first element of the Heap 
		const T& delete_root(){
			T el = container[0];
			swap(0, num_of_elem-1);
			num_of_elem--;
			heapify(0);
			return el;
		}
		
		void change_value( const size_t i, const T& value ){
			if( Comparator<T>::CMP(container[i], value) > 0 ){
				return;
				// throw //exception;
			}
			container[i] = value;
			fix_heap(i);
		}
		
		bool empty() { return num_of_elem==0; }
		
		inline size_t size() const { return num_of_elem; }
		
		inline size_t get_max_size() const { return max_size; }
		
		const T& operator[](const size_t& i) const { 
			if( i<size() )
				return container[i]; 
			throw std::out_of_range("...");
		}
		
		const BinaryHeap<T,Comparator>& operator=( const BinaryHeap<T,Comparator>& other){
			delete[] container;
			num_of_elem = other.num_of_elem;
			max_size = other.max_size;
			container = new T[max_size];
			// std::copy(other.container,other.container + other.size(), container )
			for( size_t i=0; i<other.size(); i++)
				container[i] = other.container[i];
			return *this;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const BinaryHeap<T,Comparator>& H){
			os << "BinaryHeap[ ";
			if( H.size() > 0 )
				os << H[0];
			for( size_t i=1; i<size(); i++)
				os << ", " << H[i];
			os << " ]" << std::endl;
			return os;
		}
		
};


#endif
