#include <stdio.h>
#include <stdlib.h>

/*
Crie duas estruturas (Vetores) com n posições cada 
Cada estrutura criada sera um estacionamento que terá 
2 vezes n vagas

Criar vetor auxiliar de tamanho n para servir como local de manobra

Crie um menu com as operaçõe: estacionar e retirar um carro de acordo com a placa
*/

int est1[5] = {0,0,0,0,0};
int est2[5] = {0,0,0,0,0};
int manobra[5] = {0,0,0,0,0};

int vagas1 = 5;
int vagas2 = 5;
int livres = 10;

int estaCheio();
void estacionar();
void retirar();

int main(){
	//criar um  menu apresentar as vagas.
	int escolha = 0;
	do{
		printf("Vagas Diponiveis: %i \n\n", livres);	
		printf("1 - Inserir\n");
		printf("2 - Retirar\n");
		printf("9 - Fechar!\n");
		scanf("%i", &escolha);
		
		if(escolha == 1){
			estacionar();
		}
		
		if(escolha == 2){
			retirar();
		}
	}while(escolha != 9);
	
	return 0;
}

int estaCheio(){
	return livres;
}

void estacionar(){
	if(estaCheio){
		int placa;
		printf("Digite a placa: \n");
		scanf("%i", &placa);
		if(vagas1 > 0){
			//estaciona no 1
			est1[5-vagas1] = placa;
			vagas1--;
			livres--;
		}else if(vagas2 > 0){
			//estaciona no 2
			est2[5-vagas2] = placa;
			vagas2--;
			livres--;
		}
	}else{
		printf("Está cheio. ");
	}
}

void retirar(){
	int placa;
	int i = 0;
	int topo;
	printf("Digite a placa do seu carro irmao: ");
	scanf("%i", &placa);
	if(vagas1>0){
		topo = 4 - vagas1;
		while(placa != est1[topo]){
			manobra[i] = est1[topo];
			i++;
			topo--;
		}
		i--;
		topo--;
		while(i >= 0){
			est1[i] = manobra[topo];
			i--;
			topo++;
		}
		livres++;
	}else if(vagas2>0){
		topo = 4 - vagas2;
		while(placa != est2[topo]){
			manobra[i] = est2[topo];
			i++;
			topo--;
		}
		i--;
		topo--;
		while(i >= 0){
			est2[i] = manobra[topo];
			i--;
			topo++;
		}
		livres++;
	}else{
		printf("Nem tem carro fih");
	}
}
