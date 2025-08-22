#include "Grafo.hpp"
/**
 * @file GrafoMA.tpp
 * @brief Implementación de grafo con matriz de adyacencia y arreglo de etiquetas.
 *
 * Representación:
 *  - Matriz C** grafoMatriz de tamaño fijo N x N (capacidad).
 *  - Arreglo V* grafoMatrizVertices con hasta nVertices etiquetas.
 *  - Valor sentinela grafoMatrizSinArista indica ausencia de arista.
 *  - Modo dirigido/no dirigido configurable en el constructor.
 *  - void iniciarMatriz() método aux
 *  -  void iniciarArreglo() método aux
 *
 * Complejidad (siempre con N vertices fijo):
 *  - addVertice: O(1) amortizado (chequeo de capacidad) + O(1) asignación.
 *  - addArco / delArco / hayArco / getCosto: O(1) una vez conocidas las claves.
 *  - getClave: O(N)).
 *  - getGrado / getAdyacentes: O(N) en el peor caso por recorrer fila.
 *  - Espacio: O(N^2) + O(N).
 */

// =======================
// Constructores / Destructor
// =======================

/**
 * @brief Constructor por defecto.
 *
 * Crea grafo dirigido con capacidad N=1, sentinela -1 y 0 vértices cargados.
 * Llama a iniciarMatriz() e iniciarArreglo().
 */
template <typename V, typename C>
Grafo<V, C>::Grafo()
{
    this->grafoMatrizN = 1;
    this->noDirigido = false;
    this->grafoMatrizSinArista = -1;
    this->grafoMatrizNVertices = 0;
    this->iniciarMatriz();
    this->iniciarArreglo();
}

/**
 * @brief Constructor con capacidad y modo dirigido/no dirigido.
 * @param capacidad_maxima Tamaño máximo N de la matriz (se trunca a 1 si es <= 0).
 * @param es_no_dirigido true para grafo no dirigido; false para dirigido.
 * @post Matriz inicializada con sentinela; arreglo de etiquetas listo.
 */
template <typename V, typename C>
Grafo<V, C>::Grafo(int capacidad_maxima, bool es_no_dirigido)
{
    this->grafoMatrizN = capacidad_maxima;
    this->noDirigido = es_no_dirigido;
    this->grafoMatrizSinArista = -1;
    this->grafoMatrizNVertices = 0;
    if (this->grafoMatrizN <= 0)
        this->grafoMatrizN = 1;

    this->iniciarMatriz();
    this->iniciarArreglo();
}

/**
 * @brief Constructor con capacidad, modo y sentinela personalizado.
 * @param capacidad_maxima Tamaño máximo N de la matriz (se trunca a 1 si es <= 0).
 * @param es_no_dirigido true para no dirigido; false para dirigido.
 * @param sin_arista_val Valor que representa "no hay arista".
 */
template <typename V, typename C>
Grafo<V, C>::Grafo(int capacidad_maxima, bool es_no_dirigido, C sin_arista_val)
{
    this->grafoMatrizN = capacidad_maxima;
    this->noDirigido = es_no_dirigido;
    this->grafoMatrizSinArista = sin_arista_val;
    this->grafoMatrizNVertices = 0;
    if (this->grafoMatrizN <= 0)
        this->grafoMatrizN = 1;

    this->iniciarMatriz();
    this->iniciarArreglo();
}

/**
 * @brief Destructor. Libera matriz y arreglo de vértices.
 * @post nVertices() pasa a 0.
 */
template <typename V, typename C>
Grafo<V, C>::~Grafo()
{
    if (this->grafoMatriz)
    {
        for (int i = 0; i < this->grafoMatrizN; ++i)
            delete[] this->grafoMatriz[i];
        delete[] this->grafoMatriz;
    }
    delete[] this->grafoMatrizVertices;
    this->grafoMatrizNVertices = 0;
}

// =======================
// Consultas básicas
// =======================

/**
 * @brief Cantidad de vértices actualmente cargados.
 * @return nVertices (0..N).
 * @complexity O(1)
 */
