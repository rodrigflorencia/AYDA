#include "Grafo.hpp"

template <typename V, typename C>

// O(n*n) n cantidad de vertices
// Grafo no pesado
Grafo<V,C>::Grafo(int capacidad_maxima, bool es_no_dirigido) {
       cap = capacidad_maxima;
       no_dirigido = es_no_dirigido
      sin_arista =  -1;
       
       if (cap <= 0) cap = 1;

        // reservar matriz cap x cap
        matriz = new C*[cap];
        for (int i = 0; i < cap; ++i) matriz[i] = new C[cap];

        // inicializar con sentinela
        for (int i = 0; i < cap; ++i)
            for (int j = 0; j < cap; ++j)
                matriz[i][j] = sin_arista;

        // reservar arreglo de vértices
        vertices = new V[cap];
    }

// O(n*n) n cantidad de vertices
// Grafo  pesado
Grafo<V,C>::Grafo(int capacidad_maxima, bool es_no_dirigido, C sin_arista_val) {
       cap = capacidad_maxima;
       no_dirigido = es_no_dirigido
      sin_arista =  sin_arista_val;
       
       if (cap <= 0) cap = 1;

        // reservar matriz cap x cap
        matriz = new C*[cap];
        for (int i = 0; i < cap; ++i) matriz[i] = new C[cap];

        // inicializar con sentinela
        for (int i = 0; i < cap; ++i)
            for (int j = 0; j < cap; ++j)
                matriz[i][j] = sin_arista;

        // reservar arreglo de vértices
        vertices = new V[cap];
    }

// O(n) n cantidad de vertices
template <typename V, typename C>
Grafo<V,C>::~Grafo() {
        if (matriz) {
            for (int i = 0; i < cap; ++i) delete[] matriz[i];
            delete[] matriz;
        }
        delete[] vertices;
    }

// cantidad de vértices 
// O(1)
template <typename V, typename C>
int Grafo<V,C>:: nVertices() const { return cap; }

// índice de v o -1 si no existe
// O(n) n cantidad de vertices
template <typename V, typename C>
int Grafo<V,C>:: getClave(const V& v) const {
        for (int i = 0; i < n; ++i)
            if (vertices[i] == v) return i;
        return -1;
    }

// Agrega o actualiza una arista u->v con costo c. Si el grafo no es dirigido y no_dirigido==true, también v->u.
template <typename V, typename C>
void Grafo<V,C>::agregarArista(const V& u, const V& v, const C& c) {
  int iU = getClave(u);
  int iV = getClave(v);
  if (iU == -1) iU = insertarVertice(u);
  if (iV == -1) iV = insertarVertice(v);

  matriz[iU][iV] = c;              // GD
  if (no_dirigido) matriz[iV][iU] = c; // GND
}

// Elimina arista estableciendo sin_arista
template <typename V, typename C>
void Grafo<V,C>::eliminarArista(const V& u, const V& v) {
        int iU = getClave(u);
        int iV = getClave(v);
        if (iU == -1 || iV == -1) return;
        matriz[iU][iV] = sin_arista;
        if (no_dirigido) matriz[iV][iU] = sin_arista;
    }

// ¿Existe arista?
template <typename V, typename C>
bool Grafo<V,C>::hayArista(const V& u, const V& v) const {
        int iU = getClave(u);
        int iV = getClave(v);
        if (iU == -1 || iV == -1) return false;
        return !(matriz[iU][iV] == sin_arista);
}

    // Obtiene peso; si no existe, devuelve sin_arista
template <typename V, typename C>
C Grafo<V,C>:: obtenerPeso(const V& u, const V& v) const {
        int iU = getClave(u);
        int iV = getClave(v);
        if (iU == -1 || iV == -1) return sin_arista;
        return matriz[iU][iV];
    }

// Grado de un vértice (para no dirigido = nº de vecinos; para dirigido: out-degree)
template <typename V, typename C>
int Grafo<V,C>:: getGrado(const V& u) const {
        int iU = getClave(u);
        if (iU == -1) return 0;
        int g = 0;
        for (int j = 0; j < n; ++j)
            if (!(matriz[iU][j] == sin_arista)) g++;
        return g;
}

// Impresión del grafo
template <typename V, typename C>
void Grafo<V,C>::imprimir() const {
        cout << "   ";
        for (int j = 0; j < n; ++j) cout << "[" << j << "] "; // clave del vertice destino: fila encabezado de la tabla a mostrar
        cout << "\n";
        for (int i = 0; i < n; ++i) {
            cout << "[" << i << "] "; // clave del vertice origen: columna encabezado de la tabla a mostrar
            for (int j = 0; j < n; ++j) {
                cout << matriz[i][j] << " "; // costo origen i a destino j
            }
            cout << "\n";
        }
    }
};

// ---------------------------
// Ejemplo de uso:
// ---------------------------
/*
int main() {
    // Grafo no dirigido con pesos int; -1 indica "sin arista"
    Grafo<char, int> g(4, true, -1);

    g.insertarVertice('A');
    g.insertarVertice('B');
    g.insertarVertice('C');

    g.agregarArista('A', 'B', 7);
    g.agregarArista('A', 'C', 5);

    cout << "Clave(B) = " << g.getClave('B') << "\n";
    cout << "Hay A-B? " << g.hayArista('A','B') << "\n";
    cout << "Peso A-C = " << g.obtenerPeso('A','C') << "\n";
    cout << "Grado(A) = " << g.grado('A') << "\n\n";

    g.imprimirMatriz();
}
*/
