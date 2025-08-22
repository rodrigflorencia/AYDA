/**
 * @file Grafo.tpp
 * @brief Implementación de un grafo con listas enlazadas propias (sin STL para nodos/aristas).
 *
 * Representación: cada vértice es un nodo enlazado (lista simple). Cada nodo mantiene
 * una lista enlazada de Arco que representan las adyacencias salientes.
 * Soporta grafos dirigidos y no dirigidos (controlado por @c noDirigido).
 *
 * @tparam TipoVertice tipo de la etiqueta de cada vértice (debe tener operador == y ser copiable).
 * @tparam TipoArco tipo del peso/costo del arco (debe ser copiable).
 *
 * @section ownership Propiedad de memoria
 * - @c getVertices y @c getAdyacentes devuelven arreglos @c new[] que deben liberarse con @c delete[] por el llamador.
 *
 * @section complexity Complejidades globales
 * - Estructura por listas enlazadas: operaciones típicas dependen del grado o del número de vértices/aristas.
 * - Espacio: O(n + m).
 */
#include "Grafo.hpp"

// =======================
// Constructores / dtor
// =======================

/**
 * @brief Constructor por defecto del grafo.
 *
 * Inicializa un grafo vacío @b dirigido (noDirigido = false).
 *
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(1)
 */
template <class TipoVertice, class TipoArco>
Grafo<TipoVertice, TipoArco>::Grafo()
{
    this->grafoNodo = nullptr;
    this->nV = 0;
    this->nA = 0;
    this->noDirigido = false; // por defecto se asume dirigido
}

/**
 * @brief Constructor que permite especificar si el grafo es no dirigido.
 *
 * @param noDir Si es true, el grafo será no dirigido; si es false, será dirigido.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(1)
 */
template <class TipoVertice, class TipoArco>
Grafo<TipoVertice, TipoArco>::Grafo(bool noDir)
{
    this->grafoNodo = nullptr;
    this->nV = 0;
    this->nA = 0;
    this->noDirigido = !(!noDir) ? true : false; // asegurar bool
}

/**
 * @brief Destructor. Libera todos los nodos y aristas.
 *
 * Recorre la lista de nodos y, para cada nodo, libera su lista de aristas.
 * Deja el grafo en estado vacío.
 *
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n + m), n vertices y m aristas
 */
template <class TipoVertice, class TipoArco>
Grafo<TipoVertice, TipoArco>::~Grafo()
{
    Nodo *tempNodo = grafoNodo;
    while (tempNodo != nullptr)
    {
        Arco *tempArco = tempNodo->ady;
        while (tempArco != nullptr)
        {
            Arco *arcoAEliminar = tempArco;
            tempArco = tempArco->sig;
            delete arcoAEliminar;
        }
        Nodo *nodoAEliminar = tempNodo;
        tempNodo = tempNodo->sig;
        delete nodoAEliminar;
    }
    grafoNodo = nullptr;
    nV = 0;
    nA = 0;
}

// =======================
// Alta / baja de vértices
// =======================

