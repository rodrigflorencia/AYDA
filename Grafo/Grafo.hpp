#ifndef GRAFO_H
#define GRAFO_H

#include <unordered_map>
#include <list>
#include <iostream>
using namespace std;

template <class V, class C>
class Grafo
{
public:
    Grafo();
    virtual ~Grafo();
    Grafo(bool noDirigido) ;
    void addVertice(const V &vertice);
    void addArco(const V & deVertice,const V & aVertice,const C & costo);
    void addArco(const V & deVertice,const V & aVertice);
    const list<V> &getVertices() const;
    const C* getCosto(const V & deVertice,const V & aVertice) const;
    int nVertices() const;
    int nAristas()const ;
    const unordered_map<V,C>& getAdyacentes(const V &vertice) const;
    bool hayArco(const V & deVertice,const V & aVertice)const;

private:
    bool noDirigido_;
    unordered_map<V, unordered_map<V, C>> grafo;
};
