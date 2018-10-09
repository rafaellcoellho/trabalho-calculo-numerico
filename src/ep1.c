#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Para permitir o teste das funções
#include "ep1.h"

char *convert_to_bin(double number)
{
	double num_int, num_frac;
	char *bin = calloc(50, sizeof(char));
	int position = 0;
	
	// Separa a parte inteira da fracionária
	num_frac = modf(number, &num_int);

	if(num_int != 0){
		char aux[30];

		do{
			aux[position++] = (char)('0' + (int)fmod(num_int, 2));
			num_int = floor(num_int/2);
		} while (num_int > 0);

		for(int i = 0; i < position; i++)
			bin[i] = aux[position-i-1];
	} else {
		bin[position++] = '0';
	}

	bin[position++] = '.';

	if(num_frac != 0){
		double bit;
		while (num_frac > 0) {
			num_frac *= 2;
			num_frac = modf(num_frac, &bit);
			bin[position++] = (char)('0' + (int)bit);
		}
	} else {
		bin[position] = '0';
	}

	return bin;
}

int main(void)
{
	char raw_input[2];
	int menu_option;

	do{
		printf("\n");
		printf("C - Conversao\n");
		printf("S - Sistema Linear\n");
		printf("E - Equacao Algebrica\n");
		printf("F - Finalizar\n");
		printf("Escolha uma opcao: ");
		scanf("%s", raw_input);	

		menu_option = toupper(raw_input[0]);

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
