#include <iostream>
#include <vector>
#include <LinkedList.h>


#define MAX(x,y) (x)>(y) ? x : y



char* revert_string(char* str, size_t len){
  char* rev = new char[len];
  rev = rev-1;
  for(size_t i=1; i<=len; i++)
    rev[i] = str[len + 1 - i ];

  return rev;
}




size_t* compute_BCH(char* P, size_t lP, char* alphabet, size_t alpha_len){

  size_t *bch = new size_t[alpha_len];
  bch=bch-1;
  
  for(size_t i=1; i<=alpha_len; i++)
    bch[i] = 0;

  size_t j;
  for(size_t i=1; i<=lP-1; i++){
    for( j=1; j<=alpha_len; j++)
      if( alphabet[j] == P[i] )
	break;
    bch[j] = i;
  }

  std::cout << "Bad Char Heuristic:" << std::endl;
  for(size_t i=1; i<=alpha_len; i++)
    std::cout << bch[i] << " ";
  std::cout << std::endl;

  return bch;
}




// compute Z(i) = the length of the longest prefix of S[i, ..., lP]
// that is also a prefix for S
size_t* compute_Z(char* P, size_t lP){

  char *S;
  S = revert_string(P, lP);
  
  std::cout << "reverse string" << std::endl;
  for(size_t i=1; i<=lP; i++)
    std::cout << S[i] << " ";
  std::cout << std::endl;

  size_t *Z = new size_t[lP];
  Z = Z-1;
  
  size_t j=2;
  size_t i=3;
  size_t k;

  Z[1] = lP; // or the whole string ????
  // Z[2] = 0;

  k = 0;
  while( S[ k+2 ] == S[ k+1 ] && k<lP )
    k++;
  
  Z[2] = k;

  std::cout << "Z2: " << Z[2] << std::endl;
  
  while( i<=lP ){
    std::cout << "\n\ni: " << i  << std::endl;
    if( i >= j+Z[j] ){
      std::cout << "i >= j+Z[j]" << std::endl;
      std::cout << "j " << j << " ::: Zj " << Z[j] << std::endl;
      // compute Z[i] explicitely
      k=0;
      while( S[k+1] == S[k+i] && k+i<=lP )
	k++;
      
      std::cout << "k" << k << std::endl;
      Z[i] = k;
    }
    else{  // if i < j + Z[j] then there is a prefix that start at j of length Z[j] that 
    		// goes beyond the current index i. So we can start from the position at
    		// j + Z[j] knowing that Z[j] chars are already equal
      std::cout << "i < j+Z[j]" << std::endl;
      std::cout << "j " << j << " ::: Zj " << Z[j] << std::endl;
      Z[i] = Z[ i-j+1 ];
      if( Z[i] >= Z[j] -(i-j) ){
	std::cout << "Z[i] >= Z[j] -(i-j)" << std::endl;
	std::cout << " extend the tail of Z[i]" << std::endl;
	k=Z[j] + j - i + 1;
	while( S[ k ] == S[ i+ k ] && (i + k) <= lP )
	  k++;
	std::cout << "k " << k << std::endl;
	std::cout << "j " << j << std::endl;
	Z[i] = k - (i-j);
	// Z[i] = k;
        std::cout << "Z[i] " << Z[i] << std::endl;
      }
    }

    if( j+Z[j] < i+Z[i] ){
    	std::cout << "j+Z[j] < i+Z[i]" << std::endl;
      	j = i;
    }
    i++;
  }

  for( size_t i=1; i<=lP; i++)
    std::cout << Z[i] << " ";
  std::cout << std::endl;

  return Z;
}





size_t* compute_L(char* P, size_t lP, size_t* N){

  size_t* L = new size_t[lP];
  L = L-1;
  
  size_t i;
  for( i=1; i<=lP; i++)
    L[i] = 0;  

  for( size_t j=1; j<=lP; j++ ){
    i = lP - N[j] + 1;
    L[i] = j;
  }

  return L;
}


