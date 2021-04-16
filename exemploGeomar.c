#include<stdio.h>
//#include<limits.h>

#define N 7 //quando alterear aqui, alterar também a matriz base.
#define INT_MAX 100 //máximo para os valors


int dfs(int adjMat[N][N], int origem, int destino){
	int i,j;

	int estrutura[N][3]; //0 - distancia, 1 - cor (0- branco, 1 - cinza, 2 - preto), 2 - antecessor

	estrutura[primeiroFila][1] = 2;

	//Passo 1, zerar as distâncias
		//sempre fazemos isso baseado na origem
	for (i=0; i<N; i++){
		estrutura[i][0] = 0;   //quem foi visitado, já esta colocando 1 pra a origem
		estrutura[i][1] = 0;
		estrutura[i][2] = -1;	//esta colocando como antecessor os nodos adjacentes a origem.
		
	}

	printf("Visitando %d", origem+1);
	imprimeMatriz(estrutura);
	estrutura[origem][1] = 1;
	//adicionaNaFila

	while(primeiro > ultimo){
		printf("Visitando %d\n", fila[inicio]); //visitando o primeiro da fila
		
		for (i=0; i<N; i++){
			if (adjMat[visitando][i] > 0){
				//adiciono os filhos na fila
				//cada filho é pintado de cinza
				//a distancia do filho é a soma da distancia do pai+1 -: estrura[i][0] = estrura[fila[primeiro]][0] + 1;
			}
		}
		imprimeMatriz(estrutura); //só pra imprimir a matriz bonitinha
		//imprimo a fila
		//visitar o proximo
		   //retiro o primeiro da fila
		visitando = primeiro_da_fila	// busca qual é o proximo nodo a ser visitado, lógica de pegar o menor. 

	}
	printf("terminamo!\n");
	

	return -1;
}




int main(){
	//estamos usando uma matriz fixa, mas vc pode alterar para usar uma matriz que tenha o malloc como a do guloso, vc dai vai ter que passar o tamanho das matrizes como parametro para as funções.
	int adjMat[N][N] = { {0,7,0,5,0,0,0}
						,{7,0,8,9,7,0,0}
						,{0,8,0,0,5,0,0}
						,{5,9,0,0,15,6,0}
						,{0,7,5,15,0,8,9}
						,{0,0,0,6,8,0,11}
						,{0,0,0,0,9,11,0}
						//,{0,0,0,8,8,9,0,0}
					};
	//dfs(adjMat, 0, 9);


	int fila[N]; //fila -> FIFO - first in, first out
	int inicio = 0;//primeiro elemento
	int fim = 0;//fim da fila
	int i;

	scanf("%d" , &i);
	while (i>=0){
		int remove;

		printf("Adicionando %d na fila!", i);
		fila[fim] = i;
		fim++;

		
		printf("\nFila! %d\n", fim);

		for (int j=inicio; j<fim; j++){
			printf("%d|", fila[j]);
		}

		printf("\n\n Remover elemento? (0 nao)");
		scanf("%d", &remove);

		if (remove){
			inicio++;
			printf("\nFila após remocao!\n");
			for (int j=inicio; j<fim; j++){
				printf("%d|", fila[j]);
			}
		}

		printf("\n Adicionar Elemento? (-1 nao)");
		scanf("%d" , &i);
	}




	return 0;
}