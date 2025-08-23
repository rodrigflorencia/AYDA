#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <list>

#include <iostream>
using namespace std;

template <class V, class C>
class Grafo
{
public:
    Grafo(); // por defecto se asume dirigido
    virtual ~Grafo();
    Grafo(bool noDirigido);

    bool addArco(const V &deVertice, const V &aVertice, const C &costo);
    bool addArco(const V &deVertice, const V &aVertice);
    bool delArco(const V &deVertice, const V &aVertice);
    bool hayArco(const V &deVertice, const V &aVertice) const;

    const C getCosto(const V &deVertice, const V &aVertice) const;
    void setCosto(const V &deVertice, const V &aVertice, const C &costo);

    bool addVertice(const V &vertice);
    bool delVertice(const V &vertice);

    void imprimir() const;
    int nVertices() const;

    list<V> getVertices() const;
    list<V> getAdyacentes(const V &vertice) const;
    
    int getGradoSalida(const V &v) const;
    int getGrado(const V &v) const;

    

private:
    
    bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos. Deberíamos tener una clase Grafo y dos clases hijas GD y GND, pero será en el próximo cuatrimestre.

    map<V, map<V, C>> grafoMapa;
 
};

#endif
