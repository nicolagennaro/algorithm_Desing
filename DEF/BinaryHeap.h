#ifndef __HEAP_CASAG__
#define __HEAP_CASAG__

#include<cstdlib>
#include<iterator>


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
		
		static inline size_t right_son(const size_t i) { return 2*(i+1); }
		static inline size_t left_son(const size_t i) { return 2*i + 1; }
		static inline size_t father(const size_t i) { return (i-1)/2; }
		
		virtual void swap( const size_t i, const size_t j ){
			std::swap( container[i], container[j] );
		}
		
		
		
		// 
		void heapify( size_t i ){
			/*
			do{
				size_t min_son_id = left_son(i);
				if( min_son_id >= num_of_elem ){
					return;
					}
					
				if( (right_son(i) <= num_of_elem) && Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) < 0){
					min_son_id = right_son(i);
					}
				if( Comparator<T>::CMP(container[i], container[min_son_id] ) > 0){
					swap(i, min_son_id);
				}
				else
					return;
				
				i = min_son_id;
			
			}while( true );
			*/
			do{
				size_t min_son_id = left_son(i);
				if( min_son_id >= num_of_elem ){
					return;
					}
				
				//std::cout << "cont[ " << i << " ] = " << container[i] << std::endl; 
				
				// if container[ left_son ] < container[right_son]
				// if container[min_son_id] < container[right_son]
				if( (right_son(i) < num_of_elem) && Comparator<T>::CMP(container[min_son_id], container[right_son(i)] ) < 0){
					//std::cout << "here" << std::endl;
					min_son_id = right_son(i);
					}
				// if container[min_son_id] < container[i] 
				if( Comparator<T>::CMP(container[i], container[min_son_id] ) < 0){
					//std::cout << "swap " << container[i] << " " << container[min_son_id] << std::endl;
					swap(i, min_son_id);
				}
				else
					return;
				
				i = min_son_id;
			
			}while( true );
		}
		
		void build_heap(){
			// original for( size_t i = num_of_elem/2; i>0; i--)
			for( size_t i = num_of_elem/2; i>0; i--){
				//std::cout << "heapify " << i << std::endl;
				heapify(i);
				}
			//std::cout << "build_heap " << num_of_elem << std::endl;
			if( num_of_elem > 0 ){
				//std::cout << "heapify " << "0" << std::endl;
				heapify(0);
				}
		}
		
		void fix_heap( size_t i ){
			size_t father_id = father(i);
			std::cout << "fix on " << i << std::endl;
			while( (i != 0) && (Comparator<T>::CMP(container[i], container[father_id]) > 0) ){
				std::cout << "swap " << i << " " << father_id << std::endl;
				//swap( container[i], container[father_id] );
				swap(i, father_id);
				i = father_id;
				father_id = father(i);
			}
		}
		
		// this method copy a generic std container in the heap data structure called container
		// std::allocator is the standard allocator for all types
		template< template<typename, typename> class C >
		void copy_in_heap( const C<T, std::allocator<T>> & cont){
			num_of_elem = cont.size();
			max_size = cont.size();
			this->container = new T[max_size];
			// std::cout << " copy in heap " << cont[0].node <<  std::endl;
			//for( typename C<T, std::allocator<T>>::const_iterator it = std::cbegin(cont); it != std::cend(cont); ++it)
			//	this->container[ num_of_elem++ ] = *it;
			for( unsigned int i=0; i<cont.size(); i++){
				this->container[i] = cont[i];
				// std::cout << "copi " << cont[i].node << std::endl; 
				}
			std::cout << " copy in heap " << num_of_elem << std::endl;
			std::cout << " copy in heap " << container[0] << std::endl;
		}


	public:
		template< template<typename, typename> class C >
		BinaryHeap( const C<T,std::allocator<T>>& container ){
			std::cout << "coping container" << std::endl;
			copy_in_heap(container);
			build_heap();
		}
		
		BinaryHeap(): container{nullptr}, max_size{0}, num_of_elem{0} {
			std::cout << "BinHeap" << std::endl;
		}
		
		virtual ~BinaryHeap() { delete[] container; }
		
		void insert( const T& value ){
			// check size !!!
			if( num_of_elem+1 > max_size )
				throw std::out_of_range("...");
				
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
			// T el = container[0];
			swap(0, num_of_elem-1);
			num_of_elem--;
			heapify(0);
			return container[num_of_elem];
		}
		
		void change_value( const size_t i, const T& value ){
			if( Comparator<T>::CMP(container[i], value) > 0 ){
				return;
				// throw //exception;
			}
			//std::cout << " changing " << container[i] << " in "  << value << std::endl;
			container[i] = value;
			//std::cout << container[i] << std::endl;
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

template <typename T, template<typename> class Comparator=ValueComparator >
class AssociativeBinaryHeap: public BinaryHeap<T, Comparator>{

	protected:
		// maps the nodes of the graph to the position of the binary heap
		// this is why swap was virtual, we have to swap also this MAP
		
		size_t *MAP;
	
		// overrides the swap method in the base class
		// now also the heapify and other methods that use swap calls this swap function, not the original one
		
		void swap( const size_t i, const size_t j ) override{
			//std::swap( container[i], container[j] );
			BinaryHeap<T, Comparator>::swap(i,j);
			std::swap( MAP[i], MAP[j] );
		}
	
	public:
		// some compilers complains if we don't create the base class before using its methods, that's why
		// BinaryHeap
		template< template<typename, typename> class C >
		AssociativeBinaryHeap( const C<T, std::allocator<T>>& cont ): BinaryHeap<T, Comparator> {cont}, MAP{NULL} {
			std::cout << "first el " << cont[0].distance << std::endl;
			std::cout << "first el " << cont[1].node << std::endl;
			// this->copy_in_heap( cont );
			this->num_of_elem = cont.size();
			this->max_size = cont.size();
			this->container = new T[this->max_size];
			for( unsigned int i=0; i<cont.size(); i++){
				std::cout << "copi " << this->container[i].node << std::endl; 
				this->container[i] = cont[i];
				std::cout << "after copi " << this->container[i].node << std::endl; 
				std::cout << "copi " << cont[i].node << std::endl; 
				}
			MAP = new size_t[this->max_size];
			// maps the nodes of the graph to the nodes in the heap, we use integer numbers
			for( size_t i=0; i<this->max_size; i++)
				MAP[i] = i;
			this->build_heap();
		}
		
		// we also need a new insertion method
		void insert( const T& value ){
			// check size
			
			MAP[ this->num_of_elem ] = this->num_of_elem;
			
			this->container[this->num_of_elem] = value;
			fix_heap(this->num_of_elem);
			this->num_of_elem++; 
			// size_t i = num_of elem
			// container[i] = value;
			// fix)heap(i)
			
		
		}
		
		// 
		inline const size_t& index( const size_t Graph_node ) const {
			// check size
		 	return MAP[Graph_node]; 
		 }
		
		// std::ostream& operator<<( std::ostream& os, const AssociativeBinaryHeap<T, Comparator>&  )
		void print(){
			for(size_t i=0; i<this->num_of_elem; i++)
				std::cout << this->container[i] << " ";
			std::cout << std::endl;
			for(size_t i=0; i<this->num_of_elem; i++)
				std::cout << MAP[i] << " ";
			std::cout << std::endl;
			
		}

};




/*
template<typename T>
class NodeAndDistanceComparator{
	public:
		static int CMP( const NodeAndDistance& a, const NodeAndDistance& b ){
			return MyValueComparator<double>::CMP(a.distance, b.distance);
		}
};
*/


#endif
