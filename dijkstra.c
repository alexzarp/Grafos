//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG
#include <stdio.h>
#include <limits.h>
//                     vertice | visitado | distacia | anterior
void dijkstra (int mat[7][7], int tabela[7][4], int nodoInicial) {
    int i = nodoInicial;
    tabela[i][2] = 0; //→ o primeiro nodo tem custo zero pois é o início
    //↓ 7 é o número fixo de nodos, isso está correto ou deveria estar dinâmico?
    while (i < 7) {
        tabela[i][1] = 1; // visitado = 1/true
        
        printf("\nVisitando nodo %d", i);
        for (int j = 0; j < 7; j++){
            if ((mat[i][j] != 0) && (tabela[j][1] != 1) && ((tabela[j][2]) > (mat[i][j] + tabela[i][2]))){
                tabela[j][2] = mat[i][j] + tabela[i][2];
                tabela[j][3] = i;
            }
        }
//------------Print da tabela-----------------------
        printf("\nEstado atual\n");
        printf("vert\t|vis\t|cust\t|ant\n");
        for(int p = 0; p < 7; p++){
            for(int q = 0; q < 4; q++){
                if (tabela[p][q] == INT_MAX)
                    printf("∞\t|");
                else
                    printf("%d\t|", tabela[p][q]);
            }
            if ((p == i) && (i > -1) && (i < 7)) 
                printf("← Visitando este nodo");
            printf("\n");        
        }
//---------------------------------------------------
// vertice | visitado | custo | anterior
        int menorCusto = INT_MAX, local;
        for (int w = 0; w < 7; w++)
            if ((tabela[w][1] < 1) && (tabela[w][2] < menorCusto)){
                menorCusto = tabela[w][2];
                local = w;
            }
        if (menorCusto == INT_MAX)
            local = -1;

        if(local == -1 || local > 7)
            return;           
        
        i = local;
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
    int tabela[7][4] = {{0, 0, INT_MAX, -1},
                        {1, 0, INT_MAX, -1},
                        {2, 0, INT_MAX, -1},
                        {3, 0, INT_MAX, -1},
                        {4, 0, INT_MAX, -1},
                        {5, 0, INT_MAX, -1},
                        {6, 0, INT_MAX, -1}
    };

    int inicio;
    printf("Em qual nodo começa? ");
    scanf("%d", &inicio);
    dijkstra(matAdja, tabela, inicio);
}