/****
 * Métodos válidos para Grafos con vértices numerados consecutivamente de 0 a N
 */
#ifndef DFS_H_
#define DFS_H_

#include <iostream>
#include <list>
#include <utility>
#include "Grafo.hpp"

using namespace std;

enum ClaseArco { TREE, BACK, CROSS, FORWARD };
enum Estado    { NOVISITADO, VISITADO, COMPLETO };

using Arco            = std::pair<int,int>;
using ArcoClasificado = std::pair<ClaseArco, Arco>;


// =======================
// DFS (clasificación de arcos)
// =======================
void dfsVisitArcos(const Grafo<int>& g, int v,
                   list<ArcoClasificado>& listaArcos,
                   int& tiempo,
                   Estado* estado,
                   int* descubrimiento)
{
    tiempo++;
    descubrimiento[v] = tiempo;
    estado[v] = VISITADO;

    set<int> ady = g.getAdyacentes(v);

    for (set<int>::const_iterator u = ady.begin(); u !=ady.end(); u++) {

        if (estado[*u] == NOVISITADO) {
            listaArcos.push_back({TREE, {v,*u}});
            dfsVisitArcos(g, *u, listaArcos, tiempo, estado, descubrimiento);
        } else {
            if (estado[*u] == VISITADO) {
                listaArcos.push_back({BACK, {v,*u}});
            } else {
                // COMPLETO: FORWARD o CROSS según tiempos
                if (descubrimiento[v] < descubrimiento[*u]) {
                    listaArcos.push_back({FORWARD, {v,*u}});
                } else {
                    listaArcos.push_back({CROSS, {v,*u}});
                }
            }
        }
    }

    estado[v] = COMPLETO;
}

void dfsForestArcos(const Grafo<int>& g)
{
    const int n = g.nVertices();
    list<ArcoClasificado> listaArcos;
    set<int> vertices = g.getVertices();
    Estado* estado = new Estado[n];
    int* descubrimiento = new int[n];

    for (set<int>::const_iterator i = vertices.begin(); i !=vertices.end(); i++) {
        estado[*i] = NOVISITADO;
        descubrimiento[*i] = -1;
    }
    int tiempo = 0;

    for (int v = 0; v < n; ++v) {
        if (estado[v] == NOVISITADO) {
            dfsVisitArcos(g, v, listaArcos, tiempo, estado, descubrimiento);
        }
    }

    cout << "Referencias\n0: TREE\n1: BACK\n2: CROSS\n3: FORWARD\n\n";
      for (list<ArcoClasificado>::iterator par= listaArcos.begin();listaArcos.end()!=par;par++) {
        cout << "Tipo: " << par->first
                  << ", Arco: " << par->second.first
                  << " -> "  << par->second.second << "\n";
    }


    delete[] descubrimiento;
    delete[] estado;
}

// =======================
// DFS simple (orden y padres)
// =======================

template <class TV>
void dfsVisitSimple(const Grafo<TV>& g, int v,
                    set<int> &visitados, list<int>& orden)
{
    visitados.insert(v);

    set<int> ady = g.getAdyacentes(v);

    for (set<int>::const_iterator u = ady.begin(); u !=ady.end(); u++) {

        if (visitados.find(*u)==visitados.end()) {

            dfsVisitSimple(g, *u, visitados, orden);
        }
    }
    orden.push_back(v);
}

template <class TV, class TA>
void dfsForestSimple(const Grafo<TV>& g)
{
    const int n = g.nVertices();
    set<int> estado ;

    list<int> orden;
    set<int> vertices = g.getVertices();


    for (set<int>::const_iterator v = vertices.begin(); v !=vertices.end(); v++) {
        if (estado.find(*v)!=estado.end())
            dfsVisitSimple(g, v, estado, orden);
    }


}

// =======================
// Detección de ciclo simple (en dirigidos)
// =======================

template <class TV>
bool dfsCicloVisit(const Grafo<TV>& g, int v, Estado* estado)
{
    estado[v] = VISITADO;

    set<int> ady = g.getAdyacentes(v);

    bool ciclo = false;
  set<int>::const_iterator u = ady.begin();
         while( u !=ady.end() && !ciclo) {


        if (estado[*u] == VISITADO) ciclo = true;          // back-edge
        else if (estado[*u] == NOVISITADO) ciclo = dfsCicloVisit(g, *u, estado);
            u++;
    }


    estado[v] = COMPLETO;
    return ciclo;
}

template <class TV>
bool hayCicloSimple(const Grafo<TV>& g)
{
    const int n = g.nVertices();
    set<TV> vertices = g.getVertices();

    Estado* estado = new Estado[n];
     for (set<int>::const_iterator v = vertices.begin(); v !=vertices.end(); v++) estado[*v] = NOVISITADO;

    bool ciclo = false;
  set<int>::const_iterator v = vertices.begin();
         while( v !=vertices.end() && !ciclo) {
        if (estado[*v] == NOVISITADO) ciclo = dfsCicloVisit(g, *v, estado);
        v++;
    }

    delete[] estado;
    return ciclo;
}

#endif /* DFS_H_ */
