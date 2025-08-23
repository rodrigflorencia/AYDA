
#include "Grafo.hpp"

/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias 
 * y la estructura base mapa.
 * @tparam V Tipo de dato para los vértices.
 */
template <class V>
Grafo<V>::Grafo()
{
    this->noDirigido = false;
}

/**
 * @brief Destructor. Actualmente no es necesario porque usamos map, que maneja su propia memoria.
 * O(n**n)  Destructor del map * Destructor del set
 */
template <class V>
Grafo<V>::~Grafo()
{
    
}

/**
 * @brief Constructor con parámetro para definir si el grafo es dirigido o no. O(1)
 * @param noDirigido Indica si el grafo es no dirigido.
 */
template <class V>
Grafo<V>::Grafo(bool noDirigido)
{
    this->noDirigido = noDirigido;
}

/**
 * @brief Agrega un vértice al grafo. La complejidad es O(log n). log del insert del map, cte el ctor vacio del set
 * @param v Vértice a agregar.

 */
template <class V>
void Grafo<V>::addVertice(const V &v)
{
    this->grafoMapa.insert({v, set<V>{}}); // el constructor vacio del set es O(1)
   
}

/**
 * @brief Agrega un arco entre dos vértices. Complejidad orden logaritmico.
 * @param u Vértice origen.
 * @param v Vértice destino.
 */
template <class V>
void Grafo<V>::addArco(const V &u, const V &v)
{
    this->addVertice(u); // O(log n)
    this->addVertice(v); // O(log n)
    this->grafoMapa[u].insert(v); // O(log n)
    if (this->noDirigido)
        this->grafoMapa[v].insert(u); // O(log n)
   
}

/**
 * @brief Verifica si existe un arco entre dos vértices. Costo computacional logaritmico O(log n)
 * @param u Vértice origen.
 * @param v Vértice destino.
 */
template <class V>
bool Grafo<V>::hayArco(const V &u, const V &v) const
{
    typename map<V, set<V>>::const_iterator it = grafoMapa.find(u); // O(log n)

    if (it == grafoMapa.end())
    {
        return false;
    }

    // Buscar v en la lista de adyacencia de u
    return it->second.find(v) != it->second.end();
}

/**
 * @brief Devuelve un conjunto con los adyacentes de un vértice. Costo logaritmico O(log n).
 * @param v Vértice de referencia.
 * @return Conjunto con los vértices adyacentes.
 */
template <class V>
set<V> Grafo<V>::getAdyacentes(const V &v) const
{
    if (grafoMapa.find(v) == grafoMapa.end()) //O(log n)
        return set<V>(); //O(1)
    return grafoMapa.find(v)->second; //O(log n)
}


/**
 * @brief Devuelve un conjunto con los vértices del grafo. Costo lineal O(n)
 * @param u Vértice de referencia.
 * @return Conjunto con los vértices del grafo.
 */
template <class V>
set<V> Grafo<V>::getVertices() const
{
    set<V> v;
    int i=0;
    for (typename map<V, set<V>>::const_iterator it = this->grafoMapa.begin(); it != this->grafoMapa.end(); it++)       
     v.insert(it->first);
    return v;

}

/**
 * @brief Devuelve la cantidad de vértices actuales del grafo. O(1)
 * @return Número de vértices.
 */
template <class V>
int Grafo<V>::nVertices() const
{
    return grafoMapa.size(); // O(1)
}

// ==============================================
// Instanciaciones explícitas de la plantilla
// ==============================================
template class Grafo<int>;
template class Grafo<char>;
template class Grafo<double>;
template class Grafo<string>;
