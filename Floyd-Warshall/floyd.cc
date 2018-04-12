#include <Graph.h>
#include <Strassen.h>
#include <iostream>
#include <vector>


#define MIN(X,Y) (((X)<(Y)) ? (X) : (Y))



double* weight_matrix(Graph G&, std::vector<std::vector<double>>& W){

  size_t size = G.size();

  double adj_mat = new double[size*size];

  for(unsigned int i=0; i<size; i++)
    for(unsigned int j=0; j<size; j++)
      adj_mat[i*size + j] = INFINITY;

  for(unsigned int i=0; i<G.size(); i++)
    for(unsigned int j=0; j<G.Adj[i].size(); j++)
      adj_mat[ i*size + G.Adj[i][j] ] = W[i][j];

  return adj_mat;
}


double* floyd_warshall(Graph G&, std::vector<std::vector<double>>& W){
  double *old_mat, *new_mat;

  size_t size = G.size();


  old_mat = weight_matrix(G, W);

  std::cout << "\nWeight matrix\n" << std::endl;
  print_mat(old_mat, size);
  
  new_mat = new double[size*size];

  for(unsigned int k=0; k<size; k++){
    for(unsigned int i=0; i<size; i++){
      for(unsigned int j=0; j<size; j++){
	new_mat[i][j] = MIN(old_mat[i][j], old_mat[i][k] + old_mat[k][j]);
      }
    }

    std::cout << "\nstep " << k << "\nNEW MATRIX\n" << std::endl;
    print_mat(new_mat, size);
    
    double *temp = old_mat;
    old_mat = new_mat;
    new_mat = temp;
  }

  return new_mat;
}



int main(){


  std::vector<std::vector<int>> Adj{ {2}, {0,2}, {3}, {1} };
  for( std::vector<int> i : Adj )
    for( auto j : i )
      std::cout << j << std::endl;
  
  std::vector<std::vector<double>> Weights{ {-2.0}, {4.0,3.0}, {2.0}, {-1.0} };


  Graph g{Adj};
  g.print();

  double *fw = new double[g.size()*g.size()];

  std::cout << "Finale matrix" << std::endl;
  print_mat(fw);
  
  return 0;
}