/**
 * @brief Agrega un nuevo vértice al grafo.
 *
 * @param o Etiqueta del vértice.
 * @return true si se agregó exitosamente, false si el vértice ya existía.
 * @complexity O(n), ya que recorre todos los vértices para evitar duplicados.
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::addVertice(const TipoVertice &o)
{
    // Verificar duplicado
    Nodo *tmp = this->grafoNodo;
    while (tmp != nullptr)
    {
        if (tmp->etiqueta == o)
            return false;
        tmp = tmp->sig;
    }

    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->ady = nullptr;
    nuevoNodo->sig = nullptr;
    nuevoNodo->etiqueta = o;
    nuevoNodo->incidencias = 0;
    nuevoNodo->adyacencias = 0;
    nuevoNodo->nodo = this->nV; // índice lógico al momento del alta

    if (this->grafoNodo == nullptr)
    {
        this->grafoNodo = nuevoNodo;
    }
    else
    {
        Nodo *tail = this->grafoNodo;
        while (tail->sig != nullptr)
            tail = tail->sig;
        tail->sig = nuevoNodo;
    }
    this->nV += 1;
    return true;
}

/**
 * @brief Elimina el vértice con etiqueta @p vertice y todas sus aristas incidentes.
 *
 * Quita aristas entrantes desde otros vértices y las salientes desde el propio vértice.
 *
 * @param vertice Etiqueta del vértice a eliminar.
 * @return true si se eliminó; false si no existe el vértice.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n + m) por limpieza de aristas entrantes y salientes.
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::delVertice(const TipoVertice &vertice)
{
    // Buscar nodo a borrar y su anterior
    Nodo *prev = nullptr;
    Nodo *cur = this->grafoNodo;
    while (cur != nullptr && !(cur->etiqueta == vertice))
    {
        prev = cur;
        cur = cur->sig;
    }
    if (cur == nullptr)
        return false; // no existe

    // Eliminar TODAS las aristas que entran a 'cur' desde otros nodos
    Nodo *it = this->grafoNodo;
    while (it != nullptr)
    {
        if (it != cur)
        {
            // borrar aristas it -> cur
            Arco *aprev = nullptr;
            Arco *a = it->ady;
            while (a != nullptr)
            {
                if (a->destino == cur)
                {
                    // eliminar a
                    if (aprev == nullptr)
                        it->ady = a->sig;
                    else
                        aprev->sig = a->sig;
                    delete a;
                    it->adyacencias--;  // salió una arista desde 'it'
                    cur->incidencias--; // entraba a 'cur'
                    this->nA--;
                    a = (aprev == nullptr) ? it->ady : aprev->sig;
                }
                else
                {
                    aprev = a;
                    a = a->sig;
                }
            }
        }
        it = it->sig;
    }

    // Eliminar TODAS las aristas que salen de 'cur'
    Arco *a = cur->ady;
    while (a != nullptr)
    {
        Arco *del = a;
        a = a->sig;
        del->destino->incidencias--; // le quitamos una entrada al destino
        this->nA--;
        delete del;
    }
    cur->ady = nullptr;
    cur->adyacencias = 0;

    // Quitar 'cur' de la lista de nodos
    if (prev == nullptr)
        this->grafoNodo = cur->sig;
    else
        prev->sig = cur->sig;

    delete cur;
    this->nV--;
    return true;
}

// =======================
// Aristas (add / del / query)
// =======================

/**
 * @brief Agrega una arista @c o -> @c d con peso @p peso. En no dirigido, agrega también @c d -> @c o si no existe.
 *
 * No agrega vértices automáticamente: si @c o o @c d no están, devuelve false.
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @param peso Peso/costo de la arista.
 * @return true si se agregó; false si no existen los vértices o la arista ya existía.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n) para encontrar el vertice origen entre los n vertices + verificar duplicado (grado(o)) +  insertar cte
 * @note En grafo no dirigido suma dos aristas y actualiza contadores en ambos sentidos.
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::addArco(const TipoVertice &o, const TipoVertice &d, const TipoArco &peso)
{
    // Ubicar origen y destino
    Nodo *tempOrigen = this->grafoNodo;
    while (tempOrigen != nullptr && !(tempOrigen->etiqueta == o))
        tempOrigen = tempOrigen->sig;
    if (tempOrigen == nullptr)
        return false;

    Nodo *tempDestino = this->grafoNodo;
    while (tempDestino != nullptr && !(tempDestino->etiqueta == d))
        tempDestino = tempDestino->sig;
    if (tempDestino == nullptr)
        return false;

    // Verificar si ya existe arco o->d
    Arco *aux = tempOrigen->ady;
    while (aux != nullptr)
    {
        if (aux->destino == tempDestino)
            return false; // ya existe
        aux = aux->sig;
    }

    // Insertar al inicio de la lista de adyacencia (O(1))
    Arco *nuevoArco = new Arco;
    nuevoArco->valor = peso;
    nuevoArco->destino = tempDestino;
    nuevoArco->sig = tempOrigen->ady;
    tempOrigen->ady = nuevoArco;

    tempOrigen->adyacencias++;
    tempDestino->incidencias++;
    this->nA++;

    // Si no dirigido, insertar también d->o si no existe
    if (this->noDirigido)
    {
        // Verificar si ya existe d->o
        Arco *aux2 = tempDestino->ady;
        bool existe2 = false;
        while (aux2 != nullptr && !existe2)
        {
            if (aux2->destino == tempOrigen)
            {
                existe2 = true;
            }
            aux2 = aux2->sig;
        }
        if (!existe2)
        {
            Arco *nuevoArco2 = new Arco;
            nuevoArco2->valor = peso;
            nuevoArco2->destino = tempOrigen;
            nuevoArco2->sig = tempDestino->ady;
            tempDestino->ady = nuevoArco2;
            tempDestino->adyacencias++;
            tempOrigen->incidencias++;
            this->nA++;
        }
    }
    return true;
}

/**
 * @brief Agrega una arista @c o -> @c d con peso por defecto de @c TipoArco().
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @return true si se agregó; false si no existen los vértices o la arista ya existía.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity Igual a @c addArco(o,d,peso).
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::addArco(const TipoVertice &o, const TipoVertice &d)
{
    // Usa valor por defecto de TipoArco
    TipoArco def = TipoArco();
    return addArco(o, d, def);
}

/**
 * @brief Elimina la arista @c o -> @c d. En no dirigido, elimina también @c d -> @c o.
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @return true si la arista existía y fue eliminada; false en caso contrario.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(o+grado(o)) para localizar y eliminar; en no dirigido también + O(d+grado(d)).
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::delArco(const TipoVertice &o, const TipoVertice &d)
{
    // Buscar nodos
    Nodo *origen = this->grafoNodo;
    while (origen != nullptr && !(origen->etiqueta == o))
        origen = origen->sig;
    if (origen == nullptr)
        return false;

    Nodo *dest = this->grafoNodo;
    while (dest != nullptr && !(dest->etiqueta == d))
        dest = dest->sig;
    if (dest == nullptr)
        return false;

    bool borrado = false;

    // Borrar o->d en lista de 'origen'
    Arco *aprev = nullptr;
    Arco *a = origen->ady;
    while (a != nullptr && !borrado)
    {
        if (a->destino == dest)
        {
            if (aprev == nullptr)
                origen->ady = a->sig;
            else
                aprev->sig = a->sig;
            delete a;
            origen->adyacencias--;
            dest->incidencias--;
            this->nA--;
            borrado = true;
        }
        aprev = a;
        a = a->sig;
    }

    if (!borrado || !noDirigido)
        return false;
    borrado = false;
    // Si no dirigido, borrar también d->o
    aprev = nullptr;
    a = dest->ady;
    while (a != nullptr && !borrado)
    {
        if (a->destino == origen)
        {
            if (aprev == nullptr)
                dest->ady = a->sig;
            else
                aprev->sig = a->sig;
            delete a;
            dest->adyacencias--;
            origen->incidencias--;
            this->nA--;
            borrado = true;
        }
        aprev = a;
        a = a->sig;
    }

    return borrado;
}

/**
 * @brief Indica si existe la arista @c o -> @c d.
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @return true si existe, false en caso contrario.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n) porque n vertices y grado (n) para la arista
 */
