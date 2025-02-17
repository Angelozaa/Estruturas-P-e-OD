#include <stdio.h>
#include <stdlib.h>

struct Elemento
{
	int num;
	struct Elemento *prox;
};

typedef struct Elemento Elemento;
struct Pilha
{
	struct Elemento *topo;
};

typedef struct Pilha Pilha;

//cabeçalho com todas as funções do programa
//logica das funções sempre feitas abaixo do main
//isso é uma boa pratica :)
Pilha* criar_pilha();
void inserir_elemento(Pilha *pi);
void listar_pilha(Pilha *pi);
void remover_elemento(Pilha *pi);
void esvaziar_pilha(Pilha *pi);
Elemento *aux;
int main()//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
{
	Pilha *pi = criar_pilha();
	inserir_elemento(pi);
	inserir_elemento(pi);
	listar_pilha(pi);
	return 0;
}

Pilha* criar_pilha()
{
	Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
	if( pi != NULL)
	{
		pi->topo = NULL;
	}
	return pi;
}

void inserir_elemento(Pilha *pi)
{
	Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
	printf("Digite um numero: ");
	scanf("%i", &novo->num);
	novo->prox = pi->topo;
	pi->topo = novo;
	printf("\nInserido na Pilha!\n\n");
}

void listar_pilha(Pilha *pi){
	if(pi->topo == NULL)
	{
		printf("Pilha esta vazia! \n");
	}else
	{
		aux= pi->topo;
		printf("\nListando elementos:\n\n");
		do
		{
			printf("%i ", aux->num);
			aux = aux->prox;
		}while(aux != NULL);
	}
}