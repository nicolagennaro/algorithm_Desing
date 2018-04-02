#include <iostream>
#include <stack>
#include <queue>



class Graph{
	enum class color {white, grey, black};

	class Node{
			int name;
			color col;
			int discovery_time;
			int final_time;
			int low_link;
			std::vector<Node*> adj;
		
		public:
			Node(int n): name{n}, col{color::white}, discovery_time{-1}, final_time{-1}, low_link{-1} {}

			void print_all(){ 
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
					std::cout << n->name << std::endl;
				
			}

	  		void print(){ std::cout << "Name " << name << std::endl; }
	  		int get_name(){ return name; }
	  		
			void set_adj(std::vector<Node*> &v){ adj = v; }
			
			color get_col(){ return col; }
			void set_col(color c){ col = c; }
			
			int get_disc(){ return discovery_time; }
			void set_disc(int d){ discovery_time = d; }
			
			void set_fin(int f){ final_time = f; }
			
			void set_ll(int l){ low_link = l; }
			int get_ll(){ return low_link; }
			
	                int Tarjan_SCC(int, std::stack<Graph::Node>&, std::vector<std::vector<Graph::Node>>&);
	  
	  		bool operator==(const Node& other){ return this->name == other.name; }
	  		bool operator!=(const Node& other){ return !(*this == other); }
	};


	std::vector<Node> nodes;
        std::vector<std::vector<Node>> SCCs;

        public:
		Graph() { this->insert(); }
		// Graph(std::vector<Node> &v): nodes{v} {}
		
		void print();
		void insert();
		
		void Tarjan_SCC();
		
  		// void set_SCC(){ SCCs = this->Tarjan_SCC(); }
  		void print_SCC();
};


void Graph::print_SCC(){

 int i=1;
 for( std::vector<Node> scc : this->SCCs ){
   std::cout << "SCC number " << i << std::endl;
   i++;
   for( Graph::Node n : scc ){
     n.print();
   }
 }

}



// get the number of nodes and the adjacency list of all of them 
void Graph::insert(){
int num_nodes;

	std::cout << "Insert number of nodes";
	std::cin >> num_nodes;
	// std::cout << num_nodes << std::endl;


for( int i=0; i<num_nodes; i++){
	Graph::Node node{i};
	nodes.push_back(node);
}


for( int i=0; i<num_nodes; i++){
    std::cout << "Insert adjacency list of NODE " << i << std::endl;
    std::cout << "-1 to terminate" << std::endl;
    std::vector<int> list;
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
	break;
      }
      else{
	if( list.empty() ){
	  std::cout << "inserting " << c << std::endl;
	  list.push_back(c);
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
		n.print();
}





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








int main(){

Graph g;
g.print();

g.Tarjan_SCC();
g.print_SCC();
 
  return 0;
}
