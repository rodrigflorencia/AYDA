
#include "Grafo.hpp"

/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias con nordered_mapny set. O(1)
 * @tparam V Tipo de dato para los vértices.
 * @tparam C Tipo de dato para los costos/pesos de las aristas.
 */
template <class V>
Grafo<V>::Grafo()
{
    this->noDirigido = false;
}

/**
 * @brief Destructor. Actualmente no es necesario porque usamos unordered_map, que maneja su propia memoria.
 * Aunque podemos hacer clear. O(n) complejidad lineal del tamaño de la estructura.
 */
template <class V>
Grafo<V>::~Grafo()
{
    this->grafoMapa.clear();
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
 * @brief Agrega un vértice al grafo. La complejidad es O(log n)
 * @param v Vértice a agregar.
 * @return true si el vértice se agrega, false si ya existía.
 */
template <class V>
bool Grafo<V>::addVertice(const V &v)
{
    this->grafoMapa.insert({v, set<V>{}}); // el constructor vacio del set es O(1)
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
 * @brief Verifica si existe un arco entre dos vértices. Costo computacional logaritmico O(log n)
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si existe, false si no.
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
 * @return Puntero a un arreglo con los vértices adyacentes, o nullptr si no hay adyacencias.
 */
template <class V>
set<V> Grafo<V>::getAdyacentes(const V &v) const
{
    if (grafoMapa.find(v) == grafoMapa.end()) //O(log n)
        return set<V>(); //O(1)
    return grafoMapa.find(v)->second; //O(log n)
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
 * @brief Devuelve un conjunto con los vértices del grafo. Costo lineal O(n)
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
    // TODO
return -1;

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
