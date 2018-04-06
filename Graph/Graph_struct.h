#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>
#include <../Heap/Heap.h>
#include <../Strassen/Strassen.h>



class Graph{
	enum class color {white, grey, black};

	struct Node;

	std::vector<Node> nodes;
        
        // once tarjan is performed the SCC are saved in the node
        bool tarjan_done;


        public:
		// Graph(): tarjan_done{false} { this->insert(); }
		
		Graph() {}
		Graph(std::vector<std::vector<int>>&, std::vector<std::vector<double>>& );
		Graph(std::vector<std::vector<int>>&);
		
		void print();
		void insert();
		// int number_of_nodes() {return nodes.size(); };

		void dfs();
		void bfs(int);
		
		// returns a vector with nodes number and S(nodes)
		std::vector<int> topological_sort();
		std::vector<std::pair<int, int>> topological_sort1( bool = false );

		std::vector<std::vector<int>> Tarjan_SCC();
		
		void Dijkstra(int);

		Graph collapse();
		
		double* adj_UTmatrix();
		void Fischer_Mayer();
		
  		// void set_SCC(){ SCCs = this->Tarjan_SCC(); }
  		void print_SCC();
  		
};




struct Graph::Node{
			
	int name;
			
	int SCC;
	color col;
	int topological_sort_value;
			
			
	int discovery_time;
	int final_time;
	int low_link;
			
	Node *parent;		// dijkstra
	double distance;	// bfs, dijkstra
			
	std::vector<Node*> adj;
	std::vector<double> W;
		

	Node(int n): name{n}, SCC{0}, col{color::white}, topological_sort_value{-1}, discovery_time{-1}, final_time{-1}, low_link{-1}, parent{nullptr}, distance{INFINITY} {}

	void print_Node() const;
	                
	bool operator==(const Node& other) const { return this->name == other.name; }
	bool operator!=(const Node& other) const { return !(*this == other); }
	                
	// compare distances for dijkstra
	bool operator<(const Node& other){ return this->distance < other.distance; }
	               	
	int dfs(int);
	int topological_sort(int, std::queue<int> &);
			
			
	int Tarjan_SCC(int, std::stack<Graph::Node*>&, std::vector<std::vector<int>> &);
 
 }; // Graph::Node





void zero_one( double* mat, int size ){

for ( int i=0; i<size; i++ )
	for( int j=0; j<size; j++ ) 
		if( mat[ i*size + j ] != 0.0 )
			mat[ i*size + j ] = 1.0;

}




void compute_TC_matrix_real(double* M, int size){
	
	if( size == 1 )
		return;
		
	int h_size = size/2;
	double *A, *B, *C, *D;
	
	A = new double[h_size*h_size];
	
	
	
	B = new double[h_size*h_size];
	C = new double[h_size*h_size];
	D = new double[h_size*h_size];

}




void compute_TC_matrix( double* M, int size ){
	
	if( next_pow_two(size) == size ){
		compute_TC_matrix_real(M, size);
		return;
	}
	
	int new_size = next_pow_two(size);
	double *M_resized;
	
	M_resized = resize_matrix(M, size, new_size);
	
	compute_TC_matrix_real(M_resized, new_size);
	
	for( int i=0; i<size; i++ )
		for( int j=0; j<size; j++ )
			M[ i*size + j ] = M_resized[ i*new_size + j ];
			
	delete[] M_resized;
}





