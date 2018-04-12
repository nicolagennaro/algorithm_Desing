#include <Graph.h>
#include <BinaryHeap.h>
#include <iostream>
#include <vector>
#include <cmath>


#define N_ROWS 3
#define N_COLS 3



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



// given two nodes its the euclidean distance between the two indices
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
  unsigned int **parent = new unsigned int*[size];

  for( unsigned int i=0; i<size; i++){
    distance[i] = INFINITY;
    h_bar[i] = INFINITY;
    parent[i] = nullptr;
  }

  distance[s] = 0.0;
  // parent[s] = &G.
  h_bar[s] = h(s, t);

  std::cout << "h_bar[s]" << std::endl;
  std::cout << h_bar[s] << std::endl;

  // BinaryHeap
  
} // Astar




int main(){

  std::vector<std::vector<unsigned int>> adj;

  adj = manhattan(N_ROWS, N_COLS);

  Graph g{adj};

  g.print();

  double d;
  d = heuristic(4,0);
  
  std::cout << d << std::endl;
  
  
  return 0;
}
