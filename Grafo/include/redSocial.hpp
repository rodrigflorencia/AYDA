/***
# Problema

Diseñar e implementar un algoritmo que recomiende cuentas que puede llegar a
interesarle seguir a un usuario particular de Instagram. Se considera que un
usuario V pueden estar interesado en seguir a la cuenta X si:

- V no sigue a X
- V sigue a alguien (W) que sigue a X

Proponer un algoritmo. Detallar y justificar la complejidad algoritmica.

[Enlace](https://docs.google.com/presentation/d/1Vg2iaw6ReFesm8Y9lWVmOHGchKJuyKcPUN3SDf15-Z8/edit)
**/
#ifndef REDSOCIAL_H_
#define REDSOCIAL_H_

#include "mapa/Grafo.hpp"
#include <map>
#include <queue>
#include <set>

template <typename V> set<V> recomendaciones(Grafo<V> redSocial, V usuario) {
  set<V> visitado;
  visitado.insert(usuario);
  map<V, int> orden;
  orden.insert({usuario, 0});

  set<V> recomendaciones;
  queue<V> q;
  q.push(usuario);
  while (!q.empty()) {
    V v = q.front();
    q.pop();
    set<V> ady = redSocial.getAdyacentes(v);
    for (typename set<V>::iterator w = ady.begin(); w != ady.end(); w++) {
      if (visitado.find(*w) == visitado.end()) {
        visitado.insert(*w);
        int ordenW = orden[v] + 1;
        orden.insert({*w, ordenW});
        if (ordenW == 2)
          recomendaciones.insert(*w);
        else
          q.push(*w);
      }
    }
  }
  return recomendaciones;
}
template <typename V> void mostrarRecomendaciones(set<V> r) {
  for (typename set<V>::const_iterator it = r.begin(); it != r.end(); it++)
    cout << *it << " ; ";
}

#endif /* REDSOCIAL_H_ */
