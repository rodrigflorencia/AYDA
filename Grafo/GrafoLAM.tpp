#include "Grafo.hpp"

/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias con nordered_map.
 * @tparam V Tipo de dato para los vértices.
 * @tparam C Tipo de dato para los costos/pesos de las aristas.
 */
template <class V, class C>
Grafo<V, C>::Grafo()
{
    this->noDirigido = false;
}

/**
 * @brief Destructor. Actualmente no es necesario porque usamos unordered_map, que maneja su propia memoria.
 */
template <class V, class C>
Grafo<V, C>::~Grafo()
{
    this->grafoMapa.clear();
}

/**
 * @brief Constructor con parámetro para definir si el grafo es dirigido o no.
 * @param noDirigido Indica si el grafo es no dirigido.
 */
template <class V, class C>
Grafo<V, C>::Grafo(bool noDirigido)
{
    noDirigido = noDirigido;
}

/**
 * @brief Agrega un vértice al grafo.
 * @param v Vértice a agregar.
 * @return true si el vértice se agrega, false si ya existía.
 */
template <class V, class C>
bool Grafo<V, C>::addVertice(const V &v)
{
    grafoMapa.emplace(v, unordered_map<V, C>{}).second;
    return true;
}

/**
 * @brief Agrega un arco entre dos vértices con un costo específico.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @param c Costo o peso del arco.
 * @return true si la arista se agrega correctamente.
 */
template <class V, class C>
bool Grafo<V, C>::addArco(const V &u, const V &v, const C &c)
{
    addVertice(u);
    addVertice(v);
    bool creada = grafoMapa[u].find(v) == grafoMapa[u].end();
    grafoMapa[u][v] = c;
    if (noDirigido && u != v)
        grafoMapa[v][u] = c;
    return true;
}

/**
 * @brief Agrega un arco entre dos vértices con un costo por defecto (C{}).
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si la arista se agrega correctamente.
 */
template <class V, class C>
bool Grafo<V, C>::addArco(const V &u, const V &v)
{
    return addArco(u, v, C{});
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
    typename std::unordered_map<V, std::unordered_map<V, C>>::const_iterator it = grafoMapa.find(u);

    if (it == grafoMapa.end())
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
const C *Grafo<V, C>::getCosto(const V &u, const V &v) const
{
    // iterador a la fila (u)
    typename unordered_map<V, unordered_map<V, C>>::const_iterator itU =
        grafoMapa.find(u);
    if (itU == grafoMapa.end())
        return 0;

    // referencia constante a la fila de u
    const unordered_map<V, C> &fila = itU->second;

    // iterador a la columna (v) dentro de la fila
    typename unordered_map<V, C>::const_iterator itV = fila.find(v);
    if (itV == fila.end())
        return 0; // o nullptr

    // devolver puntero al costo almacenado
    return &(itV->second);
}

/**
 * @brief Devuelve un arreglo dinámico con los adyacentes de un vértice.
 * @param v Vértice de referencia.
 * @return Puntero a un arreglo con los vértices adyacentes, o nullptr si no hay adyacencias.
 */
template <class V, class C>
V *Grafo<V, C>::getAdyacentes(const V &v) const
{
    auto x = grafoMapa.find(v);
    if (grafoMapa.find(v) == grafoMapa.end())
        return nullptr;
    const unordered_map<V, C> &ady = x->second;
    V *destino = new V[ady.size()];
    int i = 0;
    for (typename unordered_map<V, C>::const_iterator it = ady.begin(); it != ady.end(); it++)
    {
        destino[i] = it->first;
        i++;
    }
    return destino;
}

/**
 * @brief Devuelve el grado (cantidad de adyacencias) de un vértice.
 * @param u Vértice de referencia.
 * @return Cantidad de vértices adyacentes, o -1 si el vértice no existe.
 */
template <class V, class C>
int Grafo<V, C>::getGrado(const V &u) const
{
    if (grafoMapa.find(u) == grafoMapa.end())
        return -1;
    return grafoMapa.find(u)->second.size();
}

/**
 * @brief Devuelve el grado de salida de un vértice.
 *        Solo útil si el grafo es dirigido.
 * @param u Vértice de referencia.
 * @return Grado de salida, o -1 si el grafo no es dirigido o el vértice no existe.
 */
template <class V, class C>
int Grafo<V, C>::getGradoSalida(const V &u) const
{
    if (!noDirigido)
    {
        if (grafoMapa.find(u) == grafoMapa.end())
            return -1;
        return grafoMapa.find(u)->second.size();
    }
    return -1;
}
/**
 * @brief Devuelve la cantidad de vértices actuales del grafo.
 * @return Número de vértices.
 */
template <class V, class C>
int Grafo<V, C>::nVertices() const
{
    return grafoMapa.size();
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