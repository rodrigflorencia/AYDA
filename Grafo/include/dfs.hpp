/****
 * Métodos válidos para Grafos con vértices etiquetados
 */
#ifndef DFS_H_
#define DFS_H_

#include "mapa/Grafo.hpp"
#include <iostream>
#include <list>
#include <utility>

using namespace std;

enum ClaseArco { TREE, BACK, CROSS, FORWARD }; // Para clasificar arcos

enum Estado {
  NOVISITADO,
  VISITADO,
  COMPLETO
}; // En lugar de gris, amarillo y negro

// Estructuras auxiliares para clasificar arcos
template <class V> using Arco = pair<V, V>;
template <class V> using ArcoClasificado = pair<ClaseArco, Arco<V>>;

// =======================
// DFS (clasificación de arcos)
// Para grafos no dirigidos no es necesario descubrimiento y tiempo. estado debe ser un set
// =======================
template <class V>
void dfsVisitArcos(const Grafo<V> &g, const V &v,
                   list<ArcoClasificado<V>> &listaArcos, int &tiempo,
                   map<V, Estado> &estado, map<V, int> &descubrimiento) {
  tiempo++;
  descubrimiento[v] = tiempo;
  estado[v] = VISITADO;

  set<V> ady = g.getAdyacentes(v);

  for (typename set<V>::const_iterator u = ady.begin(); u != ady.end(); ++u) {
    if (estado[*u] == NOVISITADO) {
      listaArcos.push_back({TREE, {v, *u}});// Agregar *u-> v si es GND
      dfsVisitArcos(g, *u, listaArcos, tiempo, estado, descubrimiento);
    } else {
      if (estado[*u] == VISITADO) {
        listaArcos.push_back({BACK, {v, *u}});// Agregar *u-> v si es GND
      } else {
        // COMPLETO: FORWARD o CROSS según tiempos
        if (descubrimiento[v] < descubrimiento[*u]) {
          listaArcos.push_back({FORWARD, {v, *u}}); // Agregar *u-> v si es GND
        } else {
          listaArcos.push_back({CROSS, {v, *u}});// Agregar *u-> v si es GND
        }
      }
    }
  }

  estado[v] = COMPLETO;
}
template <class V> void dfsForestArcos(const Grafo<V> &g) {

  list<ArcoClasificado<V>>
      listaArcos; // lista de arcos clasificados.
                  // Cada elemento es un par <Tipo de arco, {Origen, Destino}>

  set<V> vertices = g.getVertices();
  map<V, Estado> estado; // si el grafo es ND, cambiar por set
  map<V, int> descubrimiento; // no es necesario si el grafo es ND
  int tiempo = 0;// no es necesario si el grafo es ND

  for (typename set<V>::const_iterator itV = vertices.begin();
       itV != vertices.end(); itV++) {
    estado[*itV] = NOVISITADO;
    descubrimiento[*itV] = -1;
  }

  for (typename set<V>::const_iterator itV = vertices.begin();
       itV != vertices.end(); itV++) {
    if (estado[*itV] == NOVISITADO) {
      dfsVisitArcos(g, *itV, listaArcos, tiempo, estado, descubrimiento);
    }
  }

  cout << "Referencias\n0: TREE\n1: BACK\n2: CROSS\n3: FORWARD\n\n";
  for (typename list<ArcoClasificado<V>>::iterator par = listaArcos.begin();
       listaArcos.end() != par; par++) {
    cout << "Tipo: " << par->first << ", Arco: " << par->second.first << " -> "
         << par->second.second << "\n";
  }
}

// =======================
// DFS (orden y padres)
// =======================

template <class V>
void dfsVisit(const Grafo<V> &g, int v, set<V> &visitados, list<V> &orden) {
  visitados.insert(v);

  set<V> ady = g.getAdyacentes(v);

  for (typename set<V>::const_iterator u = ady.begin(); u != ady.end(); u++) {

    if (visitados.find(*u) == visitados.end()) {

      dfsVisit(g, *u, visitados, orden);
    }
  }
  orden.push_back(v);
}

template <class V> void dfsForest(const Grafo<V> &g) {
  const int n = g.nVertices();
  set<V> visitados;

  list<V> orden;
  set<V> vertices = g.getVertices();

  for (typename set<V>::const_iterator v = vertices.begin();
       v != vertices.end(); v++) {
    if (visitados.find(*v) != visitados.end())
      dfsVisit(g, v, visitados, orden);
  }
}

// =======================
// Detección de ciclo simple
// =======================

template <class V>
bool dfsCicloVisit(const Grafo<V> &g, int v, map<V, Estado> estado) {
  estado[v] = VISITADO; // Si es GND usar set

  set<V> ady = g.getAdyacentes(v);

  bool ciclo = false;
  typename set<V>::iterator u = ady.begin();
  while (u != ady.end() && !ciclo) {

    if (estado[*u] == VISITADO)
      ciclo = true; // back-edge
    else if (estado[*u] == NOVISITADO)
      ciclo = dfsCicloVisit(g, *u, estado);
    u++;
  }

  estado[v] = COMPLETO; // Si es GND comentar linea
  return ciclo;
}

template <class V> bool hayCicloSimple(const Grafo<V> &g) {
  const int n = g.nVertices();
  set<V> vertices = g.getVertices();

  map<V, Estado> estado; // set para GND
  for (typename set<V>::const_iterator v = vertices.begin();
       v != vertices.end(); v++)
    estado[*v] = NOVISITADO;

  bool ciclo = false;
  typename set<V>::const_iterator v = vertices.begin();
  while (v != vertices.end() && !ciclo) {
    if (estado[*v] == NOVISITADO)
      ciclo = dfsCicloVisit(g, *v, estado);
    v++;
  }

  return ciclo;
}

#endif /* DFS_H_ */
