#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Para permitir o teste das funções
#include "ep1.h"

int main(void)
{
	int menu_option;

	do{
		printf("\n");
		printf("C - Conversao\n");
		printf("S - Sistema Linear\n");
		printf("E - Equacao Algebrica\n");
		printf("F - Finalizar\n");
		printf("Escolha uma opcao: ");
		menu_option = getchar();

		// Descarta o enter
		getchar();		

		menu_option = toupper(menu_option);

		switch (menu_option){
			case 'C':
				printf("Digite um numero para ser convertido: \n");
				break;

			case 'S':
				printf("Digite o nome de um arquivo com o sistema linear: \n");
				break;

			case 'E':
				printf("Insira uma equacao: \n");
				break;
		
			case 'F':
				printf("Saindo...\n");
				break;
		
			default:
				printf("\nOpcao invalida, tente novamente!\n");
				break;
		}

	}while(menu_option != 'F');
	
	return 0;
}
