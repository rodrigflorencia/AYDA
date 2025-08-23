
#include "STL-LA/Grafo.hpp"

int main() {
  Grafo<char> g;

  g.addVertice('A');
  g.addVertice('B');
  g.addVertice('C');
  g.addVertice('D');
  g.addVertice('E');
  g.addVertice('F');

  g.addArco('A', 'B');
  g.addArco('F', 'D');
  g.addArco('2', 'A');

  cout << g;

  return 0;
}
/***
#include "STL - mapa de mapa/Grafo.tpp"

using namespace std;
int main() {
  Grafo<char, int> g;

  g.addVertice('A');
  g.addVertice('B');

  g.addVertice('C');
  g.addVertice('D');

  g.addArco('A', 'B', 7);
  g.addArco('A', 'C', 5);

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";
  cout << "Peso A-C = " << g.getPeso('A', 'C') << "\n";
  cout << "Peso A-D = " << g.getPeso('A', 'D') << "\n";
  cout<<g;

  return 0;
}
***/