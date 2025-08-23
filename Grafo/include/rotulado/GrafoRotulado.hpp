/***
 * Grafo genérico utilizando STL: map de map.
 * Implementación grafo rótulado.
 * Soporta grafo dirigido y no dirigido.
 **/
#ifndef GRAFOROTULADO_H
#define GRAFOROTULADO_H

#include <list>
#include <map>

#include <iostream>
using namespace std;

template <class V, class C> class GrafoRotulado {
public:
  GrafoRotulado(); // por defecto se asume dirigido
  virtual ~GrafoRotulado();
  GrafoRotulado(bool noDirigido);

  void addArco(const V &deVertice, const V &aVertice, const C &c);
  void addArco(const V &deVertice, const V &aVertice);
  void delArco(const V &deVertice, const V &aVertice); // TODO
  bool hayArco(const V &deVertice, const V &aVertice) const;

  const C getPeso(const V &deVertice, const V &aVertice) const;
  void setPeso(const V &deVertice, const V &aVertice, const C &c); // TODO

  void addVertice(const V &vertice);
  void delVertice(const V &vertice);         // TODO
  void setVertice(const V &v1, const V &v2); // TODO
  int nVertices() const;

  list<V> getVertices() const;
  list<V> getAdyacentes(const V &vertice) const;

  // Lo más adecuado es escribir este método en otro archivo
  friend ostream &operator<<(ostream &os, const GrafoRotulado &g) {
    for (typename map<V, map<V, C>>::const_iterator it = g.grafoMapa.begin();
         it != g.grafoMapa.end(); it++) {

      os << it->first << ": { ";
      for (typename map<V, C>::const_iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++)
        os << " ( " << it2->first << " , " << it2->second << ") ; ";
      os << " } \n";
    }

    return os;
  };

private:
  bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos.
                   // Deberíamos tener una clase Grafo y dos clases hijas GD y
                   // GND, pero será en el próximo cuatrimestre.

  map<V, map<V, C>> grafoMapa;
};

#endif