template <typename V, typename C>
int Grafo<V, C>::nVertices() const { return this->grafoMatrizNVertices; }

/**
 * @brief Obtiene la clave/índice interno de un vértice por su etiqueta.
 * @param v Etiqueta a buscar.
 * @return índice [0..nVertices-1] si existe, o -1 si no existe.
 * @complexity O(nVertices)
 */
template <typename V, typename C>
int Grafo<V, C>::getClave(const V &v) const
{
    for (int i = 0; i < this->grafoMatrizN; i++)
        if (this->grafoMatrizVertices[i] == v)
            return i;
    return -1;
}

// =======================
// Gestión de vértices
// =======================

/**
 * @brief Agrega un vértice con etiqueta u si hay capacidad disponible.
 * @param u Etiqueta a insertar.
 * @return true si se insertó; false si no hay lugar.
 * @note No valida duplicados; si se requiere, verificar con getClave(u) antes.
 * @complexity O(1)
 */
template <typename V, typename C>
bool Grafo<V, C>::addVertice(const V &u)
{
    if (this->grafoMatrizNVertices < this->grafoMatrizN)
    {

        this->grafoMatrizVertices[this->grafoMatrizNVertices] = u;
        this->grafoMatrizNVertices++;
        return true;
    }
    else
    {
        return false;
    }
}

// =======================
// Gestión de aristas
// =======================

/**
 * @brief Agrega o actualiza la arista u->v con costo c.
 * @param u Origen.
 * @param v Destino.
 * @param c Costo/peso.
 * @return true si ambos vértices existen y se asignó el costo; false en caso contrario.
 * @complexity O(nVertices) por dos getClave + O(1) asignación.
 * @note En no-dirigido también setea v->u con el mismo costo.
 */
