#include <stdio.h>
#include <stdlib.h>

struct Lista {
    int peso;
    int vorigem;
    int vdestino;
    struct Controle *prox;
};
typedef struct Lista l;

void insereOrdenado (l *raiz, int peso, int vorigem, int vdestino) {
    l *novo = (l *) malloc(sizeof(l));
    novo->peso = peso;
    novo->vorigem = vorigem;
    novo->vdestino = vdestino;

    l *aux = raiz->prox;
    while (aux->prox) {
        l *control = aux->prox;
        if (novo->peso <= control->peso) {
            break;
        }
        aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
}

void printEstado (l *raiz) {
    l *p = raiz->prox;
    l *aux = raiz->prox;
    //printf("Estado da fila:\n|");
    printf("Peso→|");
    while (p != NULL) {
        printf("\t%d\t|", p->peso);
        p = p->prox;
    }
    p = aux;
    printf("\nVori→|");
    while (p != NULL) {
        printf("\t%d\t|", p->vorigem);
        p = p->prox;
    }
    p = aux;
    printf("\nVdes→|");
    while (p != NULL) {
        printf("\t%d\t|", p->vdestino);
        p = p->prox;
    }
}

void kruskal (int mat[7][7]/*, l *raiz*/) {
    int i = 0; //tanto faz a origem, começa do 0
    for (i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mat[i][j] != 0 && i < j) {
                
            }
        }
        printf("\n");
        // i++;
    }
}


int main () {
    int matAdja[7][7] = {/*(0) A*/{0, 7, 0, 5, 0, 0, 0},
            /*  ↑  ↑       (1) B*/{7, 0, 8, 9, 7, 0, 0},
            /*  L  C       (2) C*/{0, 8, 0, 0, 5, 0, 0},
                         /*(3) D*/{5, 9, 0, 0,15, 6, 0},
                         /*(4) E*/{0, 7, 5,15, 0, 8, 9},         //00  01  02  03
                         /*(5) F*/{0, 0, 0, 6, 8, 0,11},         //10  11  12  13
                         /*(6) G*/{0, 0, 0, 0, 9,11, 0}          //20  21  22  23
    };                                                           //30  31  32  33
    kruskal (matAdja);
}