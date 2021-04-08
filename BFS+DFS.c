//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG
// Não tá funcionando e isso →não faz sentido←, dia 08/04/2021 irei no atendimento
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TAM 7

struct Controle {
    int valor;
    struct Controle *prox;
};
typedef struct Controle controle;

void printControle (controle *raiz) {
    controle *p = raiz->prox;
    //printf("Estado da fila:\n|");
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

void printTabelaBFS(int tabelaBFS[TAM][4], int tamanho, int i) {
    printf("\nEstado atual\n");
    printf("vert\t|dist\t|ant\t|visit\t|\n");
    for (int linha = 0; linha < tamanho; linha++){
        // Vertice 0| Distancia 1| Anterior 2| Visitado(cor)3
        if (tabelaBFS[linha][3] == 0)
            printf("%d\t|%d\t|%d\t|bran\t|", tabelaBFS[linha][0], tabelaBFS[linha][1], tabelaBFS[linha][2]);
        if (tabelaBFS[linha][3] == 1)
            printf("%d\t|%d\t|%d\t|cinz\t|", tabelaBFS[linha][0], tabelaBFS[linha][1], tabelaBFS[linha][2]);
        if (tabelaBFS[linha][3] > 1)
            printf("%d\t|%d\t|%d\t|pret\t|", tabelaBFS[linha][0], tabelaBFS[linha][1], tabelaBFS[linha][2]);

        // if (coluna == 0)
        //     printf("%d\t|", tabelaBFS[linha][coluna]);
        // if (coluna == 1 && (tabelaBFS[linha][coluna] == INT_MAX || tabelaBFS[linha][coluna] == INT_MIN))
        //     printf("∞\t|");
        // if (coluna == 2)
        //     printf("%d\t|", tabelaBFS[linha][coluna]);
        // if (coluna == 3){
        //     if (tabelaBFS[linha][coluna] == 0)
        //         printf("bran\t|");
        //     else if (tabelaBFS[linha][coluna] == 1)
        //         printf("cinz\t|");
        //     else if (tabelaBFS[linha][coluna] > 1)
        //         printf("pret\t|");
        // }
        
        if ((linha == i) && (i > -1) && (i < tamanho))
            printf("← Visitando este vertice");
        printf("\n");
    }   
}

void printTabelaDFS(int tabelaDFS[TAM][5], int tamanho, int i) {//1
    printf("\nEstado atual\n");
    printf("vert\t|achad\t|prof\t|ante\t|visi\t|\n");
    for (int linha = 0; linha < tamanho; linha++){//2
        // Vertice  Momento_encotro  Momento_busca_completa  Anterior  Visitado
        for (int coluna = 0; coluna < 5; coluna++){//3
            if (coluna == 0)
                printf("%d\t|", tabelaDFS[linha][coluna]);
            if (coluna == 1)
                printf("%d\t|", tabelaDFS[linha][coluna]);
            if (coluna == 2)
                printf("%d\t|", tabelaDFS[linha][coluna]);
            if (coluna == 3)
                printf("%d\t|", tabelaDFS[linha][coluna]);
            if (coluna == 4){//4
                if (tabelaDFS[linha][coluna] == 0)
                    printf("bran\t|");
                else if (tabelaDFS[linha][coluna] == 1)
                    printf("cinz\t|");
                else if (tabelaDFS[linha][coluna] > 1)
                    printf("pret\t|");
            }//4
        }//3
        if ((linha == i) && (i > -1) && (i < tamanho))
            printf("← Visitando este vertice");
        printf("\n");
    }//2
}//1

// Vertice 0| Distancia 1| Anterior 2| Visitado(cor)3
void bfs (int mat[TAM][TAM], int tabelaBFS[TAM][4], controle *fila, int tamanho, int origem, int destino) {
    insereFim(fila, origem);
    int i = origem;
    tabelaBFS[i][1] = 0; //→ distancia 0
    while (i < tamanho){
        tabelaBFS[i][3]++; //→ gray
        printf("\nVisitando vértice %d", i);
        for(int j = 0; j < tamanho; j++){
            if ((mat[i][j] != 0) && (tabelaBFS[j][3] < 1)){
                tabelaBFS[j][1] = 1;
                tabelaBFS[j][2] = i;
                insereFim(fila, j);
                tabelaBFS[j][3]++;
            }
            else if (mat[i][j] != 0 && tabelaBFS[j][3] < 2) {
                tabelaBFS[j][1]++;
            }
        }
        tabelaBFS[i][3]++;

        printTabelaBFS (tabelaBFS, tamanho, i);

        printf("Estado da fila:\n|");
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

void dfs (int mat[TAM][TAM], int tabelaDFS[TAM][5], controle *pilha, int tamanho, int origem, int destino) {
    insereInicio(pilha, origem);
    int i = origem;
    int passos = 0;
    tabelaDFS[i][1] = passos;//→ encontro no momento 1
    while (i < tamanho){
        tabelaDFS[i][4]++; //→ gray
        printf("\nVisitando vértice %d", i);
        // Vertice0  Encontrado1  Prundidade2  Anterior3  Visitado4
        for(int j = 0; j < tamanho; j++){
            if ((mat[i][j] != 0) && (tabelaDFS[j][4] < 1)){
                passos++;
                tabelaDFS[j][1] = passos;
                tabelaDFS[j][3] = i;
                tabelaDFS[j][4]++;
                insereInicio(pilha, j);
            }
            else if (mat[i][j] != 0 && tabelaDFS[j][3] < 2) {
                tabelaDFS[j][2]++;
            }
        }
        tabelaDFS[i][4]++;
        printTabelaDFS (tabelaDFS, tamanho, i);

        printf("Estado da pilha:\n|");
        printControle(pilha);

        removePrimeiro(pilha);
        
        if (destino == i){
            printf("Vertice encontrado, interrompendo navegação\n");
            return;
        }
        else if (pilha->prox == NULL){
            printf("Não foi possível ligar-se ao vertice\n");
            return;
        }

        i = lePrimeiro(pilha);
    }
}

//                                    (0)(1)(2)(3)(4)(5)(6)
int main() {//                         A  B  C  D  E  F  G
    int matAdja[TAM][TAM] = {/*(0) A*/{0, 7, 0, 5, 0, 0, 0},
            /*   ↑    ↑        (1) B*/{7, 0, 8, 9, 7, 0, 0},
            /*   L    C        (2) C*/{0, 8, 0, 0, 5, 0, 0},
                             /*(3) D*/{5, 9, 0, 0,15, 6, 0},
                             /*(4) E*/{0, 7, 5,15, 0, 8, 9},         //00  01  02  03
                             /*(5) F*/{0, 0, 0, 6, 8, 0,11},         //10  11  12  13
                             /*(6) G*/{0, 0, 0, 0, 9,11, 0}          //20  21  22  23
    };                                                               //30  31  32  33
             // Vertice    Distância   Anterior   Visitado
    int tabelaBFS[TAM][4] = {{0, 0, -1, 0},
                             {1, 0, -1, 0},
                             {2, 0, -1, 0},
                             {3, 0, -1, 0},
                             {4, 0, -1, 0},
                             {5, 0, -1, 0},
                             {6, 0, -1, 0},
    };                                     // ↑ 0 = white, 1 = gray, 2 = black

    // Vertice  Momento_encotro  Momento_busca_completa  Anterior  Visitado
    int tabelaDFS[TAM][5] = {{0, 0, 0, -1, 0},
                             {1, 0, 0, -1, 0},
                             {2, 0, 0, -1, 0},
                             {3, 0, 0, -1, 0},
                             {4, 0, 0, -1, 0},
                             {5, 0, 0, -1, 0},
                             {6, 0, 0, -1, 0},
    };                                  // ↑ 0 = white, 1 = gray, 2 = black

    //essa é minha pilha ou fila
    controle *raiz = (controle*) malloc(sizeof(controle));
    raiz->prox = NULL;

    int origem, destino;
    printf("Origem destino: ");
    scanf("%d%d", &origem, &destino);
    int expression;
    printf("\nEscolha DFS - 1 ou BFS - 2: ");
    scanf("%d", &expression);
    switch (expression) {
    case 1:
        dfs(matAdja, tabelaDFS, raiz, TAM, origem, destino);
        break;
    
    default:
        bfs(matAdja, tabelaBFS, raiz, TAM, origem, destino);
        break;
    }

    return 0;
}
