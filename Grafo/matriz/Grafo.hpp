// Grafo con matriz de adyacencia usando arreglos dinámicos.
// Capacidad fija.
// Requiere que V tenga operador == y que C sea copiable.

template <typename V, typename C>
class Grafo {
private:
    C** matriz;      // matriz de adyacencia (cap x cap)
    V* vertices;     // arreglo de etiquetas (cap)
    int cap;         // capacidad máxima fija
    bool no_dirigido;
    C sin_arista;    // valor sentinela: ausencia de arista

public:
    Grafo(int capacidad_maxima, bool es_no_dirigido, C sin_arista_val);
    ~Grafo();
    int nVertices() const;
    int getClave(const V& v) const;
    void agregarArista(const V& u, const V& v, const C& c);
    void agregarArista(const V& u, const V& v);
    void eliminarArista(const V& u, const V& v);
    bool hayArista(const V& u, const V& v) const;
    C obtenerPeso(const V& u, const V& v) const;
    int grado(const V& u) const ;
};
