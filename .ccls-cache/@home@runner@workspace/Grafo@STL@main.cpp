#include "DFS/dfs.hpp"
#include "Grafo.tpp"

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
  dfsForestArcos(g);
  cout << hayCicloSimple(g);

  return 0;
}