size_t* compute_H(char* P, size_t lP, size_t* N){

  size_t* H = new size_t[lP];
  H = H-1;
  
  size_t k=0;
  for( size_t i=1; i<=lP; i++){
      //for( size_t i=1; i<=lP-1; i++){
    if( N[i] == i)
      k = i;
    H[ lP - i + 1 ] = k;
  }

  return H;
}




LinkedList<size_t> Boyer_Moore(char* T, size_t lT, char* P, size_t lP, char *alphabet, size_t alpha_len){

  for(size_t i=1; i<= lT; i++)
    std::cout << T[i] << " ";
  std::cout << std::endl;

  for(size_t i=1; i<= lP; i++)
    std::cout << P[i] << " ";
  std::cout << std::endl;

  size_t* bch;
  size_t* Z;
  
  bch = compute_BCH(P, lP, alphabet, alpha_len);

  Z = compute_Z(P, lP);

  size_t* N = new size_t[lP];
  N = N-1;

  for( size_t i=1; i<=lP; i++)
    N[i] = Z[lP - i + 1];

  delete[] (Z+1);

  
  std::cout << "N" << std::endl;
  for(size_t i=1; i<=lP; i++)
    std::cout << N[i] << " ";
  std::cout << std::endl;

  size_t *H, *L;

  H = compute_H(P, lP, N);

  std::cout << "H" << std::endl;
  for(size_t i=1; i<=lP; i++)
    std::cout << H[i] << " ";
  std::cout << std::endl;

  L = compute_L(P, lP, N);

  std::cout << "L" << std::endl;
  for(size_t i=1; i<=lP; i++)
    std::cout << L[i] << " ";
  std::cout << std::endl;

  delete[] (N+1);


  
  LinkedList<size_t> ll;

  // taken from boyer-moore-galil.pdf

  size_t i, j = lP;
  int al;
  
  while( j <= lT ){
    i = lP;
    std::cout << "j " << j << std::endl;
    while( P[i] == T[ j - lP + i ] && i != 0 ){
      if( i == 0 ){
	ll.push_back( j - lP + 1);
      }
      else{
	std::cout << "i " << i << std::endl;
	i--;
      }
    }
    if( i==0 )
      ll.push_back( j - lP + 1 );
    std::cin >> al;
    std::cout << "i " << i << std::endl;
    // std::cout << "H " << H[i] << " L " << L[i] << std::endl; 
    std::cout << "j " << j << std::endl;
    if( i != 0 ){
      std::cout << ( H[i] > L[i] ? H[i] : L[i] ) << std::endl;
      j = j + ( H[i] > L[i] ? H[i] : L[i] );
    }
    else{ j++; }
    std::cout << "j " << j << std::endl;
  }
 

  return ll;
}




int main(){
  std::vector<char> t{'g','c','a','t','c','g','c','a','g','a','g','a','g','t','a','t','a','c','a','g','t','a','c','g'};
  std::vector<char> p{'g','c','a','g','a','g','a','g'};
  std::vector<char> alphabet{'a','c','g','t'};
   
  char *T = new char[t.size()];
  char *P = new char[p.size()];
  char *al = new char[alphabet.size()];
  
  for( unsigned int i=0; i<t.size(); i++)
    T[i] = t[i];
  
  for( unsigned int i=0; i<p.size(); i++)
    P[i] = p[i];

  for( unsigned int i=0; i<alphabet.size(); i++)
    al[i] = alphabet[i];
  
  LinkedList<size_t> shifts;

  shifts = Boyer_Moore(T-1, t.size(), P-1, p.size(), al-1, alphabet.size() );

  std::cout << "Shifts:" << std::endl;
  for( LinkedList<size_t>::Iterator it=shifts.begin(); it != shifts.end(); ++it){
    std::cout << *it << std::endl;
  }
  
  return 0;
}
