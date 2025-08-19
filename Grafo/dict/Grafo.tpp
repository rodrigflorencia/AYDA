#include "Grafo.hpp"
template <class V, class C>
Grafo< V,  C>::Grafo()
{
   
}
template <class V, class C>
Grafo< V,  C>::~Grafo()
{

}
template <class V, class C>
Grafo< V,  C>::Grafo(bool noDirigido)
{
    noDirigido_=noDirigido;
}

template <class V, class C>
void Grafo< V,  C>::addVertice(const V& v)
{
    grafo.emplace(v, std::unordered_map<V, C> {}).second;
}

template <class V, class C>
void Grafo< V,  C>::addArco(const V& u, const V& v, const C& c)
{
    addVertice(u);
    addVertice(v);
    bool creada = grafo[u].find(v) == grafo[u].end();
    grafo[u][v] = c;
    if (noDirigido_ && u != v) grafo[v][u] = c;

}

template <class V, class C>
void Grafo< V,  C>::addArco(const V& u, const V& v)
{
    return addArco(u, v, C{});
}
template <class V, class C>
bool Grafo< V,  C>::hayArco(const V& u, const V& v) const
{
    auto it = grafo.find(u);
    return it != grafo.end() && it->second.find(v) != it->second.end();
}

template <class V, class C>
const C* Grafo< V,  C>::getCosto(const V& u, const V& v) const
{
    auto it = grafo.find(u);
    if (it == grafo.end()) return nullptr;
    auto jt = it->second.find(v);
    return jt == it->second.end() ? nullptr : &jt->second;
}

template <class V, class C>
const std::unordered_map<V, C>& Grafo< V,  C>::getAdyacentes(const V& v) const
{
    auto it = grafo.find(v);
    if (it == grafo.end()) return nullptr;
    return it->second;
}

template<class V, class C>
list<V> Grafo<V,C>::getVertices() const {
    list<V> vs;
  
    for (typename grafo::const_iterator it  = grafo.begin(); it != grafo.end(); it++) {
        vs.push_back(it->first); 
    }
    return vs; 
}


template <class V, class C>
int Grafo< V,  C>::nVertices() const
{
    return grafo.size();
}

template <class V, class C>
int Grafo< V,  C>::nAristas() const
{
    int sum = 0;
    for (typename grafo::const_iterator it  = grafo.begin(); it != grafo.end(); it++) 
      sum += it.second.size();
    return noDirigido_ ? sum / 2 : sum;
}

