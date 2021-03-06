#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>
#include <../Heap/Heap.h>



class Graph{
	enum class color {white, grey, black};

	class Node;

	std::vector<Node> nodes;
        std::vector<std::vector<int>> SCCs;

        public:
		Graph() { this->insert(); }
		Graph(std::vector<std::vector<int>>&, std::vector<std::vector<double>>& );
		// Graph(std::vector<Node> &v): nodes{v} {}
		
		void print();
		void insert();

		void dfs();
		void bfs(int);

		void Tarjan_SCC();
		
		void Dijkstra(int);

		Graph collapse();
  		// void set_SCC(){ SCCs = this->Tarjan_SCC(); }
  		void print_SCC();
};




class Graph::Node{
			int name;
			
			int SCC;
			color col;
			
			
			int discovery_time;
			int final_time;
			int low_link;
			
			Node *parent;		// dijkstra
			double distance;	// bfs, dijkstra
			
			std::vector<Node*> adj;
			std::vector<double> W;
		
		public:
			Node(int n): name{n}, col{color::white}, discovery_time{-1}, final_time{-1}, low_link{-1} {}

			void print_Node(){ 
				std::cout << "###########   print_Node()  ############" << std::endl;
				std::cout << "Name " << name << std::endl;
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
				
			}

	  		// void print(){ std::cout << "Name " << name << std::endl; }
	  		int get_name(){ return name; }
	  		
			void set_adj(std::vector<Node*> &v){ adj = v; }
			void set_weights(std::vector<double> &v){ W = v; }
			
			color get_col(){ return col; }
			void set_col(color c){ col = c; }
			
			int get_disc(){ return discovery_time; }
			void set_disc(int d){ discovery_time = d; }
			
			void set_fin(int f){ final_time = f; }
			int get_fin(){ return final_time; }
			
			void set_ll(int l){ low_link = l; }
			int get_ll(){ return low_link; }
			
	                void set_distance(double d){ distance =d; };
	                double get_distance(){ return distance; }
	                
	                void set_parent(Node *p){ parent = p;}
	                Node* get_parent(){ return parent; }
	                
	                bool operator==(const Node& other){ return this->name == other.name; }
	  		bool operator!=(const Node& other){ return !(*this == other); }
	                
	                // compare distances for dijkstra
	                bool operator<(const Node& other){ return this->distance < other.distance; }
	               	
			int dfs(int);
			
			
	                int Tarjan_SCC(int, std::stack<Graph::Node>&, std::vector<std::vector<int>> &);

			friend void Graph::bfs(int); // bfs must use adj[]
			friend Graph Graph::collapse();
			friend void Graph::Dijkstra(int);
	                	  
	  		

			
			
 };



class Graph Graph::collapse(){

std::cout << "##########################################################" << std::endl;
std::cout << "############            COLLAPSE            ##############" << std::endl;
std::cout << "##########################################################" << std::endl;

  for( unsigned int scc=0; scc<SCCs.size(); scc++){
  	for( unsigned int node=0; node<SCCs[scc].size(); node++ ){
  		nodes[ SCCs[scc][node] ].SCC = scc;
  	}
  }
  
  for( unsigned int i=0; i<nodes.size(); i++ ){
  	std::cout << "Node " << nodes[i].name << std::endl;
  	std::cout << "SCC " << nodes[i].SCC << std::endl;
  }
  
  // for all nodes in the SCC, temp adj for SCC compute adj to nodes outside
  // if the edge not present add it to the vector of the adj of the SCC
  
  std::vector<int> SCCadj;
  
  for( unsigned int scc=0; scc<SCCs.size(); scc++){
  
  	std::cout << "\nscanning SCC " << scc << std::endl;
  	std::vector<int> adj;
  	std::vector<double> wei;
  
  	// take node in the scc
  	for( unsigned int node=0; node<SCCs[scc].size(); node++ ){
  		
  		// check the node adjacency list
  		for( unsigned int w=0; w<nodes[node].adj.size(); w++ ){
  			
  			
  			// if not in the same SCC
  			
  			bool same = false;
  			std::cout << "size of bool " << sizeof(bool) << std::endl;
  			unsigned int p;
  			for( p=0; p<SCCs[scc].size(); p++){
  				if( p == scc )
  					continue;
  				if( nodes[p].get_name() == nodes[node].get_name() ){
  					same = true;
  					break;
  				}
  			}
  			if( same )
  				std::cout << node << " " << p << " same scc" << std::endl;
  			else
  				std::cout << node << " " << p << " not same scc" << std::endl;
  				
  			// if not already in the adj of the SCC
  			same = false;
  		
  		} // w
  		
  		
  	} // node
  
  } // scc
  
