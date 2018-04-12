#include <Graph>
#include <iostream>
#include <vector>

// creates the graph of a grid from 0 to n_row-1,
// nodes are

// (n_row-1)*(n_col)  .... (n_row-1)*n_col + n_col-1 
// ..
// n_col, n_col+1, ..
// 0,     1,       2, .. n_col-1 

std::vector<std::vector<unsigned int>> manhattan(size_t n_row, size_t n_col){

  std::vector<std::vector<unsigned int>> adj;
  
  for(unsigned int i=0; i<nrow*n_col; i++){
    std::vector<unsigned int> tmp;
    if( (i+1) % (n_col-1) != 0 ){
      tmp.push_back(i+1);
    }
    if( i<(n_rows-1)*n_col )
        tmp.push_back(i+n_col);
    adj.push_back(tmp);
  }

  return adj;
}

int main(){

  std::vector<std::vector<unsigned int>> adj;

  adj = manhattan(3,3);

  for( i : adj){
    std::cout << "adj of node " << i << std::endl;
    for( j : i )
      std::cout << j << " ";
  std::cout << std::endl;
  }

  return 0;
}
