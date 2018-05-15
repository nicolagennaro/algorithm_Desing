#include <iostream>



bool LTl(char* T1, size_t l1, char* T2, size_t l2, size_t l, size_t start=1){
  size_t k=1;
  while( k<= l1 && k<=l2 && k<=l ){
    if( T1[k] > T2[k] )
      return false;
    else
      if( T1[k] < T2[k] )
	return true;
    k++;
  }
  return k==l1+1 || k==l+1;
}


// SA contains the starting index of the suffix of T

SA_matching( char* T, size_t len_T, size_t* SA, char* P, size_t len_P){

  size_t Lp, Rp;
  
  if( LTl(P, lP, T+SA[1], lT-SA[1], lP) )
    Lp = 0;
  else if( LTl( T+SA[len_T], len_T - SA[len_T], P, lP, lP ) )
    Lp = len_T + 1;
  else{
    size_t L = 1, R = len_T;
    while( R-L > 1 ){

    }

  }

}


int main(){


  return 0;
}
