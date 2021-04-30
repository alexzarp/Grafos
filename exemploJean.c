#include <stdio.h>
#include <stdlib.h>

//Estrutura base do nó.
struct Node
{
    int valor;
    struct Node *proximo;
};

typedef struct Node node;

//Função pra printar o nó na tela.
void displayLL(node *p)
{
    p = p->proximo;
    printf("Mostrando a lista:\n");
    if(p)
    {
        do
        {            
            printf(" %d", p->valor);
            p = p->proximo;
        }
        while(p);
        printf("\n\n");

    }
    else
        printf("Lista vazia.\n\n");
}
 
// Função para inserir nó no inicio 
void insere_no_inicio(node *raiz, int info){
    node *novo = (node *) malloc(sizeof(node *));
    novo->valor = info;
    novo->proximo = raiz->proximo;
    raiz->proximo = novo;
}

// Função para inserir nó no final
void insere_no_final(node *raiz, int info){
    node *novo = NULL;
    novo = (node *)malloc(sizeof(node *));
    novo->valor = info;
    novo->proximo = NULL;

    node *ultimo = raiz->proximo;
    while (ultimo->proximo)
    {
        ultimo = ultimo->proximo;
    }

    ultimo->proximo = novo;
    novo->proximo = NULL;
}

// Função para inserir nó no meio
void insere_no_meio(node *raiz, int info, int posicao){
    node *novo = NULL;
    novo = (node *)malloc(sizeof(node *));
    novo->valor = info;
    
    node *p = raiz->proximo;

    int i = 0;
    while (p->proximo)
    {        
        i++;
        if (i == posicao)
            break;
        p = p->proximo;
        
    }    
    novo->proximo = p->proximo;
    p->proximo = novo;
    
}

// Função para remover nó no inicio
void remove_no_inicio(node *raiz){
    node *primeiro = raiz->proximo;
    raiz->proximo = primeiro->proximo;
    free(primeiro);
}
// Função para remover nó no final
void remove_no_final(node *raiz)
{
    node *p = raiz->proximo;
    node *anterior = raiz;
    
    while(p->proximo){
        anterior = p;
        p = p->proximo;
    }
    anterior->proximo = p->proximo;
    p->proximo = NULL;
    free(p);
}
// Função para remover nó no meio
void remove_no_meio(node *raiz, int posicao)
{
    node *p = raiz->proximo;
    node *anterior = raiz;
    int i = 0;
    while (p->proximo)
    {        
        anterior = p;
        p = p->proximo;
        i++;
        if (i == posicao)
            break;
    }
    anterior->proximo = p->proximo;
    p->proximo = NULL;
    free(p);
}

int main(void)
{
    printf("\n\n\n");
    node *raiz = NULL;    
    raiz = (node *)malloc(sizeof(node *));
    raiz->valor = NULL;
    raiz->proximo = NULL;
    
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_inicio(raiz, 1);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_inicio(raiz, 0);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_final(raiz, 2);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_final(raiz, 5);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_meio(raiz, 3, 3);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    insere_no_meio(raiz, 4, 4);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    remove_no_inicio(raiz);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    remove_no_inicio(raiz);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    remove_no_final(raiz);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
    
    remove_no_meio(raiz, 1);
    //Mostrando a lista.
    if (raiz)
        displayLL(raiz);
  
  free(raiz);
  
  return 0;
}