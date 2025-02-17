#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void insertion_sort(int A[10]){
	for (int j=1; j<10; j++){
		int chave= A[j];
		int i= j-1;
		while( i>=0 && A[i]>chave){
			A[i+1] = A[i];
			i = i-1;
		}
		A[i+1]= chave;
	}
}

int main(){
	int A[10];
	//gera numeros aleatorios
	for (int i = 0; i < 10; i++){
  		A[i]=rand()%100;
    }
    
    //apresenta os numero aleatorios
	for(int i=0; i<10; i++){
		printf("%d ", A[i]);
	}
	printf("\n-------------\n");
	
	//apresenta ordenado
	insertion_sort(A);
	for(int i=0; i<10; i++){
		printf("%d ", A[i]);
	}
	
	return 0;
}