double* Graph::adj_UTmatrix(){


std::cout << "##########################################################" << std::endl;
std::cout << "############         adj_UTmatrix           ##############" << std::endl;
std::cout << "##########################################################" << std::endl;


	int nodes_num = nodes.size();
	
	std::cout << "nodes_num " << nodes_num << std::endl;
	
	double *mat = new double[ nodes_num * nodes_num ];
	
	for( int i=0; i<nodes_num; i++ ){
		for( int j=0; j<nodes_num; j++){
			if( i ==j )
				mat[ i*nodes_num + j ] = 1.0;
			else
				mat[ i*nodes_num + j ] = 0.0;
		}
	}
	
	// contains nodes numbers from the topological sort (node_number, Sort)
	std::vector<std::pair<int,int>> topo;
	
	topo = this->topological_sort1(true);
	
	std::cout << "N S" << std::endl;
	for( unsigned int i=0; i<topo.size(); i++ ){
		std::cout << topo[i].first << " " << topo[i].second << std::endl;
	}
	
	// sort the nodes of the collapsed graph following decreasing order of S
	
	
	
	// remember that the name of nodes in this matrix follows the inverse topological sort 
	// order, maybe first you should order the nodes vector 
	
	
	// std::cout << "sort.size() " << sort.size() << std::endl;
	
	int size = topo.size()-1;
	for( int i=size; i>=0; i--){
		for( unsigned int w=0; w<nodes[ topo[i].first ].adj.size(); w++ ){
			std::cout << "inserting the node " << nodes[ topo[i].first ].adj[w]->name << std::endl;
			std::cout << "the position is the one in the topo sort" << std::endl;
			int pos=0;
			while( topo[pos].first != nodes[ topo[i].first ].adj[w]->name )
				pos++;
				
			mat[ (size-i)*nodes_num + size -pos ] = 1.0;
		}
	}
	
	// print_mat(mat, nodes_num);
	
	/*
	
	for( int i=sort.size()-1; i>=0; i--){
		std::cout << "\nscanning list of node " << sort[i] << std::endl;
		//if( nodes[ sort[i] ].adj )
		//	std::cout << "nodes[ sort[i] ].adhj OK" << std::endl;
		// std::cout << "   " << nodes[ sort[i] ].adj.size() << std::endl;
		// std::cout << "SAFE" << std::endl;
		// std::cout << " sort[i] " << sort[i] << std::endl;
		for( unsigned int w=0; w<nodes[ sort[i] ].adj.size(); w++ ){
			// std::cout << "here";
			std::cout << "inserting the node " << nodes[ sort[i] ].adj[w]->name << std::endl;
			// std::cout << "the position is the one in the inverse topo sort" << std::endl;
			//int pos=sort.size()-1;
			int pos=0;
			while( sort[pos] != nodes[ sort[i] ].adj[w]->name )
				pos++;
				
			std::cout << "i " << i << std::endl;
			std::cout << "pos in sort " << pos << std::endl;
			std::cout << "pos in mat " << (sort.size()-1-i) << " " << sort.size()-1 - pos << std::endl;
			mat[ (sort.size()-1-i)*nodes_num + sort.size()-1 - pos ] = 1.0;
		}
	}
	std::cout << "Final Matrix: " << std::endl;
	print_mat(mat, nodes_num);
	
	*/

return mat;
}




// FISCHER MAYER
void Graph::Fischer_Mayer(){

std::cout << "##########################################################" << std::endl;
std::cout << "############         FISCHER-MAYER          ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

	// compute collapsed graph
	
	Graph collapsed = this->collapse();

	std::cout << "COLLAPSED GRAPH" << std::endl;
	collapsed.print();
	std::cout << std::endl;

	
	// The adj matrix of collapsed should be built using this order to
	// have an upper triangular matrix, this is the vector with name of nodes
	
	
	double *m;
	
	m = collapsed.adj_UTmatrix();
	
	int SCCsize = collapsed.nodes.size();
	
	std::cout << "Adjacency matrix of collapsed graph" << std::endl;
	print_mat(m, SCCsize);
	std::cout << std::endl;

} // fisc mayer








