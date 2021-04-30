//Esta tarefa é baseada no grafo https://github.com/alexzarp/Grafos/blob/main/resources/Capturar.PNG
#include <stdio.h>
#include <stdlib.h>

int retornoGlobal[3];

int leTabelaOrdenado (t *raiz, int i);
typedef struct {
	int val;
} Vertice;
//---------------------------------------
struct Tabela {
	int origem;
	int peso;
	int destino;
	struct Tabela *prox;
	struct Tabela *ant;
};
typedef struct Tabela t;

int leTabelaOrdenado (t *raiz, int i) {
	t *aux = raiz->prox;
	int control = 0;
	while (aux->prox) {
		if (control == i) {
			break;
		}
		control++;
		aux = aux->prox;
	}
	retornoGlobal[0] = aux->origem;
	retornoGlobal[1] = aux->peso;
	retornoGlobal[2] = aux->destino;
	return retornoGlobal;
}

void insereTabelaDeArestas (int tabelaDeArestas[3][11], t *raiz) {
	for (int i = 0; i < 11; i++) {
		int ret[3] = leTabelaOrdenado(raiz, i);
		tabelaDeArestas[0][i] = ret[0];
		tabelaDeArestas[1][i] = ret[1];
		tabelaDeArestas[2][i] = ret[2];
	}
}

void insereTabelaOrdenado (t *raiz, int origem, int peso, int destino) {
	t *novo = (t *) malloc (sizeof(t*));
	novo->origem = origem;
	novo->peso = peso;
	novo->destino = destino;
	novo->prox = NULL;
	//novo->ant = NULL;

	t *aux = raiz->prox;
	while (aux->prox) {
		if (aux->peso <= aux->prox->peso) 
			break;
	}
	novo->prox = aux->prox;
	aux->prox = novo;
}


//------------------------------------------
//lista duplamente encadeada com todos os vértices
struct tp_list_vet {
	Vertice *v;
	struct tp_list_vet *ant;
	struct tp_list_vet *prox;
};
typedef struct tp_list_vet ListaVertices;

typedef struct {
	int peso;
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

void liberaMemoriaLista (t *raiz) {
	t *aux = raiz;

	while (aux != NULL) {
		aux = raiz->prox;
		free(raiz);
		raiz = aux;
	}
	free(aux);
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

void imprimeAresta(Grafo *g, t *r, int tabelaDeArestas[3][11]){
	ListaArestas *aux = g->primeiroA;

	printf("****** Lista de ListaArestas ********\n\t{");
	while(aux != NULL){
		printf("(%d)----%d----(%d)", aux->e->origem->val, aux->e->peso, aux->e->destino->val);
		insereTabelaOrdenado(r, aux->e->origem->val, aux->e->peso, aux->e->destino->val);
		if (aux != g->ultimoA){
			printf(", ");
		}
		aux=aux->prox;
	}
	printf("}\n");
	insereTabelaDeArestas (tabelaDeArestas, r);
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
void insereAresta(Grafo *G, int origem, int destino, int peso){
	Aresta *newA;
	ListaArestas *auxA;
	Vertice *o, *d;
	
	//Aresta
	newA = malloc(sizeof(Aresta)); //Cria a Aresta
	newA->peso = peso;
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
		G->ultimoA->prox = auxA; //O proximo do ultimo ser o novo elemento
		auxA->ant = G->ultimoA; //anterior do novo elemento ser o ultimo
		G->ultimoA = auxA;  //o novo elemento vira o ultimo
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

void printEstadoKruskal (int tabela) {
	
}

// já não suporto mais :((, vou esfriar minha cabeça, isso não foi trivial dessa vez
void kruskal (int tabelaDeArestas[3][11], int tabelaDeLigacao[2][7]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 7; j++) {
			if (tabelaDeArestas[3][i] == )

		}
	}
	
}

int main() {
    int matAdja[7][7] = {/*(0) A*/{0, 7, 0, 5, 0, 0, 0},
            /*  ↑  ↑       (1) B*/{7, 0, 8, 9, 7, 0, 0},
            /*  L  C       (2) C*/{0, 8, 0, 0, 5, 0, 0},
                         /*(3) D*/{5, 9, 0, 0,15, 6, 0},
                         /*(4) E*/{0, 7, 5,15, 0, 8, 9},         //00  01  02  03
                         /*(5) F*/{0, 0, 0, 6, 8, 0,11},         //10  11  12  13
                         /*(6) G*/{0, 0, 0, 0, 9,11, 0}          //20  21  22  23
    };                                                           //30  31  32  33

	int tabelaDeArestas[3][11];// peso vi vj
	int tabelaDeLigacao[2][7];
	for (int i = 0; i < 7; i++){
		tabelaDeLigacao[0][i] = i;
		tabelaDeLigacao[1][i] = -1;
	}

    Grafo *grafo = inicializaGrafo();

	t *raiz = (t *) malloc(sizeof(t*));
	raiz->prox = NULL;
	
	for (int j = 0; j < 7; j++)
		insereVertice(grafo, j);

    for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (matAdja[i][j] != 0)
				insereAresta(grafo, i, j, matAdja[i][j]);

	imprimeListaVertices(grafo);
	imprimeAresta(grafo, raiz, tabelaDeArestas);//incluir certo

	liberaMemoria(grafo);
	liberaMemoriaLista (raiz);
    return 0;
}