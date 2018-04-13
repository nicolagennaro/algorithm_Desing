#include <Graph.h>
#include <BinaryHeap.h>
#include <iostream>
#include <vector>
#include <cmath>


#define N_ROWS 4
#define N_COLS 4




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




// creates the graph of a grid from 0 to n_row-1,
// nodes are

// (n_row-1)*(n_col)  .... (n_row-1)*n_col + n_col-1 
// ..
// n_col, n_col+1, ..
// 0,     1,       2, .. n_col-1 
std::vector<std::vector<unsigned int>> manhattan(size_t n_row, size_t n_col){

  std::vector<std::vector<unsigned int>> adj;
  
  for(unsigned int i=0; i<n_row*n_col; i++){
    std::vector<unsigned int> tmp;
    if( (i+1) % n_col != 0 ){
      tmp.push_back(i+1);
    }
    if( i<(n_row-1)*n_col )
        tmp.push_back(i+n_col);
    adj.push_back(tmp);
  }

  return adj;
}



// given two nodes number compute the euclidean distance between the two indices
double heuristic(unsigned int a, unsigned int b){
  unsigned int a_x = a % N_ROWS;
  unsigned int a_y = a/N_COLS;
  unsigned int b_x = b % N_ROWS;
  unsigned int b_y = b/N_COLS;

  // std::cout << "Point " << a << std::endl;
  // std::cout << "x " << a_x << " y " << a_y << std::endl;

  // std::cout << "Point " << b << std::endl;
  // std::cout << "x " << b_x << " y " << b_y << std::endl;
  
  return sqrt( (a_x-b_x)*(a_x-b_x) + (a_y-b_y)*(a_y-b_y) );
}



void A_star(Graph& G, std::vector<std::vector<double>>& W, double (*h)(unsigned int, unsigned int), unsigned int s, unsigned int t){

  size_t size = G.size();

  double *distance = new double[size];
  double *h_bar = new double[size];
  unsigned int *parent = new unsigned int[size];

  for( unsigned int i=0; i<size; i++){
    distance[i] = INFINITY;
    h_bar[i] = INFINITY;
    parent[i] = s;
  }

  distance[s] = 0.0;
  // parent[s] = &G.
  h_bar[s] = h(s, t);

  std::cout << "h_bar[s]" << h_bar[s] << std::endl;


  std::vector<NodeAndDistance> nd1;

for(unsigned int i=0; i<size; i++){
	NodeAndDistance n{i, 0.0};
	n.node = i;
	n.distance = h_bar[i];
	nd1.push_back(n);
}


std::cout << "Heap" << std::endl;
for(unsigned int i=0; i<size; i++)
	std::cout << nd1[i] << std::endl;

AssociativeBinaryHeap<NodeAndDistance, MyValueComparator> min_heap{nd1};

std::cout << "print" << std::endl;
min_heap.print();


std::cout << "PARENTS" << std::endl;
for( unsigned int i=0; i<size; i++ )
	std::cout << i << " ";
std::cout << std::endl;	
for( unsigned int i=0; i<size; i++ )
	std::cout << parent[i] << " ";
std::cout << std::endl;

std::cout << "##########################\n" << std::endl;


// vector containing already visited nodes
std::vector<unsigned int> closed;



while( !min_heap.empty() ){
	//size_t index = min_heap.index(0); // given a position in the heap return the node number
	NodeAndDistance node = min_heap.delete_root();
	std::cout << "##########################" << std::endl;
	std::cout << "Astar on node " << node.node << std::endl;
	
	closed.push_back(node.node);
	
	if( node.node == t ){
		std::cout << "a star on target " << node.node << std::endl;
		break; 
	}
	//std::cout << "print" << std::endl;
	//min_heap.print();
	
	for( unsigned int w=0; w<G.Adj[node.node].size(); w++ ){
		unsigned int w_node = G.Adj[node.node][w];
		std::cout << "\n\tcomparing with node " << w_node << std::endl;
		std::cout << "\tdist betw " << node.node << " " << w_node << " = " << W[node.node][w] << std::endl;
		if( distance[w_node] > (distance[node.node] + W[node.node][w_node]) ){
			for( unsigned int j=0; j<closed.size(); j++){
				if( w_node == closed[j] ){
					std::cout << "find node already visited" << std::endl;
					return;
					throw "heuristic is BAD";
				}
			}
			
			distance[w_node] = distance[node.node] + W[node.node][w];
			
			std::cout << "\tdis w_node " << distance[w_node] << std::endl;
			std::cout << "\tdis index " << distance[node.node] << std::endl;
			std::cout << std::endl;
			// std::cout << "print" << std::endl;
			// min_heap.print();
			
			std::cout << "\tmin_heap.index(w_node)" << min_heap.index(w_node) << std::endl;
			
			NodeAndDistance n{w_node, distance[w_node] + h(w_node, t) };
			
			
			std::cout << "\tnew node " << n << std::endl;
			min_heap.change_value( min_heap.index(w_node), n );
			// std::cout << std::endl;
			// std::cout << "print" << std::endl;
			// min_heap.print();
			
			// std::cout << std::endl;
			
			parent[w_node] = node.node;
		}
	}
	
}// while



std::cout << "A_STAR:" << std::endl;
std::cout << "size " << size << std::endl; 
for( unsigned int i=0; i<size; i++ )
	std::cout << distance[i] << " ";
std::cout << std::endl;

std::cout << "PARENTS" << std::endl;
for( unsigned int i=0; i<size; i++ )
	std::cout << i << "\t";
std::cout << std::endl;	
for( unsigned int i=0; i<size; i++ )
	std::cout << parent[i] << "\t";
std::cout << std::endl;


std::cout << parent[10] << std::endl;
} // Astar




int main(){

  std::vector<std::vector<unsigned int>> adj;

  adj = manhattan(N_ROWS, N_COLS);
  
  std::vector<std::vector<double>> W;
  
  for( unsigned int i=0; i<adj.size(); i++ ){
  	std::vector<double> temp;
  	for( unsigned int j=0; j<adj[i].size(); j++)
  		temp.push_back(1.0);
  	W.push_back(temp);
  }

  Graph g{adj};

  g.print();
  
  for( unsigned int i=0; i<W.size(); i++ ){
  	std::cout << "Node " << i << std::endl; 
  	for( unsigned int j=0; j<W[i].size(); j++)
		std::cout << W[i][j] << " ";
	std::cout << std::endl;
}

  double d;
  d = heuristic(4,0);
  
  std::cout << d << std::endl;
  
  A_star(g, W, heuristic, 0, N_ROWS*N_COLS - 1);
  
  
  return 0;
}
