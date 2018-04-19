#include <../DEF/Graph.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <limits>



#define MIN(X,Y) (((X)<(Y)) ? (X) : (Y))


template<typename T>
void print_mat( T* A, const size_t size){
  size_t i,j;
  for(i=0; i<size; i++){
    for(j=0; j<size; j++)
      std::cout << A[ i*size + j ] << "\t";
    std::cout << std::endl;
  }
}




double* weight_matrix(Graph& G, std::vector<std::vector<double>>& W){

  size_t size = G.size();

  double *adj_mat = new double[size*size];

  for(unsigned int i=0; i<size; i++)
    for(unsigned int j=0; j<size; j++){
    	if( i==j)
    		adj_mat[i*size + j] = 0.0;
    	else
      		adj_mat[i*size + j] = INFINITY;
    }
    
  

  for(unsigned int i=0; i<G.size(); i++)
    for(unsigned int j=0; j<G.Adj[i].size(); j++)
      adj_mat[ i*size + G.Adj[i][j] ] = W[i][j];

  return adj_mat;
}





double* floyd_warshall(Graph& G, std::vector<std::vector<double>>& W){
  double *old_mat, *new_mat;

  size_t size = G.size();


  old_mat = weight_matrix(G, W);

  std::cout << "\nWeight matrix\n" << std::endl;
  print_mat(old_mat, size);
  
  unsigned int *pi_old, *pi_new;
  
  pi_old = G.adj_matrix();
  
  std::cout << "\nAdj matrix\n" << std::endl;
  print_mat(pi_old, size);
 
  for( unsigned int i=0; i<size; i++ ){
  	for(unsigned int j=0; j<size; j++){
  		if( i==j || pi_old[ i*size + j ] == 0 )
  			pi_old[ i*size + j ] = std::numeric_limits<unsigned int>::max();
  		else
  			pi_old[ i*size + j ] = i;
  	}
  }

  std::cout << "\nPI_0  matrix\n" << std::endl;
  print_mat(pi_old, size);


  new_mat = new double[size*size];
  pi_new = new unsigned int[size*size];


  for(unsigned int k=0; k<size; k++){
    for(unsigned int i=0; i<size; i++){
      for(unsigned int j=0; j<size; j++){
	// new_mat[i*size + j] = MIN(old_mat[i*size + j], old_mat[i*size + k] + old_mat[k*size + j]);
	if( old_mat[i*size + j] >  old_mat[i*size + k] + old_mat[k*size + j] ){
		new_mat[ i*size + j ] = old_mat[i*size + k] + old_mat[k*size + j];
		pi_new[ i*size + j ] = pi_old[ k*size + j ];
	}
      }
    }

    std::cout << "\nstep " << k << "\nNEW MATRIX\n" << std::endl;
    print_mat(new_mat, size);
    
    std::cout << "\nNEW PI\n" << std::endl;
    print_mat(pi_new, size);
    
    double *temp = old_mat;
    old_mat = new_mat;
    new_mat = temp;
    
    unsigned int *tmp = pi_old;
    pi_old = pi_new;
    pi_new = tmp;

  }

  return old_mat;
}



int main(){


  std::vector<std::vector<unsigned int>> Adj{ {2}, {0,2}, {3}, {1} };
  for( std::vector<unsigned int> i : Adj )
    for( auto j : i )
      std::cout << j << std::endl;
  
  std::vector<std::vector<double>> Weights{ {-2.0}, {4.0,3.0}, {2.0}, {-1.0} };

std::cout << "MIN(1,2) " << MIN(1,2) << std::endl;

  Graph g{Adj};
  g.print();

  double *fw = new double[g.size()*g.size()];

  fw = floyd_warshall(g, Weights);

  std::cout << "\n\nFinal matrix" << std::endl;
  print_mat(fw, g.size() );
  
  return 0;
}
