#include <Graph.h>
#include <iostream>
#include <queue>
#include <limits>    // for numeric_limits










void bfs( const Graph& G, const unsigned int v ){

size_t number_of_nodes = G.size();

unsigned int *distance = new unsigned int[number_of_nodes];
color *colors = new color[number_of_nodes];
unsigned int *parent = new unsigned int[number_of_nodes];
// unsigned int **parent = new unsigned int*[number_of_nodes];

for( size_t i = 0; i<number_of_nodes; i++ ){
	distance[i] = std::numeric_limits<unsigned int>::max();
	colors[i] = color::white;
	parent[i] = 0;
}

distance[v] = 0;
colors[v] = color::grey;

std::queue<unsigned int> Q;
Q.push(v);


while( !Q.empty() ){
	for( size_t w = 0; w<G.Adj[ Q.front() ].size(); w++ ){
		unsigned int w_node = G.Adj[Q.front()][w];
		if( colors[ w_node ] == color::white ){
			distance[ w_node ] = distance[ Q.front() ] + 1;
			parent[ w_node ] = Q.front();
			colors[ w_node ] = color::grey;
			Q.push( w_node );
		}
	} // for
	
	colors[Q.front()] = color::black;
	Q.pop();

} // while

std::cout << "\n#################################" << std::endl;
std::cout << "BFS starting from node " << v << std::endl;
std::cout << "\n#################################" << std::endl;

for( size_t i = 0; i<number_of_nodes; i++ ){
	std::cout << "Node:     " << i << std::endl;
	std::cout << "Color:    " << colors[i] <<std::endl;
	std::cout << "Distance: " << distance[i] << std::endl;
	std::cout << "Parent:   " << parent[i] << std::endl;
	std::cout << std::endl;
}

delete[] colors;
delete[] distance;
delete[] parent;

} // bfs



int main(){


  // graph pag 116 dasgupta
  std::vector<std::vector<unsigned int>> Adj{ {1,2}, {2,3,4}, {1,3,4}, {}, {3} };
  Graph G{Adj};
  
  G.print();
  bfs(G, 0);

  return 0;
}
