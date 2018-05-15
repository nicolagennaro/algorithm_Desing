#include <iostream>
#include <vector>


template <typename T>
T* vec_to_p(std::vector<T>& v){
  T *p = new T[v.size()];
  p = p-1;
  for( size_t i=1; i<=v.size(); i++ )
    p[i] = v[i-1];
  return p;
}

template <typename T>
void print_p(T* p, size_t len){
  for( size_t i=1; i<=len; i++)
    std::cout << p[i] << " ";
  std::cout << std::endl;
}


size_t LCP(char* T1, size_t l1, size_t i1, char* T2, size_t l2, size_t i2, size_t s=0){

  while(T1[i1 + s] == T2[i2 + s] && (i1 + s) <= l1 && (i2 + s) <= l2 )
    s++;

  std::cout << "LCS of " << std::endl;
  print_p(T1, l1);
  print_p(T2, l2);
  std::cout << "LCS " << s << std::endl;

  return s;
}



bool LTl(char* T1, size_t l1, char* T2, size_t l2, size_t l, size_t start=1){

  size_t k=1;

  std::cout << "LTl" << std::endl;
  std::cout << "comparing" << std::endl;
  print_p(T1, l1);
  std::cout << "and" << std::endl;
  print_p(T2, l2);
  std::cout << "up to " << l << std::endl;

  while( k<= l1 && k<=l2 && k<=l ){
    if( T1[k] > T2[k] )
      return false;
    else
      if( T1[k] < T2[k] )
	return true;
    k++;
  }

  return (k==l1+1 || k==l+1);
}


// SA contains the starting index of the suffix of T
void SA_matching( char* T, size_t len_T, char* P, size_t len_P, size_t* SA){


  std::cout << "#############################################" << std::endl;
  std::cout << "SA matching" << std::endl;  

  size_t Lp, Rp;

  std::cout << "SA[1] " << SA[1] << std::endl;
  std::cout << "SA[len_T] " << SA[len_T] << std::endl;
  
  if( LTl(P, len_P, T+SA[1]-1, len_T - SA[1] + 1, len_P) )
    Lp = 0;
    
  else if( LTl( T+SA[len_T]-1, len_T - SA[len_T] + 1, P, len_P, len_P ) )
    Lp = len_T + 1;
  
  else{
    size_t L = 1, R = len_T, M;
    size_t l, r, h;
    l = LCP(T, len_T - SA[L], SA[L], P, len_P, 1);
    r = LCP(T, len_T - SA[R], SA[R], P, len_P, 1);
    std::cout << "l " << l << " r " << r << std::endl;
    h = (l < r ? l : r);
    std::cout << "h " << h << std::endl;
    while( R-L > 1 ){
      M = (L+R)/2;
      // bool LTl(char* T1, size_t l1, char* T2, size_t l2, size_t l, size_t start=1){
      if( LTl(P, len_P, T+SA[M]-1, len_T - SA[M], len_P, h) ){
	R = M;
	r = LCP( T, len_T - SA[M], SA[M], P, len_P, 1, h);
      }
      else{
	L = M;
	l = LCP( T, len_T - SA[M], SA[M], P, len_P, 1, h);
      }
    } // while
    Lp = L;
  }

    std::cout << "Lp " << Lp << std::endl;
}


int main(){

  std::vector<char> t{'a','b','a','a','c'};
  std::vector<char> p{'a', 'c'};

  char *T = new char[t.size()];
  char *P = new char[p.size()];

  for( unsigned int i=0; i<t.size(); i++)
    T[i] = t[i];

  
  for( unsigned int i=0; i<p.size(); i++)
    P[i] = p[i];

  std::cout << (P[1] < T[1] ? P[1] : T[1]) << std::endl;
  std::cout << (P[1] < T[1]) << std::endl;


  bool res;

  for(size_t i=0; i<t.size(); i++)
    std::cout << T[i] << " ";
  std::cout << std::endl;

  for(size_t i=0; i<p.size(); i++)
    std::cout << P[i] << " ";
  std::cout << std::endl;
  
  res = LTl(T-1, t.size(), P-1, p.size(), 3);

  std::cout << res << std::endl;


  std::cout << "#############################################" << std::endl;

  
  std::vector<char> tt{'a','b','a','a','c'};
  std::vector<char> pp{'a','c'};

  std::vector<size_t> sa{3,1,4,2,5};
  char *PP, *TT;
  size_t *SA;

  SA = vec_to_p(sa);

  std::cout << "SA" << std::endl;
  print_p(SA, sa.size());
  
  TT = vec_to_p(tt);
  PP = vec_to_p(pp);

  std::cout << "TT" << std::endl;
  print_p(TT,tt.size());

  std::cout << "PP" << std::endl;
  print_p(PP,pp.size());

  std::cout << "#############################################" << std::endl;
  SA_matching(TT, tt.size(), PP, pp.size(), SA);
  return 0;
}
