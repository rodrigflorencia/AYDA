#include <iostream>
#include "Grafo.tpp"
#include <set>
#include <queue>
#include <map>
set<string> recomendaciones(Grafo<string> redSocial, string usuario)
{
  set<string> visitado;
  visitado.insert(usuario);
  map<string, int> orden;
  orden.insert({usuario, 0});

  set<string> recomendaciones;
  queue<string> q;
  q.push(usuario);
  while (!q.empty())
  {
    string v = q.front();
    q.pop();
    set<string> ady = redSocial.getAdyacentes(v);
    for (set<string>::iterator w = ady.begin(); w != ady.end(); w++)
    {
      if (visitado.find(*w) == visitado.end())
      {
        visitado.insert(*w);
        int ordenW = orden[v] + 1;
        orden.insert({*w, ordenW});
        if (ordenW == 2)
          recomendaciones.insert(*w);
        else
          q.push(*w);
      }
    }
  }
  return recomendaciones;
}
void mostrarRecomendaciones(set<string> r)
{
  for (set<string>::const_iterator it = r.begin(); it != r.end(); it++)
    cout << *it << " ; ";
}
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
