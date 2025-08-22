#include "GrafoLA.tpp"
#include <iostream>
using namespace std;
int main()
{

  
  Grafo<char, int> g(true);

  g.addArco('A', 'B', 7);
  g.addArco('A', 'C', 5);

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";
  cout << "Peso A-C = " << *(g.getCosto('A', 'C')) << "\n";

  cout << "Adyacentes de A" << endl;
  char *ady = g.getAdyacentes('A');
  int n = g.getGrado('A');
  for (int i = 0; i < n; i++)
    cout << ady[i] << " ; ";

  g.delArco('A', 'C');

  cout << "\n";
  cout << "Hay A-C? " << g.hayArco('A', 'C') << "\n";
  cout << "Peso A-C = " << (g.getCosto('A', 'C')) << "\n";
  cout << "Adyacentes de A" << endl;
  ady = g.getAdyacentes('A');
  n = g.getGrado('A');
  for (int i = 0; i < n; i++)
    cout << ady[i] << " ; ";
  g.imprimir();
  return 0;
}