std::vector<std::pair<int,int>> Graph::topological_sort1( bool sort ){

std::cout << "##########################################################" << std::endl;
std::cout << "############       TOPOLOGICAL SORT1        ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

  std::vector<std::vector<int>> SCCs;

  SCCs = Tarjan_SCC();
  
  int S = 1;
  std::pair<int,int> p;
  std::vector<std::pair<int,int>> r;
  for( unsigned int i=0; i<SCCs.size(); i++ ){
  	for( unsigned int j=0; j<SCCs[i].size(); j++ ){
  		p = {SCCs[i][j], S};
  		r.push_back(p);
  	}
  	S++;
  }

  if( sort ){ 
  	
  	// insertion sort
  	int key;
  	int other_key;
  	for( unsigned int j=1; j<r.size(); j++ ){
  		key = r[j].second;
  		other_key = r[j].first;
  		int i = j-1;
  		while( i>=0 && r[i].second>key ){
  			r[i+1].second = r[i].second;
  			r[i+1].first = r[i].first;
  			i--;
  		}
  		r[i+1].second = key;
  		r[i+1].first = other_key;
  	}
  	
  	
  }
  
  return r;
} // topo1


/*

// topological sort of Graph
// if V reaches W then S(V) < S(W), the topological order is the order of
// execution if the edges represent a dependency 
std::vector<int> Graph::topological_sort(){

std::cout << "##########################################################" << std::endl;
std::cout << "############       TOPOLOGICAL SORT         ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

  for(unsigned int i=0; i<nodes.size(); i++){
    nodes[i].col = color::white;
    nodes[i].discovery_time = -1;
    nodes[i].final_time = -1;
  }

  int time{0};
  std::queue<int> Q;

  for(unsigned int i=0; i<nodes.size(); i++)
    if( nodes[i].col == color::white )
      time = nodes[i].topological_sort(time, Q);

 for(unsigned int i=0; i<nodes.size(); i++){
    std::cout << "\nNode: " << nodes[i].get_name() << std::endl;
    std::cout << "Discovery: " << nodes[i].get_disc() << std::endl;
    std::cout << "Final:     " << nodes[i].get_fin() << std::endl;
  }
  

  
  std::vector<int> sorted_list;
  while( !Q.empty() ){
  	std::cout << "element: " << Q.front() << std::endl;
  	sorted_list.push_back( Q.front() );
  	Q.pop();
  }
  
std::cout << "\n##########################################################" << std::endl;

return sorted_list;

} // topo graph


int Graph::Node::topological_sort(int time, std::queue<int> &Q){

  this->set_col(color::grey);
  this->set_disc(time);
  time++;

  for(unsigned int i=0; i<adj.size(); i++){
    if( adj[i]->get_col() == color::white ){
      time = adj[i]->topological_sort(time, Q);
    }
  }

  this->set_fin(time);
  Q.push( this->name );
  time++;

  return time;

} // Node::topological_sort



*/



class Graph Graph::collapse(){

std::cout << "##########################################################" << std::endl;
std::cout << "############            COLLAPSE            ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

  std::vector<std::vector<int>> SCCs;

  SCCs = Tarjan_SCC();
  
  for( unsigned int i=0; i<nodes.size(); i++ ){
  	std::cout << "Node " << nodes[i].name << std::endl;
  	std::cout << "SCC " << nodes[i].SCC << std::endl;
  }
  std::cout << std::endl;
  
  for( unsigned int i=0; i<SCCs.size(); i++ ){
  	std::cout << "SCCs " << i << std::endl;
  	for( unsigned int j=0; j<SCCs[i].size(); j++ )
  		std::cout << SCCs[i][j] << "\t";
  	std::cout << std::endl;
  }
  
  // for all nodes in the SCC, temp adj for SCC compute adj to nodes outside
  // if the edge not present add it to the vector of the adj of the SCC
  
