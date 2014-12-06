#include <iostream>
#include <list>
#include <stdlib.h>
#include "grafo.hpp"
using namespace std;

//cpc = custo parcial do caminho
int resultado = INF;
list<int> caminho;

void imprimeCaminho(vertice *vertices, int v_atual){
    if(v_atual){
        imprimeCaminho(vertices, vertices[v_atual].pai);
        cout << " " << v_atual;
    }
    else{
        cout << "0";
    }
}

void backtrack(vertice *vertices, list<int> l, int cpc, int v_atual){

    //cout << "cpc " << cpc << " " << v_atual << endl;
    if(l.empty()){                 //percorremos todos os vertices
        //exite a aresta para a origem?
        int custo_aresta = verificaAresta(vertices, v_atual, 0);
        //cout << "custo_aresta " << custo_aresta << endl;
        if(custo_aresta){           //se existe
        //    cout << "custo " << cpc + custo_aresta << endl;
            if((cpc + custo_aresta) < resultado){
                resultado = cpc + custo_aresta;
                vertices[0].pai = v_atual;
                //listaVertices(vertices, 3);
                //salvaCaminho();
                cout << "custo total " << cpc + custo_aresta << endl;
                imprimeCaminho(vertices, v_atual);
                cout << " 0" << endl;
            }
        }
    }
    else{
        aresta *a = vertices[v_atual].adjacente;
        while(a){
            if(vertices[a->dest].pai == -1){
                if(a->dest){
                    if((cpc + a->custo) < resultado){
                        l.remove(a->dest);
                        vertices[a->dest].pai = v_atual;
                        //listaVertices(vertices, 5);
                        backtrack(vertices, l, cpc+a->custo, a->dest);
                        vertices[a->dest].pai = -1;
                        l.push_back(a->dest);
                    }
                }
            }
            a = a->prox;
        }
    }

}

int main(){
    vertice *vertices;
    int n_ver, n_are, ori, dest, custo;
    list <int> l;
    cin >> n_ver >> n_are;
    vertices = (vertice*)malloc(n_ver * sizeof(vertice));
    inicializaGrafo(vertices, n_ver);
    for(int i = 0; i < n_are; i++){
        cin >> ori >> dest >> custo;
        insereAresta(vertices, ori, dest, custo);
    }
    for(int i = 1; i < n_ver; i++){
        l.push_back(i);
    }

    backtrack(vertices, l, 0, 0);

    liberaGrafo(vertices, n_ver);
    return 0;
}
