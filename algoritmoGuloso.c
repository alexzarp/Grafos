#include <stdio.h>
/*
int exploraGrafo (int matrizAdj[][7], int origem, int destino, int numeroPassos, int maxPassos){
	//Verifica se o numero de passos é o máximo (numero de nodos)
	
	//anda nas colunas até achar a que tem o menor peso.	

	//verifica se o id da coluna com menor peso é igual ao id de destino
		//se for retorno 1 pois encontrou o caminho

	//Se a coluna não é o que buscavamos, faço a chamada recurciva
	//exploraGrafo ( matrizAdj[][7], id_coluna_menor_valor,  destino, numeroPassos++, maxPassos)


	return
*/
int ligacao(int mat[7][7], int origem, int destino, int maxPassos) {
    int i = origem, j=0;
    int numPassos, aux;
    for (j; j<7; j++){
        if(origem >= mat[i][j]){
            printf("Estou em {%d,%d}", i,j);
            origem = mat[i][j];
        }
    }
    origem = j;
    if (i == destino){
        return 1;
    } else {
        if (numPassos <= maxPassos)
            return 0;
        else if (maxPassos <= countpassos) 
            return -1;
    }
    
    ligacao(mat,origem,destino,numPassos++,maxPassos,linha);
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
    
    int partida,chegada;
    
    printf("Partida,chegada: ");
    scanf("%d,%d",&partida,&chegada);
    
    int busca = ligacao(matAdja, partida,chegada,7);
    
    if (busca > 0)
        printf("Objetivo alcançado\n");
    else if (busca == 0)
        printf("Cansei, impossível fazer com Guloso\n");
    else 
        printf("Alcance máximo atingido");
    

    return 0;
}