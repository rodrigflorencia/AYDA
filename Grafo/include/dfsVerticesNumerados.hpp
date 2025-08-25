/****
 * Métodos válidos para Grafos con vértices numerados consecutivamente de 0 a N
 */
#ifndef DFS_H_
#define DFS_H_

#include "mapa/Grafo.hpp"
#include <iostream>
#include <list>
#include <utility>

using namespace std;

enum ClaseArco { TREE, BACK, CROSS, FORWARD };
enum Estado { NOVISITADO, VISITADO, COMPLETO };

using Arco = std::pair<int, int>;
using ArcoClasificado = std::pair<ClaseArco, Arco>;

// =======================
// DFS (clasificación de arcos)
// =======================
void dfsVisitArcos(const Grafo<int> &g, int v,
                   list<ArcoClasificado> &listaArcos, int &tiempo,
                   Estado *estado, int *descubrimiento) {
  tiempo++;// no es necesario si es GND
  descubrimiento[v] = tiempo; // no es necesario si es GND
  estado[v] = VISITADO; // usar set si es GND

  set<int> ady = g.getAdyacentes(v);

  for (set<int>::const_iterator u = ady.begin(); u != ady.end(); u++) {

    if (estado[*u] == NOVISITADO) {
      listaArcos.push_back({TREE, {v, *u}}); // Agregar *u-> v si es GND
      dfsVisitArcos(g, *u, listaArcos, tiempo, estado, descubrimiento);
    } else {
      if (estado[*u] == VISITADO) {
        listaArcos.push_back({BACK, {v, *u}});// Agregar *u-> v si es GND
      } else {
        // COMPLETO: FORWARD o CROSS según tiempos
        if (descubrimiento[v] < descubrimiento[*u]) {
          listaArcos.push_back({FORWARD, {v, *u}});// Agregar *u-> v si es GND
        } else {
          listaArcos.push_back({CROSS, {v, *u}});// Agregar *u-> v si es GND
        }
      }
    }
  }

  estado[v] = COMPLETO;
}

void dfsForestArcos(const Grafo<int> &g) {
  const int n = g.nVertices();
  list<ArcoClasificado> listaArcos;
  set<int> vertices = g.getVertices();
  Estado *estado = new Estado[n];
  int *descubrimiento = new int[n]; // no es necesario si es GND

  for (set<int>::const_iterator i = vertices.begin(); i != vertices.end();
       i++) {
    estado[*i] = NOVISITADO;
    descubrimiento[*i] = -1;
  }
  int tiempo = 0; // no es necesario si es GND

  for (int v = 0; v < n; ++v) {
    if (estado[v] == NOVISITADO) {
      dfsVisitArcos(g, v, listaArcos, tiempo, estado, descubrimiento);
    }
  }

  cout << "Referencias\n0: TREE\n1: BACK\n2: CROSS\n3: FORWARD\n\n";
  for (list<ArcoClasificado>::iterator par = listaArcos.begin();
       listaArcos.end() != par; par++) {
    cout << "Tipo: " << par->first << ", Arco: " << par->second.first << " -> "
         << par->second.second << "\n";
  }

  delete[] descubrimiento;
  delete[] estado;
}

// =======================
// DFS  (orden y padres)
// =======================

void dfsVisit(const Grafo<int> &g, int v, set<int> &visitados,
              list<int> &orden) {
  visitados.insert(v);

  set<int> ady = g.getAdyacentes(v);

  for (set<int>::const_iterator u = ady.begin(); u != ady.end(); u++) {

    if (visitados.find(*u) == visitados.end()) {

      dfsVisit(g, *u, visitados, orden);
    }
  }
  orden.push_back(v);
}

void dfsForest(const Grafo<int> &g) {
  const int n = g.nVertices();
  set<int> estado;

  list<int> orden;
  set<int> vertices = g.getVertices();

  for (set<int>::const_iterator v = vertices.begin(); v != vertices.end();
       v++) {
    if (estado.find(*v) != estado.end())
      dfsVisit(g, *v, estado, orden);
  }
}

// =======================
// Detección de ciclo simple (en dirigidos)
// =======================

bool dfsCicloVisit(const Grafo<int> &g, int v, Estado *estado) {
  estado[v] = VISITADO; // si es GND usar set

  set<int> ady = g.getAdyacentes(v);

  bool ciclo = false;
  set<int>::const_iterator u = ady.begin();
  while (u != ady.end() && !ciclo) {

    if (estado[*u] == VISITADO)
      ciclo = true; // back-edge
    else if (estado[*u] == NOVISITADO)
      ciclo = dfsCicloVisit(g, *u, estado);
    u++;
  }

  estado[v] = COMPLETO; // si es GND no es necesario
  return ciclo;
}

bool hayCicloSimple(const Grafo<int> &g) {
  const int n = g.nVertices();
  set<int> vertices = g.getVertices();

  Estado *estado = new Estado[n]; // si es GND usar set
  for (set<int>::const_iterator v = vertices.begin(); v != vertices.end(); v++)
    estado[*v] = NOVISITADO;

  bool ciclo = false;
  set<int>::const_iterator v = vertices.begin();
  while (v != vertices.end() && !ciclo) {
    if (estado[*v] == NOVISITADO)
      ciclo = dfsCicloVisit(g, *v, estado);
    v++;
  }

  delete[] estado;
  return ciclo;
}

#endif /* DFS_H_ */
