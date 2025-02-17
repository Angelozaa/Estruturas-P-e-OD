#include <stdio.h>
int soma(int n){
	if(n <= 1) return 1;
	else return n + soma(n-1);
}

int main(){
		
	printf("A soma eh: %i ", soma(5));
	
	return 0;
}