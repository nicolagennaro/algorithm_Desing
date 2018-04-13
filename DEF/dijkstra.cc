#include <iostream>
#include <Graph.h>
#include <BinaryHeap.h>
#include <vector>
#include <cmath>
// #include <>





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





template<typename T>
class MyValueComparator{
public:
  static int CMP(const T& a, const T& b){
    if( b>a ) return 1;
    else if( a>b ) return -1;
    else return 0;
  }
};


class NodeAndDistance{
	public:
		size_t node;
		double distance;
		
		NodeAndDistance(): node{3}, distance{0.1} {}
		NodeAndDistance(const size_t n, const double d): node{n}, distance{d} {}
		
		
		
		friend std::ostream& operator<<(std::ostream& os, NodeAndDistance& nd){
			os << nd.node << " " << nd.distance;
			return os;
		}
		
		bool operator<( const NodeAndDistance& other ) const { return distance < other.distance; }
		bool operator>( const NodeAndDistance& other ) const { return distance > other.distance; }
		bool operator==( const NodeAndDistance& other ) const { return !(distance < other.distance) && !(distance > other.distance); }
		
};



void dijkstra(Graph& G, std::vector<std::vector<double>>& W, unsigned int s){

size_t size = G.size();
double *distance = new double[size];
unsigned int **parent = new unsigned int*[size];

std::vector<NodeAndDistance> nd1;

std::cout << "\nDIJKSTRA\n" << std::endl;

for(unsigned int i=0; i<size; i++){
	NodeAndDistance n{i, 0.0};
	if( i == s ){
		n.node = i;
		n.distance = 0.0;
	}
	else{
		n.node = i;
		n.distance = INFINITY;	
	}
	nd1.push_back(n);
	std::cout << nd1[i] << std::endl;
	distance[i] = INFINITY;
	//nd[i] = n;
	parent[i] = nullptr;
}

for( unsigned int i=0; i<size; i++){
	//std::cout << "Node " << nd[i].node << " distance " << nd[i].distance << std::endl;
	std::cout << "Node " << nd1[i].node << " distance " << nd1[i].distance << std::endl;
	}
	
distance[s] = 0.0;
parent[s] = nullptr;

AssociativeBinaryHeap<NodeAndDistance, MyValueComparator> min_heap{nd1};

std::cout << "print" << std::endl;
min_heap.print();

std::cout << "##########################\n" << std::endl;

while( !min_heap.empty() ){
	//size_t index = min_heap.index(0); // given a position in the heap return the node number
	NodeAndDistance node = min_heap.delete_root();
	std::cout << "dijkstra on node " << node.node << std::endl;
	
	// min_heap.delete_root();
	std::cout << std::endl;
	std::cout << "print" << std::endl;
	min_heap.print();
	for( unsigned int w=0; w<G.Adj[node.node].size(); w++ ){
		unsigned int w_node = G.Adj[node.node][w];
		std::cout << "\tcomparing with node " << w_node << std::endl;
		std::cout << "dist betw " << node.node << " " << w_node << " = " << W[node.node][w] << std::endl;
		if( distance[w_node] > (distance[node.node] + W[node.node][w_node]) ){
			std::cout << "\tdis w_node " << distance[w_node] << std::endl;
			std::cout << "\tdis index " << distance[node.node] << std::endl;
			std::cout << std::endl;
			std::cout << "print" << std::endl;
			min_heap.print();
			
			std::cout << "\tmin_heap.index(w_node)" << min_heap.index(w_node) << std::endl;
			NodeAndDistance n{w_node, distance[node.node] + W[node.node][w]};
			std::cout << "new node " << n << std::endl;
			min_heap.change_value( min_heap.index(w_node), n );
			std::cout << std::endl;
			std::cout << "print" << std::endl;
			min_heap.print();
			std::cout << std::endl;
			distance[w_node] = distance[node.node] + W[node.node][w];
			parent[w_node] = nullptr;
		}
	}
	
}// while

std::cout << "Dijk" << std::endl;
for( size_t i=0; i<size; i++ )
	std::cout << distance[i] << " ";
std::cout << std::endl;

} // dijkstra




int main(){

  std::vector<int> v{5,4,3,2,1,43,44,45,64,24,12,44,44};

  BinaryHeap<int> max_heap{v};

  std::cout << "heap_ done" << std::endl;
  
  for( unsigned int i=0; i<v.size(); i++)
    std::cout << max_heap[i] << " ";
  std::cout << std::endl;

  std::cout << "\nnow print test" << std::endl;
  while( !max_heap.empty() ){
    std::cout << max_heap.delete_root() << std::endl;
  }


  BinaryHeap<int, MyValueComparator> min_heap{v};

    std::cout << "\nnow print test" << std::endl;
  while( !min_heap.empty() ){
    std::cout << min_heap.delete_root() << std::endl;
  }
  
  // graph pag 116 dasgupta
  std::vector<std::vector<unsigned int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  Graph G{Adj};
  G.print();
    
  std::vector<std::vector<double>> W{ {4,2}, {3,2,3}, {1,4,5}, {}, {1}};

  dijkstra(G,W,1);
  
  return 0;
}