template <class TipoVertice, class TipoArco>
bool Grafo<TipoVertice, TipoArco>::hayArco(const TipoVertice &o, const TipoVertice &d) const
{
    const Nodo *origen = this->grafoNodo;
    const Nodo *dest = this->grafoNodo;

    while (origen != nullptr && !(origen->etiqueta == o))
        origen = origen->sig;
    if (origen == nullptr)
        return false;

    while (dest != nullptr && !(dest->etiqueta == d))
        dest = dest->sig;
    if (dest == nullptr)
        return false;

    const Arco *a = origen->ady;
    while (a != nullptr)
    {
        if (a->destino == dest)
            return true;
        a = a->sig;
    }
    return false;
}

/**
 * @brief Obtiene el puntero constante al costo de la arista @c o -> @c d.
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @return Puntero al costo si existe la arista; @c nullptr si no existe.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n) porque n vertices y grado (n) para la arista
 *
 * @warning El puntero retornado es válido mientras no se modifique/elimine la arista o el grafo.
 */
template <class TipoVertice, class TipoArco>
const TipoArco *Grafo<TipoVertice, TipoArco>::getCosto(const TipoVertice &o, const TipoVertice &d) const
{
    const Nodo *origen = this->grafoNodo;
    const Nodo *dest = this->grafoNodo;
    while (origen != nullptr && !(origen->etiqueta == o))
        origen = origen->sig;
    if (origen == nullptr)
        return 0;
    while (dest != nullptr && !(dest->etiqueta == d))
        dest = dest->sig;
    if (dest == nullptr)
        return 0;

    const Arco *a = origen->ady;
    while (a != nullptr)
    {
        if (a->destino == dest)
            return &(a->valor);
        a = a->sig;
    }
    return 0;
}

/**
 * @brief Actualiza el costo de la arista @c o -> @c d (y opcionalmente @c d -> @c o).
 *
 * Si el grafo es no dirigido, intenta actualizar también la arista inversa si existe.
 *
 * @param o Vértice origen.
 * @param d Vértice destino.
 * @param costo Nuevo valor del costo.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n) porque n vertices y grado (n) para la arista
 */
