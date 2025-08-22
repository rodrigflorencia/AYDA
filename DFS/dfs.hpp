#ifndef DFS_H_
#define DFS_H_

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include "Grafo.tpp"

using namespace std;

enum ClaseArco { TREE, BACK, CROSS, FORWARD };
enum Estado    { NOVISITADO, VISITADO, COMPLETO };

using Arco            = pair<int,int>;
using ArcoClasificado = pair<ClaseArco, Arco>;

// =======================
// Helpers
// =======================

template <class TipoVertice>
int getVertice(const TipoVertice* vertices, const TipoVertice& v, int n) {
    int i =0;
    bool encontrado = false;
    while ( i < n && !encontrado) {
        if (vertices[i] == v) {
            encontrado=true;
        }
        else {
            i++;
        }
    }
    return -1;
}

// =======================
// DFS (clasificación de arcos)
// =======================

template <class TV, class TA>
void dfsVisitArcos(const Grafo<TV,TA>& g, int v,
                   list<ArcoClasificado>& listaArcos,
                   int& tiempo,
                   Estado* estado,
                   int* descubrimiento,
                   const TV* vertices)
{
    tiempo++;
    descubrimiento[v] = tiempo;
    estado[v] = VISITADO;

    vectorzTV> ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGrado(vertices[v]);

    for (int i = 0; i < nAdy; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u < 0)  {
        if (estado[u] == NOVISITADO) {
            listaArcos.push_back({TREE, {v,u}});
            dfsVisitArcos(g, u, listaArcos, tiempo, estado, descubrimiento, vertices);
        } else {
            if (estado[u] == VISITADO) {
                listaArcos.push_back({BACK, {v,u}});
            } else {
                // COMPLETO: FORWARD o CROSS según tiempos
                if (descubrimiento[v] < descubrimiento[u]) {
                    listaArcos.push_back({FORWARD, {v,u}});
                } else {
                    listaArcos.push_back({CROSS, {v,u}});
                }
            }
        }}
    }

    delete[] ady;
    estado[v] = COMPLETO;
}

template <class TV, class TA>
void dfsForestArcos(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    list<ArcoClasificado> listaArcos;

    vector<TV> vertices = g.getVertices();
    Estado* estado = new Estado[n];
    int* descubrimiento = new int[n];

    for (int i = 0; i < n; ++i) {
        estado[i] = NOVISITADO;
        descubrimiento[i] = -1;
    }
    int tiempo = 0;

    for (int v = 0; v < n; ++v) {
        if (estado[v] == NOVISITADO) {
            dfsVisitArcos(g, v, listaArcos, tiempo, estado, descubrimiento, vertices);
        }
    }

    cout << "Referencias\n0: TREE\n1: BACK\n2: CROSS\n3: FORWARD\n\n";
    for (typename list<ArcoClasificado>::const_iterator par : listaArcos) {
        cout << "Tipo: " << par.first
                  << ", Arco: " << vertices[par.second.first]
                  << " -> "  << vertices[par.second.second] << "\n";
    }

   
    delete[] descubrimiento;
    delete[] estado;
}

// =======================
// DFS simple (orden y padres)
// =======================

template <class TV, class TA>
void dfsVisitSimple(const Grafo<TV,TA>& g, int v,
                    Estado* estado, int* padres, list<int>& orden,
                    const TV* vertices)
{
    estado[v] = VISITADO;

    vector<TV> ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGrado(vertices[v]);

    for (int i = 0; i < nAdy; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u >= 0 && estado[u] == NOVISITADO) {
            padres[u] = v;
            dfsVisitSimple(g, u, estado, padres, orden, vertices);
        }
    }

    orden.push_back(v);
}

template <class TV, class TA>
void dfsForestSimple(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    Estado* estado = new Estado[n];
    int* padres = new int[n];
    list<int> orden;
    vector<TV> vertices =g.getVertices();

    for (int i = 0; i < n; ++i) {
        estado[i] = NOVISITADO;
        padres[i] = -1;
    }

    for (int v = 0; v < n; ++v) {
        if (estado[v] == NOVISITADO)
            dfsVisitSimple(g, v, estado, padres, orden, vertices);
    }

    cout << "\nRecorrido DFS (post-orden por finalización):\n";
    for (int idx : orden) {
        if (padres[idx] != -1)
            cout << vertices[padres[idx]] << " -> ";
        cout << vertices[idx] << "\n";
    }

    delete[] padres;
    delete[] estado;
}

// =======================
// Detección de ciclo simple (en dirigidos)
// =======================

template <class TV, class TA>
bool dfsCicloVisit(const Grafo<TV,TA>& g, int v, Estado* estado, const TV* vertices)
{
    estado[v] = VISITADO;

    vector<TV> ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGrado(vertices[v]);

    bool ciclo = false;
    for (int i = 0; i < nAdy && !ciclo; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u >= 0) {
        if (estado[u] == VISITADO) ciclo = true;          // back-edge
        else if (estado[u] == NOVISITADO) ciclo = dfsCicloVisit(g, u, estado, vertices);
    }}

    estado[v] = COMPLETO;
    return ciclo;
}

template <class TV, class TA>
bool hayCicloSimple(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    vector<TV> vertices = g.getVertices();
    Estado* estado = new Estado[n];
    for (int i = 0; i < n; ++i) estado[i] = NOVISITADO;

    bool ciclo = false;
    for (int v = 0; v < n && !ciclo; ++v) {
        if (estado[v] == NOVISITADO) ciclo = dfsCicloVisit(g, v, estado, vertices);
    }

    delete[] estado;
    return ciclo;
}

#endif /* DFS_H_ */
