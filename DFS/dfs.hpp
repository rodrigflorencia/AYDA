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
// Helpers
// =======================

// Nota: solo depende del tipo de vértice.
template <class TipoVertice>
int getVertice(const TipoVertice* vertices, const TipoVertice& v, int n) {
    for (int i = 0; i < n; ++i) {
        if (vertices[i] == v) return i;
    }
    return -1;
}

// Copia las etiquetas de g en un arreglo nuevo (caller debe delete[]).
template <class TipoVertice, class TipoArco>
TipoVertice* crearArregloVertice(const Grafo<TipoVertice, TipoArco>& g) {
    int n = g.nVertices();
    TipoVertice* src = g.getVertices();   // devuelve new[] según tu implementación
    TipoVertice* out = new TipoVertice[n];
    for (int i = 0; i < n; ++i) out[i] = src[i];
    delete[] src;                         // liberamos el arreglo intermedio
    return out;
}

// =======================
// DFS (clasificación de arcos)
// =======================

template <class TV, class TA>
void dfsVisitArcos(const Grafo<TV,TA>& g, int v,
                   std::list<ArcoClasificado>& listaArcos,
                   int& tiempo,
                   Estado* estado,
                   int* descubrimiento,
                   const TV* vertices)
{
    tiempo++;
    descubrimiento[v] = tiempo;
    estado[v] = VISITADO;

    TV* ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGradoSalida(vertices[v]);

    for (int i = 0; i < nAdy; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u < 0) continue; // seguridad

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
        }
    }

    delete[] ady;
    estado[v] = COMPLETO;
}

template <class TV, class TA>
void dfsForestArcos(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    std::list<ArcoClasificado> listaArcos;

    TV* vertices = crearArregloVertice(g);
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

    std::cout << "Referencias\n0: TREE\n1: BACK\n2: CROSS\n3: FORWARD\n\n";
    for (const auto& par : listaArcos) {
        std::cout << "Tipo: " << par.first
                  << ", Arco: " << vertices[par.second.first]
                  << " -> "  << vertices[par.second.second] << "\n";
    }

    delete[] vertices;
    delete[] descubrimiento;
    delete[] estado;
}

// =======================
// DFS simple (orden y padres)
// =======================

template <class TV, class TA>
void dfsVisitSimple(const Grafo<TV,TA>& g, int v,
                    Estado* estado, int* padres, std::list<int>& orden,
                    const TV* vertices)
{
    estado[v] = VISITADO;

    TV* ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGradoSalida(vertices[v]);

    for (int i = 0; i < nAdy; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u >= 0 && estado[u] == NOVISITADO) {
            padres[u] = v;
            dfsVisitSimple(g, u, estado, padres, orden, vertices);
        }
    }

    delete[] ady;
    orden.push_back(v);
}

template <class TV, class TA>
void dfsForestSimple(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    Estado* estado = new Estado[n];
    int* padres = new int[n];
    std::list<int> orden;
    TV* vertices = crearArregloVertice(g);

    for (int i = 0; i < n; ++i) {
        estado[i] = NOVISITADO;
        padres[i] = -1;
    }

    for (int v = 0; v < n; ++v) {
        if (estado[v] == NOVISITADO)
            dfsVisitSimple(g, v, estado, padres, orden, vertices);
    }

    std::cout << "\nRecorrido DFS (post-orden por finalización):\n";
    for (int idx : orden) {
        if (padres[idx] != -1)
            std::cout << vertices[padres[idx]] << " -> ";
        std::cout << vertices[idx] << "\n";
    }

    delete[] vertices;
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

    TV* ady = g.getAdyacentes(vertices[v]);
    int nAdy = g.getGradoSalida(vertices[v]);

    bool ciclo = false;
    for (int i = 0; i < nAdy && !ciclo; ++i) {
        int u = getVertice(vertices, ady[i], g.nVertices());
        if (u < 0) continue;
        if (estado[u] == VISITADO) ciclo = true;          // back-edge
        else if (estado[u] == NOVISITADO) ciclo = dfsCicloVisit(g, u, estado, vertices);
    }

    delete[] ady;
    estado[v] = COMPLETO;
    return ciclo;
}

template <class TV, class TA>
bool hayCicloSimple(const Grafo<TV,TA>& g)
{
    const int n = g.nVertices();
    TV* vertices = crearArregloVertice(g);
    Estado* estado = new Estado[n];
    for (int i = 0; i < n; ++i) estado[i] = NOVISITADO;

    bool ciclo = false;
    for (int v = 0; v < n && !ciclo; ++v) {
        if (estado[v] == NOVISITADO) ciclo = dfsCicloVisit(g, v, estado, vertices);
    }

    delete[] estado;
    delete[] vertices;
    return ciclo;
}

#endif /* DFS_H_ */
