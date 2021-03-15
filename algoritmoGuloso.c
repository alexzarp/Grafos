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
// Faltou muita coisa, e não consegui fazer funcionar nem a parte lógica principal.

// int ligacao(int mat[7][7], int origem, int destino, int maxPassos) {
//     int i = origem, j=0;
//     int numPassos, aux;
//     for (j; j<7; j++){
//         if(origem >= mat[i][j]){
//             printf("Estou em {%d,%d}", i,j);
//             origem = mat[i][j];
//         }
//     }
//     origem = j;
//     if (i == destino){
//         return 1;
//     } else {
//         if (numPassos <= maxPassos)
//             return 0;
//         else if (maxPassos <= countpassos) 
//             return -1;
//     }
    
//     ligacao(mat,origem,destino,maxPassos);
// }

int gordo (int mat[][7], int origem, int destino, int numPassos, int numMax){
	int melhorEscolha = -1; 
	int j;// → Coluna 
	
	if (numMax < numPassos)
		return 0;

	for (j = 0; j < numMax; j++) 
		if (mat[origem][j] > 0 && j != origem)
            if (melhorEscolha == -1 || mat[origem][melhorEscolha] > mat[origem][j]) 
                melhorEscolha = j;

    if (destino == melhorEscolha)
        return 1;
    
    if (melhorEscolha > -1)
        return gordo(mat, melhorEscolha, destino, numPassos++, numMax);

    return -1;
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
    
    int busca = gordo(matAdja, partida-1,chegada-1,4, 7);
    
    if (busca == 0)
        printf("\nCansei, impossível fazer com Guloso\n");
    else if (busca == 1)
        printf("\nEncontrei\n");
    else 
        printf("\nCansei, impossível fazer com Guloso!\n");
    

    return 0;
}