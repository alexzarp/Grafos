#include <stdio.h>
#include <limits.h>
// Grafo: https://github.com/alexzarp/Grafos/blob/main/resources/new.png
void printTabelaPrim(int tabelaPrim[8][4], int i) {
    //vert0 | visitado1 | custo2 | anterior3
    printf("\nEstado atual\n");
    printf("vert\t|visi\t|cust\t|ante\t|\n");
    for (int linha = 0; linha < 8; linha++){
        if (tabelaPrim[linha][1] == 0)
            printf("%d\t|Falso\t|%d\t|%d\t|", tabelaPrim[linha][0], tabelaPrim[linha][2], tabelaPrim[linha][3]);
        if (tabelaPrim[linha][1] == 1)
            printf("%d\t|Verda\t|%d\t|%d\t|", tabelaPrim[linha][0], tabelaPrim[linha][2], tabelaPrim[linha][3]);
                
        if ((linha == i) && (i > -1) && (i < 8))
            printf("← Visitando este vertice");
        printf("\n");
    }   
}

void printGeradoraMin (int tabelaPrim[8][4]) {
    printf("\nÁrvore geradora mínima\n");
    int soma = 0;
    for (int i = 0; i < 8; i++){
        printf("(%d → %d), ", tabelaPrim[i][0], tabelaPrim[i][3]);
        soma += tabelaPrim[i][3];
    }
    printf("\nSoma: %d\n", soma);
}

void prim (int mat[8][8], int tabelaPrim[8][4], int origem) {
    int i = origem;
    //vert0 | visitado1 | custo2 | anterior3
    tabelaPrim[i][2] = 0;
    while (i < 8){ 
        int menorCusto = 0;
        printf("\nVisitando vértice %d", i);
        tabelaPrim[i][1] = 1;
        for (int j = 0; j < 8; j++) 
            if (mat[i][j] != 0 && tabelaPrim[j][2] == -1 && tabelaPrim[j][1] != 0) {
                tabelaPrim[j][2] = mat[i][j];
                tabelaPrim[j][3] = i;
            }

        for (int j = 0; j < 8; j++) {
            // if (tabelaPrim[j][2] < menorCusto && tabelaPrim[j][1] != 1 && tabelaPrim[j][2] != -1) {
                menorCusto = tabelaPrim[j][2];
                i = tabelaPrim[j][0];
            }
        }

        printTabelaPrim(tabelaPrim, i);

        for (int j = 0; j < 8; j++) {
            int count = 0;
            if (tabelaPrim[j][1] != 0)
                count++;
            if (tabelaPrim[j][1] == 0){
                j = 8;
            }
            if (count >= 7) {//
                i = 8;
            }
        }
    }
    printGeradoraMin(tabelaPrim);
}

//                                (0)(1)(2)(3)(4)(5)(6)(7)
int main() {//                     A  B  C  D  E  F  G  H
    int matAdja[8][8] = {/*(0) A*/{0, 2, 0, 6, 5, 0, 0, 0},
            /*  ↑  ↑       (1) B*/{2, 0, 7, 7, 0, 0, 0, 0},
            /*  L  C       (2) C*/{0, 7, 0, 0, 6, 2, 0, 0},
                         /*(3) D*/{6, 7, 0, 0, 0, 0, 0, 0},
                         /*(4) E*/{5, 0, 6, 0, 0, 0, 4, 5},
                         /*(5) F*/{0, 0, 2, 0, 0, 0, 4, 6},
                         /*(6) G*/{0, 0, 0, 0, 4, 4, 0, 1},
                         /*(7) H*/{0, 0, 0, 0, 5, 6, 1, 0}
    };
    //vert | visitado | custo | anterior
    int tabelaPrim[8][4];
    for (int i = 0; i < 8; i++){
        tabelaPrim[i][0] = i;
        tabelaPrim[i][1] = 0;
        tabelaPrim[i][2] = -1;
        tabelaPrim[i][3] = -1;
    }
    printf("Origem: ");
    int origem;
    scanf("%d", &origem);
    printf("\n");

    prim (matAdja, tabelaPrim, origem);

    return 0;
}