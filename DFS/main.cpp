#include "Grafo/Grafo.tpp"
#include "dfs2.hpp"
#include <iostream>
int main() {
  Grafo<char> g;

  g.addVertice('X');
  g.addVertice('B');
  g.addVertice('M');
  g.addVertice('D');
  g.addVertice('P');
  g.addVertice('F');

  g.addArco('X', 'D');
  g.addArco('X', 'M');
  g.addArco('B', 'F');
  g.addArco('B', 'P');
  g.addArco('P', 'X');
  g.addArco('F', 'B');
  g.addArco('D', 'F');

  cout << "Grafo\n" << g << endl;
  dfsForestArcos(g);
  cout << hayCicloSimple(g);

  return 0;
}