  std::vector<std::vector<int>> adj{ {1}, {0} };
  std::vector<std::vector<double>> w{ {1.0}, {2.0} };
  Graph r{ adj, w };
  
  
  std::cout << "##########################################################" << std::endl;
  return r;
  
  
} // collapse












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

Heap<float> min_heap{};

  std::cout << "##########################################################" << std::endl;

} //dijkstra



















// BFS search GRAPH
void Graph::bfs(int start=0){

std::cout << "##########################################################" << std::endl;
std::cout << "############               BFS              ##############" << std::endl;
std::cout << "##########################################################" << std::endl;
  
  for(unsigned int i=0; i<nodes.size(); i++){
    nodes[i].set_col(color::white);
    nodes[i].set_distance(INFINITY);
    nodes[i].set_parent(NULL);
  }

  nodes[start].set_distance(0.0);
  nodes[start].set_col(color::grey);

  std::queue<Graph::Node*> Q;
  Q.push( &nodes[start] );

  while( !Q.empty() ){
    /* Graph::Node *curr = Q.front(); */
    /* for( unsigned int i=0; i < curr->adj.size(); i++ ){ */
    /*   if( curr->adj[i]->get_col() == color::white ){ */
    /* 	curr->adj[i]->set_distance(curr->get_distance() + 1); */
    /* 	curr->adj[i]->set_parent(curr); */
    /* 	curr->adj[i]->set_col(color::grey); */
    /* 	Q.push(curr->adj[i]); */
    /*   } */
    /* } */
    for( Graph::Node *w : Q.front()->adj ){
      if( w->get_col() == color::white ){
	w->set_distance( Q.front()->get_distance() + 1 );
	w->set_parent( Q.front() );
	w->set_col(color::grey);
	Q.push( w );
      }
    }
    
    Q.front()->set_col(color::black);
    Q.pop();
  }



  for(unsigned int i=0; i<nodes.size(); i++){
    std::cout << "\nNode: " << nodes[i].get_name() << std::endl;
    std::cout << "Distance: " << nodes[i].get_distance() << std::endl;
    if( nodes[i].get_parent() != NULL)
      std::cout << "Parent:     " << nodes[i].get_parent()->get_name() << std::endl;
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
    nodes[i].set_col(color::white);
    nodes[i].set_disc(-1);
    nodes[i].set_fin(-1);
  }

  //for(unsigned int i=0; i<nodes.size(); i++)
  //  nodes[i].print_Node();



  int time{0};

  for(unsigned int i=0; i<nodes.size(); i++)
    if( nodes[i].get_col() == color::white )
      time = nodes[i].dfs(time);

  
  for(unsigned int i=0; i<nodes.size(); i++){
    std::cout << "\nNode: " << nodes[i].get_name() << std::endl;
    std::cout << "Discovery: " << nodes[i].get_disc() << std::endl;
    std::cout << "Final:     " << nodes[i].get_fin() << std::endl;
  }
std::cout << "\n##########################################################" << std::endl;
} // dfs


