#include <stdio.h>
//1🔴 2⚫ 3🔵 4🟡
//Modo sai colorindo com a cor que der
//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG

void coloreGrafo (int mat[7][7], int tabela[7][2]) {
    //vertice0 | cor1 |

    for (int i = 0; i < 7; i++){
        tabela[i][1] = 1;
        for (int j = 0; j < 7; j++){
            if (mat[i][j] != 0) {
                if (tabela[j][1] == tabela[i][1]){
                    tabela[i][1]++;
                    j = 0;
                }
            }
        }
    }
}

void printTabela (int tabela[7][2]) {
    int num[4] = {0,0,0,0};
    int contagem = 0;
    printf("Reultado:\n");
    printf("vert\t|\tcor\n");
    for (int i = 0; i < 7; i++){
        if (tabela[i][1] == 1){
            printf("%d\t|\t🔴", tabela[i][0]);
            if (num[0] == 0){
                contagem++;
                num[0] = 1;
            }
        }

        if (tabela[i][1] == 2) {
            printf("%d\t|\t⚫", tabela[i][0]);
            if (num[1] == 0){
                contagem++;
                num[1] = 1;
            }
        }

        if (tabela[i][1] == 3) {
            printf("%d\t|\t🔵", tabela[i][0]);
            if (num[2] == 0){
                contagem++;
                num[2] = 1;
            }
        }

        if (tabela[i][1] == 4) {
            printf("%d\t|\t🟡", tabela[i][0]);
            if (num[3] == 0){
                contagem++;
                num[3] = 1;
            }
        }

        printf("\n");
    }
    printf("\nNúmero de cores usadas: %d\n", contagem);
}

// void medeGrau (int mat[7][7], int tabela[7][3]){
//     int grau;
//     for (int i = 0; i < 7; i++){
//         grau = 0;
//         for (int j = 0; j < 7; j++){
//             if (mat[i][j] != 0){
//                 grau++;
//                 // printf("Grau %d", grau);
//             }
//         }
//         tabela[i][2] = grau;
//     }
// }

//buble sort kibado diretamente dos trabalhos de POD
// int bubblesort(int vet[7][3], int n){
//     int flag=0;
//     for(int i = n-1; i>=1; i--){
//         flag=0;
//         for(int j = 0; j<=i-1; j++){
//             if(vet[j][2]>vet[j+1][2]){
//                 int troca = vet[j][2];
//                 int troca1 = vet[j][1];
//                 int troca2 = vet[j][0];

//                 vet[j][2] = vet[j+1][2];
//                 vet[j][1] = vet[j+1][1];
//                 vet[j][0] = vet[j+1][0];
                
//                 vet[j+1][2] = troca;
//                 vet[j+1][1] = troca1;
//                 vet[j+1][0] = troca2;
//                 flag = 1;
//             }
//         }
//         if(flag == 0){
//             break;
//         }
//     }
// }

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

    //vertice | cor |
    int tabelaColoracao[7][2] = {
        {0,0},
        {1,0},
        {2,0},
        {3,0},
        {4,0},
        {5,0},
        {6,0}
    };

    //medeGrau(matAdja, tabelaColoracao);
    //bubblesort(tabelaColoracao, 7);
    coloreGrafo(matAdja, tabelaColoracao);
    printTabela(tabelaColoracao);

    // for (int i = 0; i< 7; i++){
    //     printf("Grau de %d = %d\n", tabelaColoracao[i][0], tabelaColoracao[i][1]);
    // }
}