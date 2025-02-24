#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selecionar_menor(int A[], int n);
void selecionar_maior(int A[], int n);
void delay(int segundos);
void bubble_sort(int A[], int n);
void gera_vetor(int n);
int i;
int j;
int k;

int main(){
	
	int A[10]={7,4,1,8,5,2,9,6,3,10};
	
	//selecionar_menor(A,10);
	//bubble_sort(A, 10);
	selecionar_maior(A, 10);
	return 0;
}

//---------------------------------------------------------//

void gera_vetor(int n){
	int vetor[n];
	for(i=0; i<n; i++){
		vetor[i]=rand()%(n*2);
	}
}

//---------------------------------------------------------//

void selecionar_maior(int A[], int n){
	for(i=0; i<n; i++){
		int maior = A[i];
		int pos = i;
		for(j=i+1; j<n; j++){
			if(A[j] > maior){
				maior = A[j];
				pos = j;
			}
		}
		A[pos] = A[i];
		A[i] = maior;
		imprime(A,n);
	}
}

//---------------------------------------------------------//

void bubble_sort(int A[], int n){
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(A[i] > A[j-1]){
				int aux = A[i];
				A[i] = A[j-1];
				A[j-1] = aux;
				imprime(A,n);
			}
		}
	}
}

//---------------------------------------------------------//

void imprime(int A[],int n){
	for (k=0; k<n; k++)
		printf("%i  ", A[k]);
	printf("\n\n");
	delay(1);
	
}

//---------------------------------------------------------//

void delay(int segundos){
	int ms = 1000 * segundos;
	clock_t start = clock();
	while(clock()< start + ms);
}

//---------------------------------------------------------//

void selecionar_menor(int A[], int n){
	for(i=0; i<n; i++){
		int menor = A[i];
		int pos = i;
		for(j=i+1; j<n; j++){
			if(A[j] < menor){
				menor = A[j];
				pos = j;
			}
		}
		A[pos] = A[i];
		A[i] = menor;
		imprime(A,n);
		
	}
}