// DFS search NODE
int Graph::Node::dfs(int time){

  this->set_col(color::grey);
  this->set_disc(time);
  time++;

  for(unsigned int i=0; i<adj.size(); i++){
    if( adj[i]->get_col() == color::white ){
      time = adj[i]->dfs(time);
    }
  }

  this->set_fin(time);
  time++;

  return time;

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


Graph::Graph(std::vector<std::vector<int>>& n, std::vector<std::vector<double>>& w){

  for(unsigned int i=0; i<n.size(); i++){
    Graph::Node node{(int) i};
    nodes.push_back(node);
  }

  for(unsigned int i=0; i<n.size(); i++){
    std::vector<Graph::Node*> v;
    for( unsigned int j=0; j<n[i].size(); j++){
      v.push_back( &nodes[ n[i][j] ] );
    }
    nodes[i].set_adj( v );
    nodes[i].set_weights( w[i] );
  }
  
} // Graph



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




// print all nodes
void Graph::print(){
	for( auto n : nodes )
		n.print_Node();
}












void Graph::Tarjan_SCC(){
  
std::stack<Graph::Node> Q;
int time{0};

std::cout << "##########################################################" << std::endl;
std::cout << "############              TARJAN            ##############" << std::endl;
std::cout << "##########################################################" << std::endl;
for( unsigned int i=0; i<nodes.size(); i++ ){
  #ifdef DEBUG
  std::cout << "Graph::Tarjan_SCC scanning node " << nodes[i].get_name() << std::endl;
  #endif
  if( nodes[i].get_col() == color::white ){
    #ifdef DEBUG
       	std::cout << "color is white " << std::endl;
    #endif
       	time = nodes[i].Tarjan_SCC(time, Q, SCCs);
  }
}

 for( unsigned int scc=0; scc<SCCs.size(); scc++ ){
   std::cout << "\nSCC: " << scc << std::endl;
   for( unsigned int c=0; c<SCCs[scc].size(); c++){
     std::cout << SCCs[scc][c] << " ";
   }
   std::cout << std::endl;
 }

std::cout << "\n##########################################################" << std::endl;
 
} // Tarjan_SCCint








int Graph::Node::Tarjan_SCC(int time, std::stack<Graph::Node>& Q, std::vector<std::vector<int>>& SCCs){
  #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->name << std::endl;
  #endif
  //this->print_all();
  this->set_disc(time);
  if( this->get_col() == color::white ){
    this->set_ll(time);
    }
  time++;
  // if( this->get_col() == color::white )
  #ifdef DEBUG
  std::cout << "discovery time: " << this->get_disc() << std::endl;
  std::cout << "low link: " << this->get_ll() << std::endl;
  #endif
  Q.push(*this);
  this->set_col(color::grey);
  

  
  for( Graph::Node* w : adj){
    if( w->get_col() == color::white ){
      time = w->Tarjan_SCC(time, Q, SCCs);
      this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
    }
    else{
      if( w->get_col() == color::grey){
        this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "#Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
      }
    }
  }  


  
  this->set_col(color::black);
  if( this->get_ll() == this->discovery_time ){
    #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " lowlink = discovery time " << this->get_disc() << this->get_ll() << std::endl;
    #endif
    std::vector<int> temp;
    while( Q.top() != *this && !Q.empty() ){
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
      temp.push_back( Q.top().get_name() );
      Q.pop();
    }
    
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
	temp.push_back( Q.top().get_name() );
    Q.pop();
    SCCs.push_back(temp);
  }

  return time;
} // Node::Tarjan_SCCint





#endif // __GRAPH__

/*

void Graph::Tarjan_SCC(){
  
std::stack<Graph::Node> Q;
int time{0};

std::cout << "##########################################################" << std::endl;
for( unsigned int i=0; i<nodes.size(); i++ ){
Node * n = &nodes[i];
  #ifdef DEBUG
  std::cout << "Graph::Tarjan_SCC scanning node " << n->get_name() << std::endl;
  #endif
  if( n->get_col() == color::white ){
    #ifdef DEBUG
       	std::cout << "color is white " << std::endl;
    #endif
       	time = n->Tarjan_SCC(time, Q, SCCs);
  }
}

for( auto n : nodes )
	n.print_all();

} // Tarjan_SCC



int Graph::Node::Tarjan_SCC(int time, std::stack<Graph::Node>& Q, std::vector<std::vector<Graph::Node>>& SCCs){
  #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->name << std::endl;
  #endif
  this->print_all();
  this->set_disc(time);
  if( this->get_col() == color::white ){
    this->set_ll(time);
    }
  time++;
  // if( this->get_col() == color::white )
  #ifdef DEBUG
  std::cout << "discovery time: " << this->get_disc() << std::endl;
  std::cout << "low link: " << this->get_ll() << std::endl;
  #endif
  Q.push(*this);
  this->set_col(color::grey);
  

  
  for( Graph::Node* w : adj){
    if( w->get_col() == color::white ){
      time = w->Tarjan_SCC(time, Q, SCCs);
      this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
    }
    else{
      if( w->get_col() == color::grey){
        this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "#Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
      }
    }
  }  


  
  this->set_col(color::black);
  if( this->get_ll() == this->discovery_time ){
    #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " lowlink = discovery time " << this->get_disc() << this->get_ll() << std::endl;
    #endif
    std::vector<Node> temp;
    while( Q.top() != *this && !Q.empty() ){
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
      temp.push_back(Q.top());
      Q.pop();
    }
    
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
    temp.push_back(Q.top());
    Q.pop();
    SCCs.push_back(temp);
  }

  return time;
} // Node::Tarjan_SCC

*/



