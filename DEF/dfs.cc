#include <Graph.h>
#include <iostream>
#include <queue>
#include <limits>    // for numeric_limits




unsigned int dfs_real( const Graph& G, size_t v, unsigned int time, color *colors, unsigned int *d_time, unsigned int *f_time, unsigned int *parent){

colors[v] = color::black;
d_time[v] = time;
time++;

for( size_t w = 0; w<G.Adj[v].size(); w++ ){
	unsigned int w_node = G.Adj[v][w];
	if( colors[ w_node ] == color::white ){
		parent[ w_node ] = v;
		time = dfs_real( G, w_node , time,  colors, d_time, f_time, parent );
	}
}

f_time[v] = time;
time++;

return time;
}







void dfs( const Graph& G ){

size_t number_of_nodes = G.size();

unsigned int *discovery_time = new unsigned int[number_of_nodes];
unsigned int *final_time = new unsigned int[number_of_nodes];
color *colors = new color[number_of_nodes];
unsigned int *parent = new unsigned int[number_of_nodes];
// or it can be
// unsigned int **parent = new unsigned int*[];


for( size_t i = 0; i<number_of_nodes; i++ ){
	discovery_time[i] = std::numeric_limits<unsigned int>::max();
	final_time[i] = std::numeric_limits<unsigned int>::max();
	colors[i] = color::white;
	parent[i] = 0;
}

unsigned int time{0};

for( size_t v = 0; v<number_of_nodes; v++ ){
	if( colors[v] == color::white ){
		time = dfs_real( G, v, time, colors, discovery_time, final_time, parent );
	}
}


std::cout << "\n#################################" << std::endl;
std::cout << "#######       DFS         #######" << std::endl;
std::cout << "#################################" << std::endl;

for( size_t i = 0; i<number_of_nodes; i++ ){
	std::cout << "Node:           " << i << std::endl;
	std::cout << "Color:          " << colors[i] <<std::endl;
	std::cout << "Discovery time: " << discovery_time[i] << std::endl;
	std::cout << "Final time:     " << final_time[i] << std::endl;
	std::cout << "Parent:         " << parent[i] << std::endl;
	std::cout << std::endl;
}

delete[] colors;
delete[] discovery_time;
delete[] final_time;
delete[] parent;

} // dfs



int main(){


  // graph pag 116 dasgupta
  std::vector<std::vector<unsigned int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  Graph G{Adj};
  
  G.print();
  dfs(G);

  return 0;
}