  std::vector<std::vector<int>> SCCadj;
  std::vector<std::vector<double>> SCCweights;
  
  
  // for all the SCCs of the original graph
  for( unsigned int scc=0; scc<SCCs.size(); scc++){
  
  	std::cout << "\nscanning SCC " << scc << std::endl;
  	std::vector<int> curr_adj;
  	std::vector<double> curr_wei;
  
  	// take node in the scc
  	for( unsigned int node=0; node<SCCs[scc].size(); node++ ){
  		
  		std::cout << "  Scanning node " << nodes[SCCs[scc][node]].name << std::endl;
  		
  		// check the node adjacency list
  		for( unsigned int w=0; w<nodes[ SCCs[scc][node] ].adj.size(); w++ ){
  			
  			
  			std::cout << "   Comparing with node " << nodes[SCCs[scc][node]].adj[w]->name << std::endl;
  			// if not in the same SCC
  			
  			bool sameSCC = false;
  			// std::cout << "size of bool " << sizeof(bool) << std::endl;
  			
  			if( nodes[SCCs[scc][node]].SCC == nodes[SCCs[scc][node]].adj[w]->SCC )
  				sameSCC = true;
  			
  			if( sameSCC )
  				std::cout << "\t" << nodes[SCCs[scc][node]].adj[w]->name << " " << nodes[SCCs[scc][node]].name << " same scc" << std::endl;
  			else{
  				std::cout << "\t" << nodes[SCCs[scc][node]].adj[w]->name << " " << nodes[SCCs[scc][node]].name << " not same scc" << std::endl;
  				
  				// if the SCC of the node in the adj list is already in the adj list of
  				// this SCC
  				bool already_in = false;
  				
  				for( unsigned int j=0; j<curr_adj.size(); j++ ){
  					// if present and the path is shorter substitute the value
  					if( nodes[ SCCs[scc][node] ].adj[w]->SCC == curr_adj[j] ){
  						std::cout << "already present" << std::endl;
  						if( curr_wei[j] > nodes[ SCCs[scc][node] ].W[w] ){
  						std::cout << "substituting " << curr_wei[j] << " with " << nodes[SCCs[scc][node]].W[w] << std::endl;
  						curr_wei[j] = nodes[SCCs[scc][node]].W[w];
  						}
  						already_in = true;
  					}
  				}
  				
  				
  				// for( unsigned int j=0; j<)
  				
  				if( !already_in ){
  					std::cout << "adding " << nodes[SCCs[scc][node]].adj[w]->SCC << " to curr_adj" << std::endl;
  					curr_adj.push_back( nodes[SCCs[scc][node]].adj[w]->SCC );
  					std::cout << "adding " << nodes[SCCs[scc][node]].W[w] << " to curr_adj" << std::endl;
  					curr_wei.push_back( nodes[SCCs[scc][node]].W[w] );
  					}
  			}
  				
  			// if not already in the adj of the SCC
  			// same = false;
  		
  		} // w
  		
  		
  	} // node
  	
  	SCCadj.push_back(curr_adj);
 	SCCweights.push_back(curr_wei);
  } // scc
  
  
  std::cout << "Collapsed graph: " << std::endl;
    for( unsigned int scc=0; scc<SCCadj.size(); scc++){
    	std::cout << "\nSCC number " << scc << std::endl;
  	for( unsigned int i=0; i<SCCadj[scc].size(); i++ ){
  		std::cout << SCCadj[scc][i] << "\t";
  	}
  	std::cout << std::endl;
  	for( unsigned int i=0; i<SCCadj[scc].size(); i++ ){
  		std::cout << SCCweights[scc][i] << "\t";
  	}
  		
  	std::cout << std::endl;
  }
  
  Graph r{ SCCadj, SCCweights };
  
  
  std::cout << "##########################################################" << std::endl;
  return r;
  
  
} // collapse




