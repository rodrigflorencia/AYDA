#include "Grafo/Grafo.tpp"
#include "redSocial.hpp"

int main()
{
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
