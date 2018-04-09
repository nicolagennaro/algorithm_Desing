/*
When deriving a class from a base class, the base class may be inherited through public, protected or private inheritance. 
The type of inheritance is specified by the access-specifier as explained above.

We hardly use protected or private inheritance, but public inheritance is commonly used.

Public Inheritance: When deriving a class from a public base class, public members of the base class become public members of the derived classand protected members of the base class become protected members of the derived class. A base class's private members are never accessible directly from a derived class, but can be accessed through calls to the public and protected members of the base class.

Protected Inheritance: When deriving from a protected base class, public and protected members of the base class become protected members of the derived class.

Private Inheritance: When deriving from a private base class, public and protected members of the base class become private members of the derived class.

*/
// associative binary heap for Dijkstra
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
		AssociativeBinaryHeap( const C<T, std::allocator<T>>& cont ): BinaryHeap<T, Comparator> {}, MAP{NULL} {
			copy_in_heap( cont );
			MAP = new size_t[max_size];
			// maps the nodes of the graph to the nodes in the heap, we use integer numbers
			for( size_t i=0; i<max_size; i++)
				MAP[i] = i;
			build_heap();
		}
		
		// we also need a new insertion method
		void insert( const T& value ){
			// check size
			MAP[ num_of_elem ] = num_of_elem;
			
			container[num_of_elem] = value;
			fix_heap(num_of_elem);
			num_of_elem++; 
			// size_t i = num_of elem
			// container[i] = value;
			// fix)heap(i)
			
		
		}
		
		inline const size_t& index( const size_t Graph_node ) const {
			// check size
		 	return MAP[Graph_node]; 
		 }
		
		// std::ostream& operator<<( std::ostream& os, const AssociativeBinaryHeap<T, Comparator>&  )
	

};

/*

class NodeAndDistance{
	public:
		size_t node;
		unsigned_int distance;
		
		NodeAndDistance(const size_t n, const unsigned_int d): node{n}, distance{d} {}
};

class NodeAndDistanceComparator{
	public:
		static int CMP( const NodeAndDistance& a, const NodeAndDistance& b ){
			return ValueComparator<size_t>::CMP(a.distance, b.distance);
		}
};


To bulit the graph
graph = 
NodeAndDistance *V = {{0,infinity}, {} };
AssociativeBinaryHeap<NodeAndDistance, NodeAndDistanceComparator> H{V};

while( H.size() > 0 ){
	NodeAndDistance v = H.delete_root();
	for( typename list<size_t>::const_iterator it = Adj[v.node].cbegin(); it !=  Adj[v.node].cend(); it++ ){
		if( d[*it] > v.d + W[v][*it] )
			H.change_value( H.index[*it], NodeAndDistance{ *it, v.d + W[v][*it] } )
	}
}



*/
