//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int val;
} Vertice;

typedef struct Tabela{
	int pesoAresta;
	int verticei;
	int verticej;

	struct Tabela *prox;
	//struct Tabela *ant;
}tabela;

//lista duplamente encadeada com todos os vértices
struct tp_list_vet {
	Vertice *v;
	struct tp_list_vet *ant;
	struct tp_list_vet *prox;
};
typedef struct tp_list_vet ListaVertices;

typedef struct {
	Vertice *origem;
	Vertice *destino;
} Aresta;

//lista encadeada de ListaListaArestas
struct tp_list_edges {
	Aresta *e;
	struct tp_list_edges *prox; //8 bytes de memoria
	struct tp_list_edges *ant;
};
typedef struct tp_list_edges ListaArestas;

//armazenar o começo das listas.
typedef struct {
	ListaVertices *primeiroV;
	ListaVertices *ultimoV;

	ListaArestas *primeiroA;
	ListaArestas *ultimoA;
} Grafo;


Grafo *inicializaGrafo(){
	Grafo *G = malloc(sizeof(Grafo));
	
	G->primeiroV = NULL;
	G->ultimoV = NULL;

	G->primeiroA = NULL;
	G->ultimoA = NULL;

	return G;
}

void liberaMemoria(Grafo *G){
	ListaVertices *auxV = G->primeiroV;
	ListaArestas *auxA = G->primeiroA;
	
	while(auxV != NULL){
		auxV = G->primeiroV->prox;
		free(G->primeiroV);
		G->primeiroV = auxV;
	}

	while(auxA != NULL){
		auxA=G->primeiroA->prox;
		free(G->primeiroA);
		G->primeiroA = auxA;
	}


	free(G);

	printf("\nMemoria liberada\n");
}

void imprimeListaVertices(Grafo *g){
	ListaVertices *aux = g->primeiroV;

	printf("****** Lista de Vértices ********\n\t{");
	while(aux != NULL){
		printf("%d", aux->v->val);
		if (aux != g->ultimoV){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

void imprimeAresta(Grafo *g){
	ListaArestas *aux = g->primeiroA;

	printf("****** Lista de ListaArestas ********\n\t{");
	while(aux != NULL){
		printf("(%d,%d)", aux->e->origem->val, aux->e->destino->val);
		if (aux != g->ultimoA){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
}

Vertice *getVertice(Grafo *g, int valor){
	ListaVertices *aux = g->primeiroV;

	while(aux != NULL){  //complexidade O(n)
		if (aux->v->val == valor){
			return aux->v;
		}
		aux=aux->prox;
	}

	return NULL;
} 

void insereVertice(Grafo *G, int val){
	Vertice *newV;
	ListaVertices *auxV;

	//vertice
	newV = malloc(sizeof(Vertice)); //cria vértice
	newV->val = val;

	//Elemento da lista
	auxV = malloc(sizeof(ListaVertices)); //Elemento para por na lista.
	auxV->ant = NULL;
	auxV->prox = NULL;
	auxV->v = newV;

	//Encadeamento na lista do auxV
	if (G->primeiroV == NULL){ //lista Vazia
		G->primeiroV = auxV;
		G->ultimoV = auxV; 
	} else { //faz o encadeamento
		G->ultimoV->prox = auxV; //O proximo do ultimo ser o novo elemento
		auxV->ant = G->ultimoV; //anterior do novo elemento ser o ultimo
		G->ultimoV = auxV;  //o novo elemento vira o ultimo
	}
}
/**
 * Nesta função havia um erro, não haviamos criado a aresta com dois vértices, e sim com dois int. Foi corrigido e há uma observação.
 */
void insereAresta(Grafo *G, int origem, int destino){
	Aresta *newA;
	ListaArestas *auxA;
	Vertice *o, *d;
	
	//Aresta
	newA = malloc(sizeof(Aresta)); //Cria a Aresta
	/**
	 * Perceba que aqui estamos criando um novo vértice para representar a origem, 
	 * 	poderiamos buscar um vértice já existente em nossa lista, e caso não encontrar apresentar um erro. 
	 * Nesta tarefa isso não faz diferença. A função getVertice busca um vertice, caso deseje utilizar.
	 * ex -> 
	 * 		o = getVertice(G ,origem);
	 *		newA->origem = o;
	 */
	o = malloc(sizeof(Vertice));
	o->val = origem;
	newA->origem = o;

	d = malloc(sizeof(Vertice));
	d->val = destino;
	newA->destino = d;
	//fim da aresta.


	//Elemento da lista de Arestas
	auxA = malloc(sizeof(ListaArestas));
	auxA->ant = NULL;
	auxA->prox = NULL;
	auxA->e = newA;

	//encadeamento na lista de Arestas.
	if (G->primeiroA == NULL){ //lista Vazia
		G->primeiroA = auxA;
		G->ultimoA = auxA; 
	} else { //faz o encadeamento
		//printf("Não é o primeiro\n");
		G->ultimoA->prox = auxA; //O proximo do ultimo ser o novo elemento
		auxA->ant = G->ultimoA; //anterior do novo elemento ser o ultimo
		G->ultimoA = auxA;  //o novo elemento vira o ultimo
		//printf("Feito\n");
	}
}

//função vai imprimir todas as ListaArestas que o vertice X aparece como origem
//   Ex: X = 2, imprime todas as ListaArestas em que X aparece como origem.
void imprimeListaArestasOrigem( Grafo *g, int valor){
	ListaArestas *aux = g->primeiroA; //primeira aresta

	while(aux != NULL){
			//(vertice(aresta))	
		if (((aux->e)->origem)->val == valor) //pegando a origem de uma aresta
			printf("\tA(%d, %d)\n", aux->e->origem->val, aux->e->destino->val);

		aux = aux->prox;
	}

}

void imprimeListaArestasDestino( Grafo *g, int valor){
	ListaArestas *aux = g->primeiroA; //primeira aresta

	while(aux != NULL){
			//(vertice(aresta))	
		if (((aux->e)->destino)->val == valor) //pegando a origem de uma aresta
			printf("\tA(%d, %d)\n", aux->e->origem->val, aux->e->destino->val);

		aux = aux->prox;
	}

}

// void kruskal (int mat[7][7]) {

// }

int main() {
    int matAdja[7][7] = {/*(0) A*/{0, 7, 0, 5, 0, 0, 0},
            /*  ↑  ↑       (1) B*/{7, 0, 8, 9, 7, 0, 0},
            /*  L  C       (2) C*/{0, 8, 0, 0, 5, 0, 0},
                         /*(3) D*/{5, 9, 0, 0,15, 6, 0},
                         /*(4) E*/{0, 7, 5,15, 0, 8, 9},         //00  01  02  03
                         /*(5) F*/{0, 0, 0, 6, 8, 0,11},         //10  11  12  13
                         /*(6) G*/{0, 0, 0, 0, 9,11, 0}          //20  21  22  23
    };                                                           //30  31  32  33

    Grafo *grafo = inicializaGrafo();

	
	for (int j = 0; j < 7; j++)
		insereVertice(grafo, j);

    for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (matAdja[i][j] != 0)
				insereAresta(grafo, i, j);

	imprimeListaVertices(grafo);
	imprimeAresta(grafo);

	liberaMemoria(grafo);
    return 0;
}