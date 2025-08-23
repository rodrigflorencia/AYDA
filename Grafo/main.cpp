#include "include/mapa/Grafo.hpp"
#include "include/puntero/GrafoLista.cpp"
#include "include/rotulado/GrafoRotulado.hpp"

#include "include/dfs.hpp"
#include "include/redSocial.hpp"

/**
 * Pruebas de la implementación de grafo rotulado con punteros
 */
int grafoPuntero() {
  GrafoPuntero<char, char> g;

  g.addVertice('A');
  g.addVertice('B');
  g.addVertice('C');
  g.addVertice('D');

  g.addArco('A', 'B', '7');
  g.addArco('A', 'C', '5');

  cout << "\n\nGrafo rotulado implementado con punteros\n";

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";
  cout << "Peso A-C = " << g.getPeso('A', 'C') << "\n";
  cout << "Peso A-D = " << g.getPeso('A', 'D') << "\n";
  g.imprimir();

  return 0;
}

/**
 * Pruebas de la implementación de grafo rotulado con stl lista de adyacentes
 */
int grafoRotulado() {
  GrafoRotulado<char, int> g;

  g.addVertice('A');
  g.addVertice('B');
  g.addVertice('C');
  g.addVertice('D');

  g.addArco('A', 'B', 7);
  g.addArco('A', 'C', 5);

  cout << "\n\nGrafo rotulado implementado con lista de adyacentes y mapa\n";

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";
  cout << "Peso A-C = " << g.getPeso('A', 'C') << "\n";
  cout << "Peso A-D = " << g.getPeso('A', 'D') << "\n";
  cout << g;

  return 0;
}
/**
 * Pruebas de la implementación de grafo  con  lista de adyacentes
 */
int grafo() {
  // Grafo con lista de adyacencias "include/mapa/Grafo.cpp" o
  //  "include/mapa/GrafoList.cpp"

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

  cout << "\n\nGrafo implementado como lista de adyacentes\n" << g;

  return 0;
}
/**
Prueba del dfs
***/
int dfs() {
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

int redSocial() {
  Grafo<string> g;

  g.addVertice("@pupi");
  g.addVertice("@pepe");
  g.addVertice("@toto");
  g.addVertice("@pepe");
  g.addVertice("@rodo");
  g.addVertice("@tito");
  g.addVertice("@rodo");
  g.addVertice("@luli");
  g.addArco("@kuky", "@toto");
  g.addArco("@kuky", "@pupi");
  g.addArco("@pepe", "@toto");
  g.addArco("@pepe", "@kuky");
  g.addArco("@pepe", "@luli");
  g.addArco("@pepe", "@rodo");
  g.addArco("@rodo", "@tito");

  cout << g;
  string usuario = "@pepe";
  set<string> r = recomendaciones(g, usuario);
  cout << "\nRecomendaciones para " << usuario << endl;
  mostrarRecomendaciones(r);

  return 0;
}

int main() {
  dfs();
  redSocial();

  return 0;
}
