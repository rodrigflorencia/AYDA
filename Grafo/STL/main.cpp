#include "Grafo.tpp"
int main()
{
  Grafo<char> g;
  
    g.addVertice('B');
    g.addVertice('C');
    g.addVertice('D');
    g.addVertice('A');
    g.addArco('A', 'B');
    g.addArco('A', 'C');
    g.addArco('C', 'B');
    g.addArco('B', 'D');

  cout << "Hay A-B? " << g.hayArco('A', 'B') << "\n";
  cout << "Hay C-B? " << g.hayArco('C', 'B') << "\n";

    cout << g;

  return 0;