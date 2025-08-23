#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

bool es_sufijo(char P[],int k,int q,char s)
{
  string ending="" ;
  for (int i=0;i<k;i++)
      ending = ending+P[i];
  string fullString="";
  for (int i = 0;i<q;i++)
      fullString = fullString + P[i];
  fullString = fullString + s;
  if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

// P el patrón; S arreglo con las cadenas del lenguaje
void compute_transition_function(char P[],char S[],int D[5][3])
{
  
  int m = strlen(P);
  int n = strlen(S);

  for (int q=0;q<m;q++){
      for (int s=0;s<n;s++){
          int k;
          if (m+1<q+2)
              k=m+1;
          else
              k=q+2;
          do {
              k=k-1;
          }while (!es_sufijo(P,k,q,S[s]));
          D[q][s]=k;
      }
  }
}

int main()
{
    char P[6] = "abcab";
    char S[4] = "abc";
    int D[5][3];
    compute_transition_function(P,S,D);
    return 0;
}