/*

// function to compare nodes
bool compare(Graph::Node* a, Graph::Node* b){
	return a->get_distance() > b->get_distance();
}


struct heapItem{
	int node;
	double dist;
	heapItem(int i, double d): node{i}, dist{d} {}
};



void Graph::Dijkstra(int s){

std::cout << "##########################################################" << std::endl;
std::cout << "############            DIJKSTRA            ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

// initialize
for(unsigned int i=0; i<nodes.size(); i++){
	nodes[i].set_distance(INFINITY);
	nodes[i].set_parent(nullptr);
}

nodes[s].set_distance( 0.0 );
nodes[s].set_parent( &nodes[s] );

std::vector<Graph::Node*> nod;

for(unsigned int i=0; i<nodes.size(); i++)
	nod.push_back( &nodes[i] );

std::cout << "\ncreating heap... " << std::endl;

Heap<Graph::Node*> min_heap{ nod, &compare };

std::cout << "\noriginal vector heap... " << std::endl;
for(unsigned int i=0; i<nodes.size(); i++)
	std::cout << nod[i]->get_name() << std::endl;

std::cout << "\nheap.front() .. " << std::endl;
std::cout << min_heap.Top()->get_name() << std::endl;
std::cout << std::endl;

int k=0;

while( !min_heap.empty() && k<6 ){
	Graph::Node *u = min_heap.Top();
	min_heap.Pop();
	std::cout << "while on Node " << u->get_name() << std::endl;
	std::cout << "distance " << u->get_distance() << std::endl << std::endl;
	// for( Graph::Node *w : u->adj ){
	for( unsigned int i=0; i<u->adj.size(); i++ ){
		std::cout << "adj: " << u->adj[i]->name << " u->adj[i]->distance " << u->adj[i]->distance << std::endl;
		if( u->adj[i]->distance > (u->distance +  u->W[i]) ){
			std::cout << "u->adj[i]->distance > (u->distance +  u->W[i])" << std::endl;
			
			u->adj[i]->set_distance( u->distance +  u->W[i] );
			
			min_heap.Heapify();
			
			std::cout << "\nheap top " << min_heap.Top()->get_name() << std::endl;
			
			u->adj[i]->set_parent( u );
		}
	}
	k++;

} // while

	std::cout << "DIJKSTRA TERMINATED\n" << std::endl;
	std::cout << "Started on node " << s << std::endl;
	for(unsigned int i=0; i<nodes.size(); i++){
		std::cout << "Node       " << nodes[i].get_name() << std::endl;
		std::cout << "Distance   " << nodes[i].get_distance() << std::endl;
		std::cout << "Parent     " << nodes[i].get_parent()->get_name() << std::endl;
		std::cout << std::endl;
	}
  std::cout << "##########################################################" << std::endl;

} //dijkstra



*/















// BFS search GRAPH
void Graph::bfs(int start=0){

std::cout << "##########################################################" << std::endl;
std::cout << "############               BFS              ##############" << std::endl;
std::cout << "##########################################################" << std::endl;
  
  for(unsigned int i=0; i<nodes.size(); i++){
    nodes[i].col = color::white;
    nodes[i].distance = INFINITY;
    nodes[i].parent = nullptr;
  }

  nodes[start].distance = 0.0;
  nodes[start].col = color::grey;

  std::queue<Graph::Node*> Q;
  Q.push( &nodes[start] );

  while( !Q.empty() ){

    for( Graph::Node *w : Q.front()->adj ){
      if( w->col == color::white ){
	w->distance = Q.front()->distance + 1;
	w->parent = Q.front();
	w->col = color::grey;
	Q.push( w );
      }
    }
    
    Q.front()->col = color::black;
    Q.pop();
  }



  for(unsigned int i=0; i<nodes.size(); i++){
    std::cout << "\nNode: " << nodes[i].name << std::endl;
    std::cout << "Distance: " << nodes[i].distance << std::endl;
    if( nodes[i].parent != nullptr )
      std::cout << "Parent:     " << nodes[i].parent->name << std::endl;
    else
      std::cout << "No Parent" << std::endl;
  }
std::cout << "\n##########################################################" << std::endl;
  
} // bfs







