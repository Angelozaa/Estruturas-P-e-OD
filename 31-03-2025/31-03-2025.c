#include <stdlib.h>
#include <stdio.h>

typedef struct no *p_no;
struct no{
	int chave;
	p_no esq, dir, pai;
};
p_no criar_arvore(); // ok
p_no novo_no(p_no raiz, int x); // ok
p_no procurar_no(p_no raiz, int x);
int numero_nos(p_no raiz);
int altura(p_no raiz);

void destruir_arvore(p_no raiz);
p_no inserir(p_no raiz, int chave); //ok
p_no remover(p_no raiz, int chave);
p_no buscar(p_no raiz, int chave); //ok
p_no minimo(p_no raiz); //ok
p_no maximo(p_no raiz); //ok
p_no sucessor(p_no x); //ok
p_no antecessor(p_no x); //ok
p_no ancestral_a_direita(p_no x);
p_no inserir_no(p_no pai, int chave);
void inordem(p_no raiz);

int main(){
	p_no raiz = criar_arvore();
	raiz = inserir(raiz, 8);
	raiz = inserir(raiz, 3);
	raiz = inserir(raiz, 13);
	raiz = inserir(raiz, 1);
	raiz = inserir(raiz, 7);
	raiz = inserir(raiz, 10);
	raiz = inserir(raiz, 14);
	raiz = inserir(raiz, 4);
	raiz = inserir(raiz, 12);
	raiz = inserir(raiz, 5);
	
	
	inordem(raiz);
	return 0;
}

p_no ancestral_a_direita(p_no x){
	if(x == NULL) return NULL;
	if(x->pai == NULL || x->pai->esq == x) return x->pai;
	else return ancestral_a_direita(x->pai);
}
p_no sucessor(p_no x){
	if(x->dir != NULL)
		return minimo(x->dir);
	else
		return ancestral_a_direita(x);	
}

p_no maximo(p_no raiz){
	if(raiz==NULL || raiz->dir == NULL) return raiz;
	return maximo(raiz->dir);
}

p_no minimo(p_no raiz){
	if(raiz==NULL || raiz->esq == NULL) return raiz;
	return minimo(raiz->esq);
}

p_no buscar(p_no raiz, int chave){
	if (raiz == NULL || chave == raiz->chave) return raiz;
	if (chave < raiz->chave) return buscar(raiz->esq, chave);
	else return buscar (raiz->dir, chave);	
}

void inordem(p_no raiz){
	if (raiz != NULL)
	{
		inordem(raiz->esq);
		printf("%d ", raiz->chave);
		inordem(raiz->dir);
	}
}

p_no novo_no(p_no raiz, int x) {
	
	p_no r = malloc(sizeof(struct no));
	r->chave = x;
	r->esq = NULL;
	r->dir = NULL;
	r->pai = raiz;
	return r;
}

p_no criar_arvore(){
	return NULL;
}

p_no inserir(p_no raiz, int chave){
	if (raiz == NULL)
		return novo_no(raiz, chave);
	if (chave < raiz->chave)
		raiz->esq = inserir_no(raiz, chave);
	else
		raiz->dir = inserir_no(raiz, chave);
	return raiz;
}

p_no inserir_no(p_no pai, int chave){
	if(pai->chave < chave){
		if(pai->esq == NULL) return novo_no(pai, chave);
		else inserir_no(pai->esq, chave);
	}else{
		if(pai->dir == NULL)return novo_no(pai, chave);
		else inserir_no(pai->dir, chave);	
	}
}


p_no remover(p_no raiz, int chave){ 
	if (raiz == NULL)
		return NULL;
	if (chave raiz->chave)
		raiz->esq = remover(raiz->esq, chave);
	else if (chave > raiz->chave)
		raiz->dir remover(raiz->dir, chave);
	else if (raiz->esq == NULL)
		return raiz->dir;
	else if (raiz->dir == NULL) 
		return raiz->esq;
	else
		remover_sucessor(raiz);
	return raiz;
}
