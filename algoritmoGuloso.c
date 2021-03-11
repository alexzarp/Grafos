#include <stdio.h>

int ligacao(int *mat[], int a, int b, int c, int d) {
    for(int i=a; i<7; i++){
        for(int j=b; j<7; j++){
          // ????   if((mat[i][j] <= mat[a][c]) && != 0)
            if((mat[i][j] <= mat[a][c]) != 0){
                a = i; c = j;
                if ((a == c) && (b == d)){
                    return 1;
                } else {
                    ligacao(mat, a,b,c,d);
                }
            }
        }
    }
    return 0;
}

int ligacao(int *mat[], int a, int b, int c, int d, int n_passos) {
    for(int i=a; i<7; i++){
        for(int j=b; j<7; j++){
          // ????   if((mat[i][j] <= mat[a][c]) && != 0)
            if((mat[i][j] <= mat[a][c]) != 0){
                a = i; c = j;
                if ((a == c) && (b == d)){
                    return 1;
                } else {
                    ligacao(mat, a,b,c,d);
                }
            }
        }
    }
    return 0;
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
    
    int a,b,c,d;
    //printf("Grafos disponíveis são: ");
    printf("[Part,ida][cheg,ada]: ");
    scanf("[%d,%d][%d,%d]",&a,&b,&c,&d);

    //pra não criar confusão na minha cabeça
    if (ligacao(&matAdja, a-1,b-1,c-1,d-1))
        printf("Objetivo alcançado");
    else
        printf("Não o encontrei");
    

    return 0;
}