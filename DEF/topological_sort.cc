#include <Graph.h>
#include <iostream>
#include <stack>
#include <limits>    // for numeric_limits



// TARJAN_REAL
unsigned int Tarjan_SCC_real( const Graph& G, size_t v, unsigned int time, color *colors, unsigned int *d_time, unsigned int *ll, std::stack<unsigned int>& Q, std::vector<std::vector<unsigned int>>& SCCs){

d_time[v] = time;
ll[v] = time;

time++;

colors[v] = color::grey;
Q.push(v);


for( size_t w = 0; w<G.Adj[v].size(); w++ ){
	
	unsigned int w_node = G.Adj[v][w];
	if( colors[ w_node ] == color::white ){
		time = Tarjan_SCC_real( G, w_node , time,  colors, d_time, ll, Q, SCCs );
		ll[v] = ll[v] < ll[ w_node ] ? ll[v] : ll[ w_node ];
	}
	else{
		if( colors[ w_node ] == color::grey ){
			ll[v] = ll[v] < ll[w_node] ? ll[v] : ll[w_node];
		}
	}	
}

colors[v] = color::black;

if( ll[v] == d_time[v] ){

	std::vector<unsigned int> SCC;
	
	while( Q.top() != v /*&& !Q.empty()*/ ){
		SCC.push_back( Q.top() );
		Q.pop();
	}
	SCC.push_back( Q.top() );
	Q.pop();
	
	SCCs.push_back(SCC);
}

return time;
}

// TARJAN
std::vector<std::vector<unsigned int>> Tarjan_SCC( const Graph& G ){

size_t number_of_nodes = G.size();

unsigned int *discovery_time = new unsigned int[number_of_nodes];
color *colors = new color[number_of_nodes];
unsigned int *low_link = new unsigned int[number_of_nodes];



for( size_t i = 0; i<number_of_nodes; i++ ){
	discovery_time[i] = std::numeric_limits<unsigned int>::max();
	colors[i] = color::white;
	low_link[i] = std::numeric_limits<unsigned int>::max();
}

std::stack<unsigned int> Q;
std::vector<std::vector<unsigned int>> SCCs;
unsigned int time{0};

for( size_t v = 0; v<number_of_nodes; v++ ){
	if( colors[v] == color::white ){
		time = Tarjan_SCC_real( G, v, time, colors, discovery_time, low_link, Q, SCCs );
	}
}


return SCCs;
} // tarjan_SCC





// return a pair Node, S(Node), only for collapsed graphs
std::vector<std::pair<unsigned int, unsigned int>> topological_sort( const Graph G ){

// compute the collapsed graph
// compute the SCCs with tarjan on the collapsed

}




// returns the collapsed graph
class Graph collapse( const Graph& G ){

	// compute the sccs
	std::vector<std::vector<unsigned int>> SCCs;
	SCCs = Tarjan_SCC( G );


	// map node->SCC, can be also one vector
	std::vector<std::pair<unsigned int, unsigned int>> Node2SCC;
	for( unsigned int i = 0; i<G.size(); i++ ){
		std::pair<unsigned int, unsigned int> p;
		for( unsigned int scc=0; scc<SCCs.size(); scc++ )
			for( unsigned int w : SCCs[scc] ){
				if( w == i ){
					p.first = w;
					p.second = scc;
					goto PUSH;
				}
			}
		PUSH:	
		Node2SCC.push_back(p);
	}

	for( std::pair<unsigned int, unsigned int> p : Node2SCC){
		std::cout << p.first << " " << p.second << std::endl;
	}

	/*
	// vector to create the collapsed graph
	std::vector<std::vector<unsigned int>> SCCadj;

	// for all the SCCs
	for( unsigned int scc=0; scc<SCCs.size(); scc++){
		std::vector<unsigned int> temp_adj;
		
		// for all the nodes in the SCC
		for( unsigned int w=0; w<SCCs[scc].size(); w++ ){
			
			
			bool sameSCC = false;
			bool already_in = false;
			
			// check if the nodes in the adj list of SCCs[scc][w] are in the same scc or the node 
			// is already in the list
			
			for( unsigned int comp = 0; comp<SCCs[scc].size())
			
			
		
		} // w
	} // scc
	*/
	

return Graph{SCCs};
} // collapse








int main(){

{
  // graph pag 116 dasgupta
  std::vector<std::vector<unsigned int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  Graph G{Adj};
  
  G.print();
  std::vector<std::vector<unsigned int>> SCCs;
  
  SCCs = Tarjan_SCC(G);
  
  std::cout << "Tarjan: " << std::endl;
  for( size_t i = 0; i<SCCs.size(); i++){
  	std::cout << "SCC " << i << std::endl;
  	for( size_t j = 0; j<SCCs[i].size(); j++)
  		std::cout << SCCs[i][j] << "\t";
  	std::cout << std::endl;
  }
  Graph G1;
  G1 = collapse(G);
}  


  return 0;
}
