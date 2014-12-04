#include <iostream>
#include <queue>
#include <stdlib.h>
#include "grafo.hpp"
using namespace std;


/*    priority_queue <TCasa> casas;
    casas.push(aux); //inserindo na fila de prioridades    }
    casas.empty()
    aux = casas.top (); //lê o de maior prioridade
    casas.pop (); */

bool operator<(const vertice& v1, const vertice& v2)
{
  return v1.valor < v2.valor;
}

int main(){
    vertice *vertices;
    int n_ver, n_are;//, i, ori, dest, custo, consultas;
    cin >> n_ver >> n_are;
    vertices = (vertice*)malloc(n_ver * sizeof(vertice));
    inicializaGrafo(vertices, n_ver);
    listaVertices(vertices, n_ver);
    listaArestas(vertices, n_ver);
    liberaGrafo(vertices, n_ver);
    return 0;
}
