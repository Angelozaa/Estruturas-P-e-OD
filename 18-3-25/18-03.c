#include <stdio.h>
#include <stdlib.h>

typedef struct no {
 int valor;
 struct No *esq;
 struct No *dir;
} No;

No* cria_arvore();
No* procurar(No* raiz, int valor);
int numero_nos(No* raiz);
int altura(No* raiz);
void inserir_no(No *raiz, int valor);

int main(){
	No *raiz = cria_arvore();
	printf("Numero de Nos %i", numero_nos(raiz));
	return 1;
}


void inserir_no(No *raiz, int valor){
	if(raiz == NULL){
		No *novo = (No*) malloc(sizeof(No));
		novo->valor = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		raiz = novo;
			
	}else{
		if(valor < raiz->valor){
			inserir_no(raiz->esq, valor);
		}else{
			inserir_no(raiz->dir, valor);
		}
	}
}

No* cria_arvore(){
	return NULL;
}


int altura(No* raiz){
	if(raiz == NULL) return 0;
	int h_esq, h_dir;
	h_esq = altura(raiz->esq);
	h_dir = altura(raiz->dir);	
	return 1+ (h_esq > h_dir ? h_esq : h_dir);
}

int numero_nos(No* raiz){
	if(raiz == NULL) return 0;
	return numero_nos(raiz->esq) + numero_nos(raiz->dir) + 1;
}
