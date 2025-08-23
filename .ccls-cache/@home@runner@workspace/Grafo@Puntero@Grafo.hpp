#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
using namespace std;

template <class V, class C>
class Grafo
{
public:
    Grafo(); // por defecto se asume dirigido
    virtual ~Grafo();
    Grafo(bool noDirigido);

    bool addArco(const V &deVertice, const V &aVertice, const C &costo);
    bool addArco(const V &deVertice, const V &aVertice);
    bool delArco(const V &deVertice, const V &aVertice);
    bool hayArco(const V &deVertice, const V &aVertice) const;

    const C *getCosto(const V &deVertice, const V &aVertice) const;
    void setCosto(const V &deVertice, const V &aVertice, const C &costo);

    bool addVertice(const V &vertice);
    bool delVertice(const V &vertice);

    void imprimir() const;
    int nVertices() const;

    V *getVertices() const;
    V *getAdyacentes(const V &vertice) const;
    
    int getGradoSalida(const V &v) const;
    int getGrado(const V &v) const;

    // Métodos usados en la implementación con matriz de adyacencias y arreglos
    Grafo(int capacidad_maxima, bool es_no_dirigido);
    Grafo(int capacidad_maxima, bool es_no_dirigido, C sin_arista_val);

private:
    
    bool noDirigido; // No se hace esto de usar un flag para GD/GND según objetos. Deberíamos tener una clase Grafo y dos clases hijas GD y GND, pero será en el próximo cuatrimestre.

    /* *Estructuras para la lista de adyacencias con puntero** */
    struct Arco;
    struct Nodo
    {
        V etiqueta;
        int nodo;
        Nodo *sig;
        Arco *ady;
        int incidencias; // para reducir la complejidad a la hora de calcular grados, recorrer ady, ...
        int adyacencias; // lo mismo de la línea anterior
    };
    struct Arco
    {
        C valor;
        Arco *sig;
        Nodo *destino;
    };

    Nodo *grafoNodo;
    int nV;
    int nA;
    /* *** */

    /*** Estructuras para la matriz de adyacencias****/
    C **grafoMatriz;        // matriz de adyacencia
    V *grafoMatrizVertices; // arreglo de etiquetas
    int grafoMatrizN;       // capacidad máxima fija
    int grafoMatrizNVertices;
    C grafoMatrizSinArista; // valor sentinela: ausencia de arista
    void iniciarMatriz();
    void iniciarArreglo();
    int getClave(const V &v) const;
    /* *** */
};

#endif