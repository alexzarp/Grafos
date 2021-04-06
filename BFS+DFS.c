//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct Controle {
    int valor;
    struct Controle *prox;
};
typedef struct Controle controle;

void printControle (controle *raiz) {
    controle *p = raiz->prox;
    printf("Estado da fila:\n|");
    while (p != NULL) {
        printf(" %d |", p->valor);
        p = p->prox;    
    }
    printf("\n");
}

void insereFim(controle *raiz, int info){
    controle *novo = NULL;
    novo = (controle *)malloc(sizeof(controle *));
    novo->valor = info;
    novo->prox = NULL;

    controle *ultimo = raiz;
    while (ultimo->prox) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = novo;
}

void insereInicio (controle *raiz, int numero) {
    controle *novo = (controle*) malloc(sizeof(controle));
    novo->valor = numero;
    novo->prox = raiz->prox;
    raiz->prox = novo;
}

void removePrimeiro (controle *raiz) {
    controle *aux = raiz->prox;
    raiz->prox = aux->prox;
    free(aux);
}

int lePrimeiro (controle *raiz){
    controle *aux = raiz;
    aux = aux->prox;
    int value = aux->valor;
    return value;
}

// Vertice 0| Distancia 1| Anterior 2| Visitado(cor)3
void bfs (int mat[7][7], int tabelaBFS[7][4], controle *fila, int tamanho, int origem, int destino) {
    insereFim(fila, origem);
    int i = origem;
    tabelaBFS[i][1] = 0; //→ distancia 0
    int contagemPassos = 0;
    while (i < tamanho){
        tabelaBFS[i][3]++; //→ gray
        printf("\nVisitando vértice %d", i);
        for(int j = 0; j < tamanho; j++){
            if ((mat[i][j] != 0) && (tabelaBFS[j][3] < 1)){
                tabelaBFS[j][1] = 1;
                // for (int linha = i; linha < tamanho; linha++){
                //     for (int coluna = j; coluna < 4; coluna++) {
                //         if (tabelaBFS[linha][1] == INT_MAX) {
                //             tabelaBFS[linha][1] = 1;
                //         } else {
                //             if (tabelaBFS[linha][2] == origem) 
                //                 break;
                //             else {
                //                 tabelaBFS[linha][1]++;
                //                 linha = tabelaBFS[linha][2];
                //             } 
                //         }
                //     }
                // }
                tabelaBFS[j][2] = i;
                insereFim(fila, j);
                tabelaBFS[j][3]++;
            }
            else if (mat[i][j] != 0 && tabelaBFS[j][3] < 2) {
                tabelaBFS[j][1]++;
            }
        }
        tabelaBFS[i][3]++;
//--------------Print da tabela--------------------------------------------
        printf("\nEstado atual\n");
        printf("vert\t|dist\t|ant\t|visit\n");
        for (int linha = 0; linha < tamanho; linha++){
            for (int coluna = 0; coluna < 4; coluna++){
        // Vertice 0| Distancia 1| Anterior 2| Visitado(cor)3
        
                if (tabelaBFS[linha][coluna] == INT_MAX || tabelaBFS[linha][coluna] == INT_MIN)
                    printf("∞\t|");
                if ((tabelaBFS[linha][coluna] == 0) && (coluna == 3))
                    printf("bran\t|");
                if ((tabelaBFS[linha][coluna] == 1) && (coluna == 3))
                    printf("cinz\t|");
                if ((tabelaBFS[linha][coluna] > 1) && (coluna == 3))
                    printf("pret\t|");
                else
                    printf("%d\t|", tabelaBFS[linha][coluna]);
            }
            if ((linha == i) && (i > -1) && (i < tamanho))
                printf("← Visitando este vertice");
            printf("\n");
        }
//-------------------------------------------------------------------------
        printControle(fila);

        removePrimeiro(fila);
        
        if (destino == i){
            printf("Vertice encontrado, interrompendo navegação\n");
            return;
        }
        else if (fila->prox == NULL){
            printf("Não foi possível ligar-se ao vertice\n");
            return;
        }

        i = lePrimeiro(fila);
    }
    
}

//                                (0)(1)(2)(3)(4)(5)(6)
int main() {//                     A  B  C  D  E  F  G
    int matAdja[7][7] = {/*(0) A*/{0, 7, 0, 5, 0, 0, 0},
            /*  ↑  ↑       (1) B*/{7, 0, 8, 9, 7, 0, 0},
            /*  L  C       (2) C*/{0, 8, 0, 0, 5, 0, 0},
                         /*(3) D*/{5, 9, 0, 0,15, 6, 0},
                         /*(4) E*/{0, 7, 5,15, 0, 8, 9},         //00  01  02  03
                         /*(5) F*/{0, 0, 0, 6, 8, 0,11},         //10  11  12  13
                         /*(6) G*/{0, 0, 0, 0, 9,11, 0}          //20  21  22  23
    };                                                           //30  31  32  33
             // Vertice    Distância   Ligado com   Visitado
    int tabelaBFS[7][4] = {{0, INT_MAX, -1, 0},
                           {1, INT_MAX, -1, 0},
                           {2, INT_MAX, -1, 0},
                           {3, INT_MAX, -1, 0},
                           {4, INT_MAX, -1, 0},
                           {5, INT_MAX, -1, 0},
                           {6, INT_MAX, -1, 0},
    };                                   // ↑ 0 = white, 1 = gray, 2 = black
    //essa é minha pilha
    controle *raiz = (controle*) malloc(sizeof(controle));
    raiz->prox = NULL;
    //raiz->valor = NULL;
    int origem, destino;
    printf("Qual origem destino: ");
    scanf("%d%d", &origem, &destino);
    bfs(matAdja, tabelaBFS, raiz, 7, origem, destino);
    
    return 0;
}