#include "include/mapa/Grafo.hpp"
#include "include/puntero/GrafoLista.cpp"
#include "include/rotulado/GrafoRotulado.hpp"

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

int main() {
  grafoRotulado();
  grafo();
  grafoPuntero();

  return 0;
}
