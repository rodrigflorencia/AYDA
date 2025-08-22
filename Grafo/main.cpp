#include "GrafoLAM.tpp"
#include <iostream>
#include "dfs.hpp"
using namespace std;
int main()
{
  Grafo<char, int> g;

  g.addVertice('A');
  g.addVertice('B');

  g.addVertice('C');
  g.addVertice('D');

  g.addArco('A', 'B', 7);
  g.addArco('A', 'C', 5);

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";
  cout << "Peso A-C = " << *(g.getCosto('A', 'C')) << "\n";


dfsForestArcos(g);      // clasificación de arcos
    dfsForestSimple(g);     // recorrido/orden

    //bool ciclo = hayCicloSimple(g);
    //std::cout << "Hay ciclo? " << (ciclo ? "si" : "no") << "\n";

  return 0;

  
}