template <typename V, typename C>
bool Grafo<V, C>::addArco(const V &u, const V &v, const C &c)
{
    int iU = this->getClave(u);
    int iV = this->getClave(v);
    if (iU != -1 && iV != -1)
    {

        this->grafoMatriz[iU][iV] = c; // GD
        if (this->noDirigido)
            this->grafoMatriz[iV][iU] = c; // GND
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Elimina (pone sentinela) la arista u->v. En no-dirigido también v->u.
 * @param u Origen.
 * @param v Destino.
 * @return true si ambos vértices existen; false si alguno no existe.
 * @complexity O(nVertices) por dos getClave + O(1) asignación.
 */
template <typename V, typename C>
bool Grafo<V, C>::delArco(const V &u, const V &v)
{
    int iU = this->getClave(u);
    int iV = this->getClave(v);
    if (iU != -1 && iV != -1)
    {

        this->grafoMatriz[iU][iV] = this->grafoMatrizSinArista;
        if (this->noDirigido)
            this->grafoMatriz[iV][iU] = this->grafoMatrizSinArista;
        return true;
    }
    return false;
}

/**
 * @brief Indica si existe arista u->v (distinta del sentinela).
 * @param u Origen.
 * @param v Destino.
 * @return true si hay arista; false si no.
 * @complexity O(nVertices) + O(1).
 */
template <typename V, typename C>
bool Grafo<V, C>::hayArco(const V &u, const V &v) const
{
    int iU = this->getClave(u);
    int iV = this->getClave(v);
    if (iU == -1 || iV == -1)
        return false;
    return !(this->grafoMatriz[iU][iV] == this->grafoMatrizSinArista);
}

/**
 * @brief Devuelve un puntero constante al costo de u->v (o al sentinela si no existe).
 * @param u Origen.
 * @param v Destino.
 * @return &matriz[iU][iV] si ambos existen; de lo contrario, &grafoMatrizSinArista.
 * @complexity O(nVertices) + O(1).
 * @warning El puntero retornado es válido mientras no se destruya el grafo ni se cambie la arista/sentinela.
 */
template <typename V, typename C>
const C *Grafo<V, C>::getCosto(const V &u, const V &v) const
{
    int iU = getClave(u);
    int iV = getClave(v);
    if (iU == -1 || iV == -1)
        return &(this->grafoMatrizSinArista);
    return &(this->grafoMatriz[iU][iV]);
}

// =======================
// Impresión y métricas
// =======================

/**
 * @brief Imprime la matriz de adyacencia con las etiquetas como encabezados.
 * @complexity O(N^2).
 * @note Muestra N filas/columnas (capacidad), no solo los nVertices cargados.
 */
template <typename V, typename C>
void Grafo<V, C>::imprimir() const
{
    cout << "   ";
    for (int j = 0; j < this->grafoMatrizN; j++)
        cout << "[" << this->grafoMatrizVertices[j] << "] "; // clave del vertice destino: fila encabezado de la tabla a mostrar
    cout << "\n";
    for (int i = 0; i < this->grafoMatrizN; i++)
    {
        cout << "[" << this->grafoMatrizVertices[i] << "] "; // clave del vertice origen: columna encabezado de la tabla a mostrar
        for (int j = 0; j < this->grafoMatrizN; j++)
        {
            cout << this->grafoMatriz[i][j] << " "; // costo origen i a destino j
        }
        cout << "\n";
    }
}

/**
 * @brief Grado de salida del vértice u (cantidad de vecinos alcanzables desde u).
 * @param u Etiqueta del vértice.
 * @return Número de adyacentes salientes.
 * @complexity O(nVertices) para ubicar la clave + O(N) para recorrer la fila.
 */
template <typename V, typename C>
int Grafo<V, C>::getGradoSalida(const V &u) const
{
    int salida = 0;
    int ku = this->getClave(u);
    for (int i = 0; i < this->grafoMatrizN; i++)
    {
        if (this->grafoMatriz[i][ku] != this->grafoMatrizSinArista)
            salida++;
    }
    return salida;
}

/**
 * @brief Devuelve un arreglo con los adyacentes salientes de u.
 * @param u Etiqueta del vértice origen.
 * @return Arreglo dinámico de etiquetas V con tamaño getGrado(u); nullptr si u no existe o no tiene vecinos.
 * @complexity O(nVertices) + O(N). El llamador debe liberar con delete[].
 */
template <typename V, typename C>
vector<V> Grafo<V, C>::getAdyacentes(const V &u) const
// V *Grafo<V, C>::getAdyacentes(const V &u) const

{
    int key = this->getClave(u);
    vector<V> v;
    //V *v = new V[this->getGrado(key)];
    //int j = 0;
    for (int i = 0; i < this->grafoMatrizN; i++)
    {
        if (this->grafoMatriz[key][i] != this->grafoMatrizSinArista)
        {
            v.push_back(this->grafoMatrizVertices[i]);
            //v[j] = this->grafoMatrizVertices[i];
            //j++;
        }
    }
    return v;
}

// =======================
// Inicialización interna
// =======================

/**
 * @brief Reserva y llena la matriz N x N con el sentinela.
 * @post grafoMatriz queda alocado; todas las celdas = grafoMatrizSinArista.
 */
template <typename V, typename C>
void Grafo<V, C>::iniciarMatriz()
{
    this->grafoMatriz = new C *[this->grafoMatrizN];
    for (int i = 0; i < this->grafoMatrizN; i++)
        this->grafoMatriz[i] = new C[this->grafoMatrizN];

    for (int i = 0; i < this->grafoMatrizN; i++)
        for (int j = 0; j < this->grafoMatrizN; j++)
            this->grafoMatriz[i][j] = this->grafoMatrizSinArista;
}

/**
 * @brief Reserva el arreglo de etiquetas V y lo inicializa con el valor por defecto de V().
 * @post grafoMatrizVertices tiene N entradas inicializadas.
 */
template <typename V, typename C>
void Grafo<V, C>::iniciarArreglo()
{
    this->grafoMatrizVertices = new V[this->grafoMatrizN];
    for (int i = 0; i < this->grafoMatrizN; i++)
        this->grafoMatrizVertices[i] = nullptr || 0;
}

// =======================
// Instanciaciones explícitas
// =======================

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