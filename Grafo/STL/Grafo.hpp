#ifndef GRAFO_H
#define GRAFO_H

#include <unordered_map>
#include <set>

#include <iostream>
using namespace std;

template <class V>
class Grafo
{
public:
    Grafo(); // por defecto se asume dirigido
    virtual ~Grafo();
    Grafo(bool noDirigido);

    bool addVertice(const V &vertice);
    bool delVertice(const V &vertice); // TODO borrar arcos que inciden en vertice y luego borrar vertice
    set<V> getVertices() const;

    bool addArco(const V &deVertice, const V &aVertice);
    bool delArco(const V &deVertice, const V &aVertice);
    bool hayArco(const V &deVertice, const V &aVertice) const;
    set<V> getAdyacentes(const V &vertice) const;

    int nVertices() const;
    int getGradoSalida(const V &v) const;
    int getGrado(const V &v) const;

    friend  ostream& operator<<(ostream& os, const Grafo& g)
    {
        for (typename unordered_map<V, set<V>>::const_iterator it = g.grafoMapa.begin(); it != g.grafoMapa.end(); it++)
    {

        cout<<it->first<<": { ";
        for (typename set<V>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
            cout<<*it2<<" ; ";
        cout<<" } \n";

    }
    };

private:
    
    bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos. Deberíamos tener una clase Grafo y dos clases hijas GD y GND, pero será en el próximo cuatrimestre.
    unordered_map<V, set<V>> grafoMapa;
};

#endif
