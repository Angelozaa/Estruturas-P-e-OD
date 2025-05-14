#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int **adj;
	int n;
} Grafo;

typedef Grafo * p_grafo;

 p_grafo criar_grafo(int n);

void destroi_grafo(p_grafo g);
void insere_aresta(p_grafo g, int u, int v);
void remove_aresta(p_grafo g, int u, int v);
int tem_arestas(p_grafo, int u, int v);
int grau(p_grafo g, int u);
int mais_popular(p_grafo g);

void imprime_recomendacoes(p_grafo g, int u);
void imprime_aresta(p_grafo g);

int main(){
	
	p_grafo g = criar_grafo(6);
	
	insere_aresta(g, 0, 1);
	insere_aresta(g, 0, 4);
	insere_aresta(g, 1, 2);
	insere_aresta(g, 1, 4);
	insere_aresta(g, 2, 3);
	insere_aresta(g, 2, 5);
	insere_aresta(g, 3, 5);
	insere_aresta(g, 4, 5);
	insere_aresta(g, 0, 5);
	
	mais_popular(g);
	int n = mais_popular(g);
	printf("Grau do %d = %d ", n, grau(g,5));
	imprime_arestas(g);
	printf("\nMais Popular = %d ", n);
	
	return 0;
}

p_grafo criar_grafo(int n) {
	int i, j;
	p_grafo g = malloc(sizeof(Grafo));
	g->n = n;
	g->adj = malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		g->adj[i] = malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			g->adj[i][j] = 0;
	return g;
}

void destroi_grafo(p_grafo g) {
	int i;
	for (i = 0; i < g->n; i++)
	free(g->adj[i]);
	free(g->adj);
	free(g);
}

void insere_aresta(p_grafo g, int u, int v) {
	g->adj[u][v] = 1;
	g->adj[v][u] = 1;
}

void remove_aresta(p_grafo g, int u, int v) {
	g->adj[u][v] = 0;
	g->adj[v][u] = 0;
}

int tem_aresta(p_grafo g, int u, int v) {
	return g->adj[u][v];
}

p_grafo le_grafo() {
	int n, m, i, u, v;
	p_grafo g;
	scanf("%d %d", &n, &m);
	g = criar_grafo(n);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		insere_aresta(g, u, v);
	}
	return g;
}

void imprime_arestas(p_grafo g) {
	int u, v;
	for (u = 0; u < g->n; u++)
		for (v = u+1; v < g->n; v++)
			if (g->adj[u][v])
				printf("{%d,%d}\n", u, v);
}

int grau(p_grafo g, int u) {
	int v, grau = 0;
	for (v = 0; v < g->n; v++)
		if (g->adj[u][v])
		grau++;
	return grau;
}

int mais_popular(p_grafo g) {
	int u, max, grau_max , grau_atual;
	max = 0;
	grau_max = grau(g, 0);
	for (u = 1; u < g->n; u++) {
		grau_atual = grau(g, u);
		if (grau_atual > grau_max) {
			grau_max = grau_atual;
			max = u;
		}
	}
	return max;
}

void imprime_recomendacoes(p_grafo g, int u) {
	int v, w;
	for (v = 0; v < g->n; v++) {
		if (g->adj[u][v]) {
			for (w = 0; w < g->n; w++) {
				if (g->adj[v][w] && w != u && !g->adj[u][w])
				printf("%d\n", w);
			}
		}
	}
}


