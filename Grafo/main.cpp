/**
#include "STL/Grafo.tpp"

int main() {
  Grafo<int> g;

  g.addVertice(1);
  g.addVertice(2);
  g.addVertice(3);
  g.addVertice(2);
  g.addVertice(4);
  g.addVertice(4);

  g.addArco(0, 3);
  g.addArco(0, 1);
  g.addArco(2, 3);
  g.addArco(2, 0);
  g.addArco(1, 4);
  g.addArco(2, 4);

  cout << g;

  return 0;
}
***/
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
  cout << "Peso A-C = " << (g.getCosto('A', 'C')) << "\n";

  return 0;
}
/***/