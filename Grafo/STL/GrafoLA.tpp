
#include "Grafo.hpp"
#include <algorithm>
/**
 * @brief Implementación de un grafo genérico utilizando lista de adyacencias.
 * @tparam V Tipo de dato para los vértices.
 */
template <class V> Grafo<V>::Grafo() {
  this->noDirigido = false;
  this->nV = 0;
}

/**
 * @brief Destructor.
 *
 */
template <class V> Grafo<V>::~Grafo() {}

/**
 * @brief Constructor con parámetro para definir si el grafo es dirigido o no.
 * @param noDirigido Indica si el grafo es no dirigido.
 */
template <class V> Grafo<V>::Grafo(bool noDirigido) {

  this->noDirigido = noDirigido;
  this->nV = 0;
}

/**
 * @brief Agrega un vértice al grafo.
 * @param v Vértice a agregar.
 */
template <class V> void Grafo<V>::addVertice(const V &v) {

  this->vertices.insert({v, this->nV});
  this->adyacencias.push_back(list<int>());
  this->nV++;
}

/**
 * @brief Agrega un arco entre dos vértices. Complejidad orden logaritmico.
 * @param u Vértice origen.
 * @param v Vértice destino.
 */
template <class V> void Grafo<V>::addArco(const V &u, const V &v) {

  this->addVertice(u);
  this->addVertice(v);
  int iU = this->vertices.find(u)->second;
  int iV = this->vertices.find(v)->second;
  this->adyacencias[iU].push_back(iV);

  if (this->noDirigido)
    this->adyacencias[iV].push_back(iU);
}

/**
 * @brief Verifica si existe un arco entre dos vértices.
 * @param u Vértice origen.
 * @param v Vértice destino.
 * @return true si existe, false si no.
 */
template <class V> bool Grafo<V>::hayArco(const V &u, const V &v) const {

  if ((this->vertices.end() == this->vertices.find(u)) ||
      (this->vertices.end() == this->vertices.find(v)))
    return false;
  int iU = this->vertices.find(u)->second;
  int iV = this->vertices.find(v)->second;
  if (find(this->adyacencias[iU].begin(), this->adyacencias[iU].end(), iV) ==
      this->adyacencias[iU].end())
    return false;
  return true;
}

/**
 * @brief Devuelve un conjunto con los adyacentes de un vértice.
 * @param v Vértice de referencia.
 * @return Conjunto con los vértices adyacentes.
 */
template <class V> set<V> Grafo<V>::getAdyacentes(const V &v) const {
  const int iV = this->vertices.find(v)->second;
  set<V> adyacentes;
  list<int> iA;
  int i = 0;

  for (typename map<V, int>::const_iterator v = vertices.begin();
       vertices.end() != v; v++) {
    if (find(this->adyacencias[iV].begin(), this->adyacencias[iV].end(),
             v->second) != this->adyacencias[iV].end())
      adyacentes.insert(v->first);
  }
  return adyacentes;
}

/**
 * @brief Devuelve un conjunto con los vértices del grafo. Costo lineal O(n)
 * @param u Vértice de referencia.
 * @return Conjunto con los vértices del grafo.
 */
template <class V> set<V> Grafo<V>::getVertices() const {
  set<V> v;
  for (typename map<V, int>::const_iterator it = this->vertices.begin();
       it != this->vertices.end(); it++)
    v.insert(it->first);
  return v;
}

/**
 * @brief Devuelve la cantidad de vértices actuales del grafo. O(1)
 * @return Número de vértices.
 */
template <class V> int Grafo<V>::nVertices() const {
  return this->nV; // O(1)
}

// ==============================================
// Instanciaciones explícitas de la plantilla
// ==============================================
template class Grafo<int>;
template class Grafo<char>;
template class Grafo<double>;
template class Grafo<string>;
