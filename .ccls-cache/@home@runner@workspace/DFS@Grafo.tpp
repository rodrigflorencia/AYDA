
#include "Grafo.hpp"

/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias con nordered_mapny set.
 * @tparam V Tipo de dato para los vértices.
 * @tparam C Tipo de dato para los costos/pesos de las aristas.
 */
template <class V>
Grafo<V>::Grafo()
{
    this->noDirigido = false;
}

/**
 * @brief Destructor. Actualmente no es necesario porque usamos map, que maneja su propia memoria.
 * Aunque podemos hacer clear que tiene una complejidad lineal del tamaño de la estructura.
 */
template <class V>
Grafo<V>::~Grafo()
{
    this->grafoMapa.clear();
}

/**
 * @brief Constructor con parámetro para definir si el grafo es dirigido o no.
 * @param noDirigido Indica si el grafo es no dirigido.
 */
template <class V>
Grafo<V>::Grafo(bool noDirigido)
{
    noDirigido = noDirigido;
}

/**
 * @brief Agrega un vértice al grafo. La complejidad es del orden logaritmico.
 * @param v Vértice a agregar.
 * @return true si el vértice se agrega, false si ya existía.
 */
template <class V>
bool Grafo<V>::addVertice(const V &v)
{
    grafoMapa.insert({v, set<V>{}});
    return true;
}

/**
 * @brief Agrega un arco entre dos vértices. Complejidad orden logaritmico.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si la arista se agrega correctamente.
 */
template <class V>
bool Grafo<V>::addArco(const V &u, const V &v)
{
    this->addVertice(u); // O(log n)
    this->addVertice(v); // O(log n)
    this->grafoMapa[u].insert(v); // O(log n)
    if (this->noDirigido)
        this->grafoMapa[v].insert(u); // O(log n)
    return true;
}

/**
 * @brief Verifica si existe un arco entre dos vértices. Costo computacional logaritmico
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si existe, false si no.
 */
template <class V>
bool Grafo<V>::hayArco(const V &u, const V &v) const
{
    typename map<V, set<V>>::const_iterator it = grafoMapa.find(u);

    if (it == grafoMapa.end())
    {
        return false;
    }

    // Buscar v en la lista de adyacencia de u
    return it->second.find(v) != it->second.end();
}

/**
 * @brief Devuelve un conjunto con los adyacentes de un vértice. Costo logaritmico.
 * @param v Vértice de referencia.
 * @return Puntero a un arreglo con los vértices adyacentes, o nullptr si no hay adyacencias.
 */
template <class V>
set<V> Grafo<V>::getAdyacentes(const V &v) const
{
    if (grafoMapa.find(v) == grafoMapa.end())
        return set<V>();
    return grafoMapa.find(v)->second;
}

/**
 * @brief Devuelve el grado (cantidad de adyacencias) de un vértice.
 * @param u Vértice de referencia.
 * @return Cantidad de vértices adyacentes, o -1 si el vértice no existe.
 */
template <class V>
int Grafo<V>::getGrado(const V &u) const
{
    // TODO hacer para grafo no dirigido
    return this->getGradoSalida(u);
}

/**
 * @brief Devuelve un conjunto con los vértices del grafo. Costo lineal
 * @param u Vértice de referencia.
 * @return Cantidad de vértices adyacentes, o -1 si el vértice no existe.
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
 * @brief Devuelve el grado de salida de un vértice.
 *        Solo útil si el grafo es dirigido.
 *   Costo  logaritmico.
 * @param u Vértice de referencia.
 * @return Grado de salida, o -1 si el grafo no es dirigido o el vértice no existe.
 */
template <class V>
int Grafo<V>::getGradoSalida(const V &u) const
{
    if (grafoMapa.find(u) == grafoMapa.end())
        return -1;
    return grafoMapa.find(u)->second.size();

}

/**
 * @brief Devuelve la cantidad de vértices actuales del grafo.
 * @return Número de vértices.
 */
template <class V>
int Grafo<V>::nVertices() const
{
    return grafoMapa.size();
}

// ==============================================
// Instanciaciones explícitas de la plantilla
// ==============================================
template class Grafo<int>;
template class Grafo<char>;
template class Grafo<double>;
template class Grafo<string>;
