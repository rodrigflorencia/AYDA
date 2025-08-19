#ifndef GRAFO_H_
#define GRAFO_H_

template <typename T, typename C>
class Grafo
{
private:
    struct Arco;
    struct Nodo
    {
        T etiqueta;
        int nodo;
        Nodo *sig;
        Arco *ady;
        int incidencias;
        int adyacencias;
    };

    struct Arco
    {
        C valor;
        Arco *sig;
        Nodo *destino;
    };

    Nodo *inicio;
    int nVertices;
    int nArcos;
    int grado;

public:
    Grafo();
    ~Grafo();
    void addVertice(const T &dato);
    void addArco(const T &o, const T &d, const C &peso);
    int getGrado() const;
    int getGradoVertice(const T &etiqueta) const;
    T *getVertices() const;
    T *getAdyacentes(const T &etiqueta) const;
    int nVertices() const;
    int nAdyacentes(const T &etiqueta) const;
};

#endif /* GRAFO_H_ */
