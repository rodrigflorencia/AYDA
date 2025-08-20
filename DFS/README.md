# DFS

Su funcionamiento consiste en ir recorriendo cada uno de los nodos de forma recurrente, en un camino concreto. 

Cuando ya no quedan más nodos que visitar en dicho camino, regresa, de modo que repite el mismo proceso con cada uno de los hermanos del nodo ya procesado.

```
DFS(Grafo g)
  FOR vértice w ∈ g.obtenerVertices()
        estado[w] = BLANCO
        padre[w] = NULO

  FOR vértice w ∈ g.obtenerAdyacentes(w)
          IF estado[w] = BLANCO
                DFS_Visitar(w)

DFS_Visitar(Grafo g, Vertice v)
  estado[v] = AMARILLO
  FOR u ∈ g.obtenerAdyacentes(v)
    IF estado[u] = BLANCO
      padre[u] = v
      DFS_Visitar(u)
```

# Aplicaciones: clasificación de arcos y detección de ciclos

```
DFS(Grafo g)
  tiempo = 0
     FOR vértice w ∈ g.obtenerVertices()
             estado[w] = BLANCO
             padre[w] = NULO
             descubrimiento [w] = -1
             finalizacion[w] = -1
     FOR vértice w ∈ g.obtenerAdyacentes(w)
             IF estado[w] = BLANCO
                     DFS_Visitar(w)

DFS_Visitar(Grafo g, Vertice v)
     tiempo = tiempo + 1
  descubrimiento [v] = tiempo
     estado[v] = AMARILLO
     FOR u ∈ g.obtenerAdyacentes(v)
             IF estado[u] = BLANCO
                     padre[u] = v
                     DFS_Visitar(u)
     estado[v] = NEGRO
  tiempo = tiempo + 1
  finalizacion [v] = tiempo
```
## Seguimiento

![](img/Grafos-DFS.png)

![](img/Grafos-DFS%20(1).png)

![](img/Grafos-DFS%20(2).png)


![](img/Grafos-DFS%20(3).png)


![](img/Grafos-DFS%20(4).png)

![](img/Grafos-DFS%20(5).png)

![](img/Grafos-DFS%20(6).png)

![](img/Grafos-DFS%20(7).png)

![](img/Grafos-DFS%20(8).png)

![](img/Grafos-DFS%20(9).png)

![](img/Grafos-DFS%20(10).png)

![](img/Grafos-DFS%20(11).png)

![](img/Grafos-DFS%20(12).png)

![](img/Grafos-DFS%20(13).png)

![](img/Grafos-DFS%20(14).png)

![](img/Grafos-DFS%20(15).png)

![](img/Grafos-DFS%20(16).png)

![](img/Grafos-DFS%20(17).png)

![](img/Grafos-DFS%20(18).png)

![](img/Grafos-DFS%20(19).png)

![](img/Grafos-DFS%20(20).png)

![](img/Grafos-DFS%20(21).png)


