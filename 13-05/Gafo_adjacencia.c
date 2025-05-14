#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	int v;
	struct No *prox;
} No;

typedef No * p_no;

typedef struct {
	p_no *adjacencia;
	int n;
} Grafo;

typedef Grafo * p_grafo;

p_grafo criar_grafo(int n);

void destroi_grafo(p_grafo g);

void insere_aresta(p_grafo g, int u, int v);

void remove_aresta(p_grafo g, int u, int v);

int tem_aresta(p_grafo g, int u, int v);

void imprime_arestas(p_grafo g);

int main(){
	p_grafo g = criar_grafo(7);
	
	insere_aresta(g, 0, 1);
	insere_aresta(g, 0, 2);
	insere_aresta(g, 0, 4);
	insere_aresta(g, 1, 2);
	insere_aresta(g, 1, 3);
	insere_aresta(g, 1, 4);
	insere_aresta(g, 1, 5);
	insere_aresta(g, 2, 4);
	insere_aresta(g, 3, 5);
	
	int a = 0;
	int b = 5;
	
	printf("Tem aresta entre %d e %d = %d\n", a, b, tem_aresta(g,a,b));
	
	imprime_arestas(g);
	
	return 0;
}

p_grafo criar_grafo(int n) {
	int i;
	p_grafo g = malloc(sizeof(Grafo));
	g->n = n;
	g->adjacencia = malloc(n * sizeof(p_no));
	for (i = 0; i < n; i++)
		g->adjacencia[i] = NULL;
	return g;
}

void libera_lista(p_no lista) {
	if (lista != NULL) {
		libera_lista(lista->prox);
		free(lista);
	}
}

void destroi_grafo(p_grafo g) {
	int i;
	for (i = 0; i < g->n; i++)
		libera_lista(g->adjacencia[i]);
	free(g->adjacencia);
	free(g);
}

p_no insere_na_lista(p_no lista, int v) {
	p_no novo = malloc(sizeof(No));
	novo->v = v;
	novo->prox = lista;
	return novo;
}

void insere_aresta(p_grafo g, int u, int v) {
	g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
	g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
}

p_no remove_da_lista(p_no lista, int v) {
	p_no proximo;
	if (lista == NULL)
		return NULL;
	else if (lista->v == v) {
		proximo = lista->prox;
		free(lista);
		return proximo;
	} else {
		lista->prox = remove_da_lista(lista->prox, v);
		return lista;
	}
}

void remove_aresta(p_grafo g, int u, int v) {
	g->adjacencia[u] = remove_da_lista(g->adjacencia[u], v);
	g->adjacencia[v] = remove_da_lista(g->adjacencia[v], u);
}

int tem_aresta(p_grafo g, int u, int v) {
	p_no t;
	for (t = g->adjacencia[u]; t != NULL; t = t->prox)
		if (t->v == v)
			return 1;
	return 0;
}
void imprime_arestas(p_grafo g) {
	int u;
	p_no t;
	for (u = 0; u < g->n; u++)
		for (t = g->adjacencia[u]; t != NULL; t = t->prox)
			printf(" {%d,%d}\n", u, t->v);
}

