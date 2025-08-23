#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
using std::pow;

// d tiene que ser un número mayor a la cantidad de caracteres del lenguaje
#define d 256

// q tiene que ser un número primo
void rabin_karp_matcher(char T[],char P[],int q) {
    
    int h_t = 0; // hash de texto T
    int h_p = 0; // hash de patron P
    int m = strlen(P); // tamaño de P
    int n = strlen(T); // tamaño de T
    int h=1; 
    
    // pow(d,M-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // rolling hashing
    for (int i=0; i<m; i++){
      h_t =(d * h_t + T[i]) % q;
      h_p =( d * h_p + P[i]) % q ;
    }
   
   // busqueda
   for (int i=0;i<n-m;i++){
      if (h_t == h_p) {
        cout << "Matching con desplazamiento: " << i << endl;
      }
      if (i<n-m){
        h_t = (d*(h_t - T[i]*(int)h) + T[i+m])%q;
        if (h_t<0)
          h_t=h_t+q;
		}
	}
}

int main () {
  char T[10] = "holamundo";
  char P[6] = "mundo";
  rabin_karp_matcher(T,P,101);
}
