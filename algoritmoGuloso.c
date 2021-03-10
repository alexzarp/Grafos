#include <stdio.h>

int ligacao(int *mat[], int partiu, int chegou) {
    int valor, soma;
    for (int i=0; i<7; i++){
        //mat = mat[i][partiu];

        for (int j=0; j<7; j++){
            if (mat[i][j] != 0) {
                if (valor <= mat[i][j]){

                }
            }
        }
    }
}

//                                (0)(1)(2)(3)(4)(5)(6)
int main() {//                     1  2  3  4  5  6  7
    int matAdja[7][7] = {/*(0) 1*/{0, 2, 0, 6,12, 0, 0},
            /*  ↑  ↑       (1) 2*/{0, 0, 1, 0, 0, 5, 0},
            /*  L  C       (2) 3*/{0 ,0, 0, 0, 0, 0,40},
                         /*(3) 4*/{0, 0, 0, 0, 0, 4, 0},
                         /*(4) 5*/{0, 0, 0, 0, 0, 0,30},         //00  01  02  03
                         /*(5) 6*/{0, 0, 0, 0, 0, 0, 8},         //10  11  12  13
                         /*(6) 7*/{0, 0, 0, 0, 0, 0, 0}          //20  21  22  23
    };                                                           //30  31  32  33
    
    int partiu, chegou;
    printf("Partida,chegada: ");
    scanf("%d", &partiu, &chegou);

    if (ligacao(matAdja, partiu, chegou) == 1) 
        printf("Objetivo alcançado");
    else
        printf("Não o encontrei");
    

    return 0;
}