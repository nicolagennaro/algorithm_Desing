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


for( size_t w = 0; w<G.Adj[v].size(); w++ ){\
	
	unsigned int w_node = G.Adj[v][w];
	std::cout << "node " << v << " W " << w << " w_node " << w_node <<std::endl;
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
	std::cout << "on node " << v << std::endl;
	std::vector<unsigned int> SCC;
	while( Q.top() != v /*&& !Q.empty()*/ ){
		std::cout << "pushing  " << Q.top() << std::endl;
		SCC.push_back( Q.top() );
		Q.pop();
	}
	std::cout << "on node " << v << std::endl;
	std::cout << "pushing  " << Q.top() << std::endl;
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
}  
// graph pag 616 a 
  std::vector<std::vector<unsigned int>> Adj{ {1}, {2,4}, {3,6}, {2,7}, {0,5}, {6}, {5,7}, {7} };

  // graph pag 659 Introduction to Algorithms
  // std::vector<std::vector<unsigned int>> Adj{ {1,2}, {2,3}, {1,4}, {4}, {0,3} };
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

  return 0;
}
