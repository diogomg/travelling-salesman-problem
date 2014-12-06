#include <iostream>
#include <list>
#include <stdlib.h>
#include "grafo.hpp"
using namespace std;

int resultado = INF;
list<int> caminho;

/*
@input:
    lista de adjacencia do grafo
*/
void imprimeCaminho(vertice *vertices){

    list<int>::iterator it;

    for (it=caminho.begin(); it!=caminho.end(); ++it)
        cout << *it << ' ';
    cout << '0' << endl;
}

/*
adiciona na lista 'caminho' os vertices que compoe o menor caminho
a insercao é feita do ultimo vertice do caminho(ignorando a volta para a origem)
para o começo. O lista porem fica organizada da forma correta.

@input:
    lista de adjacencia do grafo;
    ultimo vertice adicionado ao caminho
*/
void salvaCaminho(vertice *vertices, int v_atual){

    caminho.clear();//exclui caminho anterior
    while(v_atual){ //vertice nao é a origem
        caminho.push_front(v_atual);//adiciona no comeco da lista
        v_atual = vertices[v_atual].pai;//atualiza o vertice
    }
    caminho.push_front(0);//adiciona o vertice inicial
}

/*
@input:
    lista de adjacencia do grafo;
    lista de vertices nao adicionados ao caminho;
    cpc = custo parcial do caminho;
    ultimo vertice adicionado ao caminho
*/
void backtrack(vertice *vertices, list<int> l, int cpc, int v_atual){

    //lista vazia == nenhum vertice para se adicionar ao caminho
    if(l.empty()){

        //exite a aresta para a origem?
        //custo 0 == aresta nao existe
        int custo_aresta = verificaAresta(vertices, v_atual, 0);
        if(custo_aresta){           //se existe

            //novo caminho possui um custo melhor que o atual?
            if((cpc + custo_aresta) < resultado){
                //atualiza o custo final
                resultado = cpc + custo_aresta;
                //atualiza o caminho
                vertices[0].pai = v_atual;
                salvaCaminho(vertices, v_atual);
            }
        }
    }
    else{//ha vertices para se adicionar ao caminho
        aresta *a = vertices[v_atual].adjacente;//lista de arestas
        while(a){//verifica todas as arestas

            /*verifica se a aresta nao aponta para um
            vertice ja adicionado no caminho*/
            if(vertices[a->dest].pai == -1){
                if(a->dest){//aresta ainda nao pode apontar para a origem
                    /*branch and bound
                    ainda é viavel proceguir no caminho?*/
                    if((cpc + a->custo) < resultado){//se sim
                        //remove o vertice da lista de vertices nao adicionados
                        l.remove(a->dest);
                        vertices[a->dest].pai = v_atual;//atualiza referencias
                        //explora caminho a partir de a->dest
                        backtrack(vertices, l, cpc+a->custo, a->dest);
                        /* caminho por a->dest ja foi explorado
                        reinserir o vertice na lista*/
                        vertices[a->dest].pai = -1;
                        l.push_back(a->dest);
                    }
                }
            }
            a = a->prox;//proxima resta
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

    //adiciona todos os vertices à lista, exceto a origem
    for(int i = 1; i < n_ver; i++){
        l.push_back(i);
    }

    //o caminho inicializa-se com custo 0, no vertice 0
    backtrack(vertices, l, 0, 0);

    imprimeCaminho(vertices);

    liberaGrafo(vertices, n_ver);
    return 0;
}
