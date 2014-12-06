#include <stdio.h>
#include <stdlib.h>

int** buildMatrix(int **arestas, int ver);
void buildGraph(FILE *out, int **arestas, int ver, int are);

int main(int argc, char **argv) {

    FILE *out = fopen("in.txt", "w");
    int **arestas = NULL;
    int ver, are;

    printf("Entre com a quantidade de vertices e arestas\n");
    scanf("%d %d", &ver, &are);

    while(are > ver*(ver-1)){
        puts("Diminua o numero de arestas");
        scanf("%d", &are);
    }

    arestas = buildMatrix(arestas, ver);

    fprintf(out, "%d %d\n", ver, are);
    buildGraph(out, arestas, ver, are);
    fclose(out);
}

int** buildMatrix(int **arestas, int ver){

    arestas = (int **)calloc(ver, sizeof(int*));
    if(arestas){
        for(int i=0; i < ver; i ++){
            arestas[i] = (int*)calloc(ver, (sizeof(int)));
        }
    }
    return arestas;
}

void buildGraph(FILE *out, int **arestas, int ver, int are) {
    int aux1, aux2, aux3;

    for(int i=0; i<are; i++) {
        do {
            aux1 = rand() % ver;
            aux2 = rand() % ver;
        } while(aux1 == aux2 || arestas[aux1][aux2]);

        aux3 = (rand() % 10) + 5;

        arestas[aux1][aux2] = aux3;
        //arestas[aux2][aux1] = aux3;

        fprintf(out, "%d %d %d\n", aux1, aux2, aux3);
    }
}