// DFS search GRAPH
void Graph::dfs(){

std::cout << "##########################################################" << std::endl;
std::cout << "############               DFS              ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

  for(unsigned int i=0; i<nodes.size(); i++){
    nodes[i].col = color::white;
    nodes[i].discovery_time = -1;
    nodes[i].final_time = -1;
  }

  int time{0};

  for(unsigned int i=0; i<nodes.size(); i++)
    if( nodes[i].col == color::white )
      time = nodes[i].dfs(time);

  
  for(unsigned int i=0; i<nodes.size(); i++){
    std::cout << "\nNode: " << nodes[i].name << std::endl;
    std::cout << "Discovery: " << nodes[i].discovery_time << std::endl;
    std::cout << "Final:     " << nodes[i].final_time << std::endl;
  }
std::cout << "\n##########################################################" << std::endl;
} // dfs




// DFS search NODE
int Graph::Node::dfs(int time){

  col = color::grey;
  discovery_time = time;
  time++;

  for(unsigned int i=0; i<adj.size(); i++){
    if( adj[i]->col == color::white ){
      time = adj[i]->dfs(time);
    }
  }

  final_time = time;
  // time++;

  return ++time;
} // Node::dfs





/*

void Graph::print_SCC(){

 int i=1;
 for( std::vector<Node> scc : this->SCCs ){
   std::cout << "SCC number " << i << std::endl;
   i++;
   for( Graph::Node n : scc ){
     std::cout << n.get_name() << std::endl;
     // n.print();
   }
 }

}

*/

// constructor with weights vector
Graph::Graph(std::vector<std::vector<int>>& n, std::vector<std::vector<double>>& w){

  // tarjan_done = false;
  
  for(unsigned int i=0; i<n.size(); i++){
    Graph::Node node{(int) i};
    nodes.push_back(node);
  }

  for(unsigned int i=0; i<n.size(); i++){
    std::vector<Graph::Node*> v;
    for( unsigned int j=0; j<n[i].size(); j++){
      v.push_back( &nodes[ n[i][j] ] );
    }
    nodes[i].adj = v;
    nodes[i].W = w[i];
  }
  
} // Graph

// constructor without weights vector
Graph::Graph(std::vector<std::vector<int>>& n){

  // tarjan_done = false;

  for(unsigned int i=0; i<n.size(); i++){
    Graph::Node node{(int) i};
    nodes.push_back(node);
  }
  
  for(unsigned int i=0; i<n.size(); i++){
    std::vector<Graph::Node*> v;
    std::vector<double> w;
    for( unsigned int j=0; j<n[i].size(); j++){
      v.push_back( &nodes[ n[i][j] ] );
      w.push_back( 1.0 );
    }
        nodes[i].adj = v;
        nodes[i].W = w;
   }

} // Graph



/*
// get the number of nodes and the adjacency list of all of them 
void Graph::insert(){
int num_nodes;

	std::cout << "Insert number of nodes: ";
	std::cin >> num_nodes;
	// std::cout << num_nodes << std::endl;


for( int i=0; i<num_nodes; i++){
	Graph::Node node{i};
	nodes.push_back(node);
}


for( int i=0; i<num_nodes; i++){
    std::cout << "Insert adjacency list of NODE " << i << "   (-1 to terminate)" << std::endl;
    // std::cout << "-1 to terminate" << std::endl;
    std::vector<int> list;
    std::vector<double> weights;
    int c = 0;
    while( 1 ){
      std::cin >> c;
      if( c < -1 || c > num_nodes-1 ){
	std::cout << "invalid input" << std::endl;
	// continue;
      }
      else if( c == -1 ){
        std::vector<Node*> ad;
	for(auto j : list){
		Node *pt;
		pt = &nodes[j];
		ad.push_back(pt);
	}
	
	nodes[i].set_adj(ad);
	nodes[i].set_weights(weights);
	break;
      }
      else{
	if( list.empty() ){
	  std::cout << "inserting " << c << std::endl;
	  list.push_back(c);
	  std::cout << "Insert weight:" << std::endl;
	  double w;
	  std::cin >> w;
	  weights.push_back(w);
 	  continue;
	}
	else{
	  int present = 0;
	  for( auto j : list)
	    if( c == j )
	      present = 1;

	  if( !present ){
	    std::cout << "inserting " << c << std::endl;
	    list.push_back(c);
	    std::cout << "Insert weight:" << std::endl;
	    double w;
	    std::cin >> w;
	    weights.push_back(w);
	  }
	  else
	    std::cout << c << " already present" << std::endl;
	    
	}
      }
    }
  }
} // insert

*/


