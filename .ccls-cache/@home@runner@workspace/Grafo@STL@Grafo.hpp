/***
 * Grafo genérico utilizando STL.
 * Implementación grafo con tipo de vértices parametrizado.
 * Soporta grafo dirigido y no dirigido.
 **/
#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <set>

#include <list>   // para lista de adyacencias
#include <vector> // para lista de adyacencias

#include <iostream>
using namespace std;

template <class V> class Grafo {
public:
  Grafo(); // por defecto se asume dirigido
  virtual ~Grafo();
  Grafo(bool noDirigido);

  void addVertice(const V &vertice); // agrega un vertice si no existe
  void setVertice(const V &v1,
                  const V &v2);      // TODO cambia las etiquetas del vertice
  void delVertice(const V &vertice); // TODO borrar arcos que inciden en vertice
                                     // y luego borrar vertice. Si usamos LA,
                                     // actualizar índices.
  set<V> getVertices() const;

  void addArco(const V &deVertice,
               const V &aVertice); // agrega arco si no existe. agrega vertices
                                   // si no existen
  void delArco(const V &deVertice, const V &aVertice); // elimina arco
  bool hayArco(const V &deVertice,
               const V &aVertice) const; // devuelve true si existe el arco
  set<V> getAdyacentes(const V &vertice)
      const; // conjunto de etiquetas de vertices adyacentes a vertice dado

  int nVertices() const; // cantidad de vertices actuales

  friend ostream &operator<<(ostream &os, const Grafo &g) {
    /**
    // Descomentar si usamos la implementación lista de adyacencias. Comentar si
    // usamos map y set (aunque igual funciona, pero no es taaan eficiente)
    **/
    /***
     * cout <<"Referencias\n";
     * for (typename map<V, int>::const_iterator it = g.vertices.begin(); it !=
     *g.vertices.end(); it++) cout << it->first << ": " << it->second << endl;
     **/
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
    /***
    // Implementación con map y set. Comentar todo lo anterior si usamos mapa.
    // Aunque no es necesario, dado que la implementación anterior igual
    funciona,
    // pero no es muy eficiente.
    for (typename map<V, set<V>>::const_iterator it = g.grafoMapa.begin();
         it != g.grafoMapa.end(); it++) {

      os << it->first << ": { ";
      for (typename set<V>::const_iterator it2 = it->second.begin();
           it2 != it->second.end(); it2++)
        os << *it2 << " ; ";
      os << " } \n";
    }
    return os;
    **/
  }

private:
  bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos.
                   // Deberíamos tener una clase Grafo y dos clases hijas GD y
                   // GND, pero será en el próximo cuatrimestre.
                   // Igual, OJO con las implementaciones, estén atentos a esto.

  map<V, set<V>> grafoMapa; // Estructura válida para el mapa de mapa.

  /** Estructuras para la implementación con lista de adyacencias**/
  vector<list<int>>
      adyacencias; // Lista de adyacencias. Si quieren la matriz de adyacencias,
                   // pueden usar un vector de vector de int o bool.
  map<V, int> vertices; // Para vincular cada etiqueta del vertice a un indice.
  int nV;               // Cantidad de vertices actuales.
  /***/
};

#endif