template <class TipoVertice, class TipoArco>
void Grafo<TipoVertice, TipoArco>::setCosto(const TipoVertice &o, const TipoVertice &d, const TipoArco &costo)
{
    Nodo *origen = this->grafoNodo;
    Nodo *dest = this->grafoNodo;
    while (origen != nullptr && !(origen->etiqueta == o))
        origen = origen->sig;
    if (origen == nullptr)
        return;
    while (dest != nullptr && !(dest->etiqueta == d))
        dest = dest->sig;
    if (dest == nullptr)
        return;

    Arco *a = origen->ady;
    bool corte= false;
    while (a != nullptr && !corte)
    {
        if (a->destino == dest)
        {
            a->valor = costo;
            corte = true
        }
        a = a->sig;
    }

    if (this->noDirigido)
    {
        // actualizar también d->o si existe
        a = dest->ady;
        corte= false;
        while (a != nullptr && !corte)
        {
            if (a->destino == origen)
            {
                a->valor = costo;
                corte = true
            }
            a = a->sig;
        }
    }
}

// =======================
// Consultas
// =======================

/**
 * @brief Retorna la cantidad de vértices actuales.
 * @return Número de vértices.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(1)
 */
template <class TipoVertice, class TipoArco>
int Grafo<TipoVertice, TipoArco>::nVertices() const
{
    return this->nV;
}

/**
 * @brief Devuelve un arreglo con las etiquetas adyacentes a @p etiqueta.
 *
 * Si el vértice no existe o no tiene adyacentes, retorna @c nullptr.
 * El tamaño del arreglo es igual al grado de salida del vértice.
 *
 * @param etiqueta Vértice cuyo vecindario se solicita.
 * @return Arreglo dinámico con etiquetas adyacentes o @c nullptr.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n). n hasta encontrar el vertice, + grado (n) para encontrar la arista
 * @warning El llamador debe liberar el arreglo con @c delete[].
 */
template <class TipoVertice, class TipoArco>
TipoVertice* Grafo<TipoVertice, TipoArco>::getAdyacentes(const TipoVertice &etiqueta) const
{
    
    Nodo *temp = this->grafoNodo;
    while (temp != nullptr && !(temp->etiqueta == etiqueta))
        temp = temp->sig;

    if (temp != nullptr && temp->adyacencias > 0)
    {
        TipoVertice *arcos = new TipoVertice[temp->adyacencias];
        int i = 0;
        Arco *aux = temp->ady;
        while (aux != nullptr)
        {
            arcos[i] = aux->destino->etiqueta;
            aux = aux->sig;
            i++;
        }
        return arcos;
    }
    return nullptr;
}

/**
 * @brief Devuelve un arreglo con todas las etiquetas de vértices en el grafo.
 *
 * El orden corresponde al orden de alta (recorrido de la lista de nodos).
 *
 * @return Arreglo dinámico con @c nV elementos.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n) con n vertices
 * @warning El llamador debe liberar el arreglo con @c delete[].
 */
template <class TipoVertice, class TipoArco>
TipoVertice* Grafo<TipoVertice, TipoArco>::getVertices() const
//TipoVertice *Grafo<TipoVertice, TipoArco>::getVertices() const
{
    // TODO
    return nullptr;
}

/**
 * @brief Retorna el grado de salida del vértice @p v.
 *
 * En grafos no dirigidos, coincide con el grado usual.
 *
 * @param v Etiqueta del vértice.
 * @return Número de adyacencias salientes de @p v.
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O() para ubicar el nodo + O(1) para leer el contador.
 */
template <class TipoVertice, class TipoArco>
int Grafo<TipoVertice, TipoArco>::getGradoSalida(const TipoVertice &v) const
{
    const Nodo *temp = this->grafoNodo;
    while (temp != nullptr && !(temp->etiqueta == v))
        temp = temp->sig;
    if (temp == nullptr)
        return 0;
    return temp->adyacencias; // out-degree; en no-dirigido coincide con grado
}

/**
 * @brief Imprime por pantalla la lista de adyacencia y un resumen del grafo.
 *
 * Formato: por cada vértice, imprime sus aristas salientes como "u -> v [peso]".
 *
 * @tparam TipoVertice
 * @tparam TipoArco
 * @complexity O(n+m) n vertices y m aristas.
 */
template <class TipoVertice, class TipoArco>
void Grafo<TipoVertice, TipoArco>::imprimir() const
{
    const Nodo *u = this->grafoNodo;
    while (u != nullptr)
    {
        cout << u->etiqueta << " :";
        const Arco *a = u->ady;
        if (a == nullptr)
            cout << " (sin adyacentes)";
        while (a != nullptr)
        {
            cout << " -> " << a->destino->etiqueta << " [" << a->valor << "]";
            a = a->sig;
        }
        cout << "\n";
        u = u->sig;
    }
    cout << "Vértices: " << this->nV << " | Aristas almacenadas: " << this->nA
         << (this->noDirigido ? " (no dirigido)\n" : " (dirigido)\n");
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