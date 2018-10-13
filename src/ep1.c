#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "ep1.h"

char int_to_ascii[16] = 
	{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/******************************************************************
 *	                        CONVERSÃO                             *
 ******************************************************************/

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

/******************************************************************
 *	                      METODO DE JORDAN                        *
 ******************************************************************/

void gaussianJordanElimination(double **m, int n, int *x)
{
	int i, j, k; // Iteradores
	x[0] = 0; x[1] = 1; x[2] = 2;

	for(i=0;i<n;i++){
		if(m[i][i] == 0){
			j=i+1;
			while(j<n && m[i][j]==0)
				j++;
			if(j<n){
				double aux;
				x[i] = j;
				x[j] = i;
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

void solveJordanMatrix(double **m, int n, double *result)
{
	for(int i = 0; i < n; i++) {
		if((m[i][n] && m[i][i]) == 0)
			result[i] = 0;
		else 
			result[i] = m[i][n] / m[i][i];
	}
}

double **allocateMatrix(long unsigned int lines, long unsigned int coluns)
{
	double **matrix;
	
	matrix = malloc(sizeof(double *) * lines);
	if(matrix == NULL)
		return NULL;
	
	for(long unsigned int i=0; i<lines; i++){
		matrix[i] = malloc(sizeof(double) * coluns);
		if(matrix[i] == NULL){
			for(long unsigned int j=0; j<i; j++)
				free(matrix[j]);
			free(matrix);
			return NULL;
		}
	}

	return matrix;
}

double **leArquivo(char *nome_arquivo, int *numero_de_linhas)
{
	FILE *arquivo;
	double **matriz;

	// Abre o arquivo
	arquivo = fopen(nome_arquivo, "r");
	if (arquivo == NULL) {
		printf("Nao foi possivel abrir o arquivo!\n");
		return NULL;
	}

	// Lê o número de variáveis
	if (fscanf(arquivo, "%d", numero_de_linhas) == 0) {
		printf("Problema ao ler o arquivo!\n");
		return NULL;
	}

	// Aloca dinamicamente a matriz
	matriz = allocateMatrix(*numero_de_linhas, *numero_de_linhas+1);
	if(matriz == NULL){
		printf("Impossivel alocar a matriz!\n");
		return NULL;
	}

	// Lê a matriz aumentada
	for (int i = 0; i < *numero_de_linhas; i++) {
		for (int j = 0; j < *numero_de_linhas+1; j++) {
			if (fscanf(arquivo, "%lf", &matriz[i][j]) == 0) {
				printf("Problema ao ler o arquivo!\n");
				return NULL;
			}
		}
	}

	// Fecha o arquivo
	fclose(arquivo);

	return matriz;
}

void mostraMatriz(double **matriz, int linhas, int colunas)
{
	printf("\n");
	for(int i=0; i<linhas; i++){
		for(int j=0; j<colunas; j++){
			printf("%7.3lf", matriz[i][j]);
		}
		printf("\n");
	}
}

/******************************************************************
 *	                    TEOREMA DE LAGRANGE                       *
 ******************************************************************/



/******************************************************************
 *	                             MENU                             *
 ******************************************************************/

void menu(void)
{
	char raw_input[2];
	int menu_option;

	double number;

	char nome_do_arquivo[100];
	double **matriz;
	int numero_de_linhas;
	int ordem_das_raizes[3];
	double resultado[3];

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
				printf("Digite o nome de um arquivo com o sistema linear: ");
				scanf("%s", nome_do_arquivo);
				matriz = leArquivo(nome_do_arquivo, &numero_de_linhas);
				if (matriz != NULL) {
					gaussianJordanElimination(matriz, numero_de_linhas, ordem_das_raizes);
					mostraMatriz(matriz, numero_de_linhas, numero_de_linhas+1);
					solveJordanMatrix(matriz, numero_de_linhas, resultado);
					printf("\n");
					for (int i = 0; i < numero_de_linhas; i++) 
						printf("  x%d = %lf\n", i, resultado[ ordem_das_raizes[i] ]);
				}
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
