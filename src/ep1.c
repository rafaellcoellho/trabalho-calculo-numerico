#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "ep1.h"

char int_to_ascii[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


// Corverte um numero do sistema de base 10 para outro
char *convert(double number, int base)
{
	double num_int, num_frac;
	char *bin = calloc(50, sizeof(char));
	int position = 0;
	
	// Separa a parte inteira da fracionária
	num_frac = modf(number, &num_int);

	if(num_int != 0){
		char aux[30];

		do{
			aux[position++] = int_to_ascii[ (int)num_int % base ];
			num_int = floor(num_int/base);
		} while (num_int > 0);

		for(int i = 0; i < position; i++)
			bin[i] = aux[position-i-1];
	} else {
		bin[position++] = '0';
	}

	bin[position++] = '.';

	if(num_frac != 0){
		double bit;
		int max_digits = 20;
		while (num_frac > 0 && max_digits > 0) {
			num_frac *= base;
			num_frac = modf(num_frac, &bit);
			bin[position++] = int_to_ascii[ (int)bit ];
			max_digits--;
		}
	} else {
		bin[position] = '0';
	}

	return bin;
}


void gaussianJordanElimination(double m[][4], int n)
{
	int i, j, k; // Iteradores

	for(i=0;i<n;i++){
		if(m[i][i] == 0){
			j=i+1;
			while(j<n && m[i][j]==0)
				j++;
			if(j<n){
				double aux;
				for(k=0;k<n;k++){
					aux = m[k][i];
					m[k][i] = m[k][j];
					m[k][j] = aux;
				}
			}else{
				for(k=0;k<n;k++)
					m[k][i]=0;
			}
		}
		if(m[i][i]!=0){
			for(j=0;j<n;j++){
				if(j!=i){
					double mult = -m[j][i]/m[i][i];
					m[j][i] = 0;
					for(k=i+1;k<=n;k++){
						m[j][k] += mult*m[i][k];
					}
				}
			}
		}
	}
}


void menu(void)
{
	char raw_input[2];
	int menu_option;
	double number;

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
				printf("Digite um numero para ser convertido: ");
				scanf("%lf", &number);
				printf("\nBin: %s", convert(number, 2));
				printf("\nOctal: %s", convert(number, 8));
				printf("\nHex: %s", convert(number, 16));
				printf("\n");
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

	} while (menu_option != 'F');
}
