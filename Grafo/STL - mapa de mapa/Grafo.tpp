#include "Grafo.hpp"

/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias con map. 
 * Complejidad: O(1)
 * @tparam V Tipo de dato para los vértices.
 * @tparam C Tipo de dato para los costos/pesos de las aristas.
 */
template <class V, class C>
Grafo<V, C>::Grafo()
{
    this->noDirigido = false;
}

/**
 * @brief Destructor
 */
template <class V, class C>
Grafo<V, C>::~Grafo()
{
    
}

/**
 * @brief Constructor con parámetro para definir si el grafo es dirigido o no.
 * Complejidad: O(1)
 * @param noDirigido Indica si el grafo es no dirigido.
 */
template <class V, class C>
Grafo<V, C>::Grafo(bool noDirigido)
{
    this->noDirigido = noDirigido;
}

/**
 * @brief Agrega un vértice al grafo.
 * @param v Vértice a agregar.
 */
template <class V, class C>
void Grafo<V, C>::addVertice(const V &v)
{
    this->grafoMapa.emplace(v, map<V, C>{}).second;
}

/**
 * @brief Agrega un arco entre dos vértices con un costo específico.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @param c Costo o peso del arco.
 */
template <class V, class C>
void Grafo<V, C>::addArco(const V &u, const V &v, const C &c)
{
    this->grafoMapa[u].insert({v,c});
    if (this->noDirigido && u != v)
        this->grafoMapa[v].insert({u,c});
   
}

/**
 * @brief Agrega un arco entre dos vértices con un costo por defecto (C{}).
 * @param u Vértice origen.
 * @param v Vértice destino.
 */
template <class V, class C>
void Grafo<V, C>::addArco(const V &u, const V &v)
{
    return this->addArco(u, v, C{});
}

/**
 * @brief Verifica si existe un arco entre dos vértices.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si existe, false si no.
 */
template <class V, class C>
bool Grafo<V, C>::hayArco(const V &u, const V &v) const
{
    typename map<V, map<V, C>>::const_iterator it = this->grafoMapa.find(u);

    if (it == this->grafoMapa.end())
    {
        return false;
    }

    // Buscar v en la lista de adyacencia de u
    return it->second.find(v) != it->second.end();
}

/**
 * @brief Obtiene el costo de un arco entre dos vértices.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return Puntero constante al costo, o nullptr si no existe.
 */
template <class V, class C>
const C Grafo<V, C>::getPeso(const V &u, const V &v) const
{
    typename map<V, map<V, C>>::const_iterator itU =
        this->grafoMapa.find(u);
    if (itU == this->grafoMapa.end())
        return 0;

    const map<V, C> &fila = itU->second;

    typename map<V, C>::const_iterator itV = fila.find(v);
    if (itV == fila.end())
        return 0; // o nullptr

    // devolver puntero al costo almacenado
    return itV->second;
}

/**
 * @brief Devuelve una lista con los adyacentes de un vértice.
 * @param v Vértice de referencia.
 * @return Lista con los vértices adyacentes, o lista vacía si no hay adyacencias.
 */

template <class V, class C>
list<V> Grafo<V, C>::getAdyacentes(const V &v) const
{
   if (grafoMapa.find(v) == grafoMapa.end())
       return list<V>();
   const map<V, C> &ady = grafoMapa.find(v)->second;
  list< V> destino;
   for (typename map<V, C>::const_iterator it = ady.begin(); it != ady.end(); it++)
   {
       destino.push_back(it->first);
   }
   return destino;
}

/**
*
* O(n)
*/
template <class V, class C>
list<V> Grafo<V, C>::getVertices() const
{
   list<V> v ;
   for (typename map<V, map<V, C>>::const_iterator it = this->grafoMapa.begin();it != this->grafoMapa.end();it++){
       v.push_back(it->first); 
   }
   return v;
}


/**
 * @brief Devuelve la cantidad de vértices actuales del grafo.
 * Complejidad: O(1)
 * @return Número de vértices.
 */
template <class V, class C>
int Grafo<V, C>::nVertices() const
{
    return this->grafoMapa.size();
}


// ==============================================
// Instanciaciones explícitas de la plantilla
// ==============================================
template class Grafo<int, int>;
template class Grafo<char, int>;
template class Grafo<char, char>;
template class Grafo<int, char>;
template class Grafo<int, double>;
template class Grafo<double, double>;
template class Grafo<double, int>;
template class Grafo<char, double>;
template class Grafo<double, char>;
template class Grafo<string, int>;
template class Grafo<int, string>;
template class Grafo<string, string>;