// print all nodes
void Graph::print(){
	for( auto n : nodes )
		n.print_Node();
}






void Graph::Node::print_Node() const { 
		std::cout << "###########   print_Node()  ############" << std::endl;
		std::cout << "Name: " << name << std::endl;
		
		switch(col){
			case color::black:
						std::cout << "Color " << "black" << std::endl;
						break;
			case color::grey:
						std::cout << "Color " << "grey" << std::endl;
						break;
			case color::white:
						std::cout << "Color " << "white" << std::endl;
						break;
		}

		std::cout << "Adjacency list: " << std::endl;
		for( auto n : adj )
			std::cout << n->name << "\t";
		
		std::cout << std::endl;
		std::cout << "Weights list: " << std::endl;
		
		for( auto w : W )
			std::cout << w << "\t";
		std::cout << std::endl;
		
		std::cout << "\nSCC: " << SCC << std::endl;
			
}




// 
std::vector<std::vector<int>> Graph::Tarjan_SCC(){

std::cout << "##########################################################" << std::endl;
std::cout << "############              TARJAN            ##############" << std::endl;
std::cout << "##########################################################" << std::endl;


std::vector<std::vector<int>> SCCs;

for( unsigned int i=0; i<nodes.size(); i++ )
	nodes[i].col = color::white;
	  

std::stack<Graph::Node*> Q;
int time{0};


for( unsigned int i=0; i<nodes.size(); i++ )
  if( nodes[i].col == color::white )
       	time = nodes[i].Tarjan_SCC(time, Q, SCCs);
  
  

for( unsigned int scc=0; scc<SCCs.size(); scc++ ){
   std::cout << "\nSCC: " << scc << std::endl;
   for( unsigned int c=0; c<SCCs[scc].size(); c++){
     std::cout << SCCs[scc][c] << "\t";
   }
   std::cout << std::endl;
 }
 
 
 
 for( unsigned int scc=0; scc<SCCs.size(); scc++ )
   for( unsigned int c=0; c<SCCs[scc].size(); c++)
   	nodes[ SCCs[scc][c] ].SCC = scc;

 
 
 tarjan_done = true;

 std::cout << "\n##########################################################" << std::endl;

return SCCs;
 
} // Tarjan_SCCint








int Graph::Node::Tarjan_SCC(int time, std::stack<Graph::Node *>& Q, std::vector<std::vector<int>>& SCCs){

  discovery_time = time;

  if( col == color::white )
    low_link = time;

  time++;

  Q.push(this);

  col = color::grey;
  

  
  for( Graph::Node* w : adj){
    if( w->col == color::white ){
      time = w->Tarjan_SCC(time, Q, SCCs);
      low_link = low_link < w->low_link ? low_link : w->low_link ;
    }
    else{
      if( w->col == color::grey){
         low_link = low_link < w->low_link ? low_link : w->low_link ;
      }
    }
  }  


  
  col = color::black;
  if( low_link == discovery_time ){

    std::vector<int> temp;
    
    while( Q.top() != this && !Q.empty() ){
      temp.push_back( Q.top()->name );
      Q.pop();
    }

    temp.push_back( Q.top()->name );
    Q.pop();
    SCCs.push_back(temp);
  }

  return time;
} // Node::Tarjan_SCCint





#endif // __GRAPH__
