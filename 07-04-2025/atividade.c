#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define FILAS_MENORES 9
#define TAMANHO_FILA 10
#define TAMANHO_FILA_GRANDE 50
#define TEMPO_TOTAL_SEGUNDOS 60

typedef struct {
    int *dados;
    int tamanho;
    int inicio;
    int fim;
    int quantidade;
    int processados; // quantidade de vezes que essa thread retirou da fila grande
    pthread_mutex_t mutex;
} Fila;

Fila filaGrande;
Fila filasMenores[FILAS_MENORES];

int tempo_ativo = 1;

// -------- Funções da Fila --------
void inicializarFila(Fila *fila, int tamanho) {
    int i;
    fila->dados = (int *)malloc(sizeof(int) * tamanho);
    for (i = 0; i < tamanho; i++) {
        fila->dados[i] = 0;
    }
    fila->tamanho = tamanho;
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
    fila->processados = 0;
    pthread_mutex_init(&fila->mutex, NULL);
}

int temEspaco(Fila *fila) {
    return fila->quantidade < fila->tamanho;
}

int estaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int inserir(Fila *fila, int valor) {
    pthread_mutex_lock(&fila->mutex);
    if (temEspaco(fila)) {
        fila->dados[fila->fim] = valor;
        fila->fim = (fila->fim + 1) % fila->tamanho;
        fila->quantidade++;
        pthread_mutex_unlock(&fila->mutex);
        return 1;
    }
    pthread_mutex_unlock(&fila->mutex);
    return 0;
}

int remover(Fila *fila, int *valor) {
    pthread_mutex_lock(&fila->mutex);
    if (!estaVazia(fila)) {
        *valor = fila->dados[fila->inicio];
        fila->dados[fila->inicio] = 0;
        fila->inicio = (fila->inicio + 1) % fila->tamanho;
        fila->quantidade--;
        pthread_mutex_unlock(&fila->mutex);
        return 1;
    }
    pthread_mutex_unlock(&fila->mutex);
    return 0;
}

// -------- Thread: Geração de números --------
void *gerarNumeros(void *arg) {
    while (tempo_ativo) {
        int valor = (rand() % 10) + 1;
        if (inserir(&filaGrande, valor)) {
            printf("[GERADOR] Inserido na fila grande: %d\n", valor);
        }
        int tempo = (rand() % 91 + 10) * 1000; // Entre 10ms e 100ms
        usleep(tempo);
    }
    return NULL;
}

// -------- Thread: Processamento de filas menores --------
void *processarFila(void *arg) {
    int id = *(int *)arg;

    while (tempo_ativo) {
        int valor;
        if (remover(&filaGrande, &valor)) {
            printf("[THREAD %d] Retirado da fila grande: %d\n", id + 1, valor);
            filasMenores[id].processados++;

            int destino = valor - 1;
            if (destino >= 0 && destino < FILAS_MENORES) {
                if (inserir(&filasMenores[destino], valor)) {
                    printf("[FILA %d] Recebeu: %d\n", destino + 1, valor);
                }
            }
        }
        usleep(1000); // Pequeno delay para não sobrecarregar
    }

    return NULL;
}

// -------- Main --------
int main() {
    int i;
    int j;
    srand(time(NULL));

    inicializarFila(&filaGrande, TAMANHO_FILA_GRANDE);
    for (i = 0; i < FILAS_MENORES; i++) {
        inicializarFila(&filasMenores[i], TAMANHO_FILA);
    }

    pthread_t threadGerador;
    pthread_t threadsFilas[FILAS_MENORES];
    int ids[FILAS_MENORES];

    pthread_create(&threadGerador, NULL, gerarNumeros, NULL);

    for (i = 0; i < FILAS_MENORES; i++) {
        ids[i] = i;
        pthread_create(&threadsFilas[i], NULL, processarFila, &ids[i]);
    }

    sleep(TEMPO_TOTAL_SEGUNDOS); // Roda por 60 segundos
    tempo_ativo = 0;

    pthread_join(threadGerador, NULL);
    for (i = 0; i < FILAS_MENORES; i++) {
        pthread_join(threadsFilas[i], NULL);
    }

      // Resultado final
    printf("\n===== RESULTADO FINAL =====\n");
    for (i = 0; i < FILAS_MENORES; i++) {
        printf("Thread %d - Retirados da fila grande: %d | Fila %d - Tamanho final: %d\n",
               i + 1,
               filasMenores[i].processados,
               i + 1,
               filasMenores[i].quantidade);
    }
    printf("Fila Grande - Elementos restantes: %d\n", filaGrande.quantidade);

    // Mostra conteúdo de todas as filas menores
    printf("\n===== CONTEÚDO DAS FILAS MENORES =====\n");
    for (i = 0; i < FILAS_MENORES; i++) {
        printf("Fila %d: ", i + 1);
        int idx = filasMenores[i].inicio;
        for (j = 0; j < filasMenores[i].quantidade; j++) {
            printf("%d ", filasMenores[i].dados[idx]);
            idx = (idx + 1) % filasMenores[i].tamanho;
        }
        printf("\n");
    }

    // Libera memória
    free(filaGrande.dados);
    for (i = 0; i < FILAS_MENORES; i++) {
        free(filasMenores[i].dados);
    }

    return 0;
}

