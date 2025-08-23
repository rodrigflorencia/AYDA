#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <map>
#include <set>
#include <vector>

#include <iostream>
using namespace std;

template <class V> class Grafo {
public:
  Grafo(); // por defecto se asume dirigido
  virtual ~Grafo();
  Grafo(bool noDirigido);

  void addVertice(const V &vertice);

  set<V> getVertices() const;

  void addArco(const V &deVertice, const V &aVertice);
  void delArco(const V &deVertice, const V &aVertice);
  bool hayArco(const V &deVertice, const V &aVertice) const;
  set<V> getAdyacentes(const V &vertice) const;

  int nVertices() const;
  friend ostream &operator<<(ostream &os, const Grafo &g) {
    cout << "Referencias\n";
    for (typename map<V, int>::const_iterator it = g.vertices.begin();
         it != g.vertices.end(); it++)
      cout << it->first << ": " << it->second << endl;
    set<V> v = g.getVertices();
    for (typename set<V>::const_iterator it = v.begin(); it != v.end(); it++) {
      os << "Vertice: [" << *it << "] Destinos: { ";
      set<V> ady = g.getAdyacentes(*it);
      for (typename set<V>::const_iterator itA = ady.begin(); itA != ady.end();
           itA++)
        os << " [" << (*itA) << "] ; ";
      os << " } " << endl;
    }

    return os;
  };

private:
  bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos.
                   // Deberíamos tener una clase Grafo y dos clases hijas GD y
                   // GND, pero será en el próximo cuatrimestre.
  vector<list<int>> adyacencias; // Lista de adyacencias
  map<V, int> vertices; // Para vincular cada etiqueta del vertice a un indice.
  int nV;               // Cantidad de vertices actuales.
};

#endif
