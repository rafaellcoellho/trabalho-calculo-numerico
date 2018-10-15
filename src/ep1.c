#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "ep1.h"


// Array auxiliar para converter um inteiro para char,
// o inteiro é usado como índice neste array e lhe é devolvido o char correspondente
char int_para_ascii[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


/******************************************************************
 *	                        CONVERSÃO                             *
 ******************************************************************/

/**
 *	Converte um numero de base dez para outra base
 *
 *	@param numero_decimal - Numero de base dez a ser convertido
 *	@param base_destino - numero que representa a base do sistema numerico destino
 *	@return numero convertido para o sistema destino
 */
char *converter(double numero_decimal, int base_destino)
{
	double parte_inteira, parte_fracionaria;
	char *numero_convertido = calloc(50, sizeof(char));
	int posicao = 0;
	
	// Separa a parte inteira da fracionária
	parte_fracionaria = modf(numero_decimal, &parte_inteira);

	// Calcula a parte inteira do resultado dividindo a parte inteira
	// do numero pela base até ficar indivisivel pela base
	if (parte_inteira != 0) {
		char aux[30];

		do {
			aux[posicao++] = int_para_ascii[ (int)parte_inteira % base_destino ];
			parte_inteira = floor(parte_inteira/base_destino);
		} while (parte_inteira > 0);

		for(int i = 0; i < posicao; i++)
			numero_convertido[i] = aux[posicao-i-1];
	} else {
		numero_convertido[posicao++] = '0';
	}

	numero_convertido[posicao++] = '.';

	// Calcula a parte fracionária do resultado mutiplicando a parte 
	// fracionaria do numero pela base até a parte fracionaria ser zero
	if (parte_fracionaria != 0) {
		// Variavel auxiliar para armazenamento da parte inteira da multiplicacao
		double resultado_inteiro;

		// Limite de casas decimais para o numero convertido
		int numero_max_digitos = 20; 	

		while (parte_fracionaria > 0 && numero_max_digitos > 0) {
			parte_fracionaria *= base_destino;
			parte_fracionaria = modf(parte_fracionaria, &resultado_inteiro);
			numero_convertido[posicao++] = int_para_ascii[ (int)resultado_inteiro ];
			numero_max_digitos--;
		}
	} else {
		numero_convertido[posicao] = '0';
	}

	return numero_convertido;
}



/******************************************************************
 *	                      METODO DE JORDAN                        *
 ******************************************************************/

/**
 *	Executa o metodo de jordan
 *
 *	@param m - Matriz Aumentada
 *	@param ordem_matriz_coeficientes - ordem da matriz ao retirar coluna dos termos independentes
 *	@param ordem_das_raizes - vetor que relaciona a posicao das raizes de acordo com as colunas
 */ 
void metodo_de_jordan(double **m, int ordem_matriz_coeficientes, int *ordem_das_raizes)
{
	// Iteradores
	int i, j, k;

	// Mapea a ordem das raizes de acordo com as colunas
	int xi = 0;
	while(xi < ordem_matriz_coeficientes) {
		ordem_das_raizes[xi] = xi;
		xi++;
	}

	// Percorre as linhas da matriz atribuindo pivo M(i,i)
	for (i = 0; i < ordem_matriz_coeficientes; i++) {
		// Se pivo igual a zero, procura uma coluna a direita para trocar
		if(m[i][i] == 0) {
			j = i + 1;
			while (j < ordem_matriz_coeficientes && m[i][j]==0)
				j++;

			// Realiza uma troca de colunas se uma coluna válida for encontrada
			if (j < ordem_matriz_coeficientes) {
				// A ordem das raizes sao rearranjadas
				ordem_das_raizes[i] = j;
				ordem_das_raizes[j] = i;

				double aux;
				for(k = 0; k < ordem_matriz_coeficientes; k++) {
					aux = m[k][i];
					m[k][i] = m[k][j];
					m[k][j] = aux;
				}
			}
			// Se uma coluna valida não for encontrada, atribui-se zero aos elementos da coluna do pivo
			else {
				for(k = 0; k < ordem_matriz_coeficientes; k++)
					m[k][i] = 0;
			}
		}

		// Se o pivo é diferente de zero é calculado o multiplicador
		// e é feita as operações nas linhas abaixo e acima
		if (m[i][i] != 0) {
			for (j = 0; j < ordem_matriz_coeficientes; j++) {
				if (j != i) {
					double multiplicador = -m[j][i] / m[i][i];
					m[j][i] = 0;
					for (k = i+1; k <= ordem_matriz_coeficientes; k++) {
						m[j][k] += multiplicador * m[i][k];
					}
				}
			}
		}
	}
}



/**
 *	Realiza operacao para o calculo das raizes do sistema linear na matriz de jordan
 *
 *	@param m - matriz aumentada
 *	@param ordem_matriz_coeficientes - ordem da matriz ao retirar coluna dos termos independentes
 *	@param raizes - vetor com as raizes do sistema
 *	@return tipo do sistema linear: 0-Compativel Determinado / 1-Compativel Indeterminado / 2-Iconpativel
 */
int solucionar_matriz_jordan(double **m, int ordem_matriz_coeficientes, double *raizes)
{
	int tipo = 0;

	for(int i = 0; i < ordem_matriz_coeficientes; i++) {
		// atribui a zero caso seja variavel livre
		if((m[i][ordem_matriz_coeficientes] && m[i][i]) == 0) {
			raizes[i] = 0;
			tipo = 1;
		}
		// retorna incompativel caso coeficente seja zero e o termo independete nao
		else if (m[i][ordem_matriz_coeficientes] != 0 && m[i][i] == 0) {
			return 2;
		}
		// realiza calculo da raiz e adiciona na lista de raizes
		else 
			raizes[i] = m[i][ordem_matriz_coeficientes] / m[i][i];
	}

	return tipo;
}



/******************************************************************
 *	              TEOREMA DE LAGRANGE E BISSECAO                  *
 ******************************************************************/

/**
 *   Inverte o conteudo do array
 *   @param array - lista a ser convertido
 *   @param n - numero de elementos de array
 */
void inverter_array(double *array, int n) {
    int t, end = n - 1;

    for (int c = 0; c < n/2; c++) {
        t          = array[c];
        array[c]   = array[end];
        array[end] = t;
    
        end--;
    }
}


/**
 *   Troca os sinais dos coeficientes que multiplicam 
 *   varivel elevado a potencia impar
 * 
 *   @param polinomio - array com os coeficientes do polinomio
 *   @param ordem - ordem do polinomio
 */
void trocar_sinais_dos_coeficientes_An_com_n_impar(double *polinomio, int ordem) {
    for (int i = 0; i <= ordem; i++) {
        // Se a ordem - indice é impar, significa que n é impar
        // Ex.: 4-0 = 0, logo nao inverte / 4-1 = 3, logo inverte o sinal
        if (!((ordem - i) % 2 == 0)) {
            polinomio[i] *= -1;
        }
    }
}


/**
 *   Calcula limite da raiz de um polinomio de acordo com a 
 *   formula: L = 1 + raiz(n-k) de b/An
 * 
 *   @param polinomio - array com os coeficientes do polinomio
 *   @param ordem - ordem do polinomio
 *   @return limite da raiz do polinomio, caso nao exista raizes reais retorna -1
 */
double calcular_limite(double *polinomio, int ordem) {
    double n, an, k, b;
    int multiplicadoPorUmNegativo = 0;

    // Se An for negativo, multiplica-se o polinomio por -1
    if (polinomio[0] < 0) {
        for (int i = 0; i <= ordem; i++)
            polinomio[i] *= -1;
        multiplicadoPorUmNegativo = 1;
    }

    n = ordem;
    an = polinomio[0];
    
    k = 0;
    // Verifica primeiro indice se coeficiente for negativo
    for (int i = 0; i < ordem; i++) {
        if (polinomio[i] < 0) {
            k = ordem - i;
            break;
        }
    }

    b = 0;
    // Percorre os coeficiente e armazena em b, o maior negativo em modulo
    for (int i = 0; i < ordem; i++) {
        if (polinomio[i] < 0 && abs(polinomio[i]) > b) {
            b = abs(polinomio[i]);
        }
    }

    // Desfaz a multiplicao por -1 se esta foi feita previamente
    if (multiplicadoPorUmNegativo == 1) {
        for (int i = 0; i <= ordem; i++)
            polinomio[i] *= -1;
    }

	// Caso nao exista raizes reais retorna -1
    if ((k && b) == 0)
        return -1;

    // Aplica a formula e retorna seu valor
    return 1 + pow(b/an, 1.0/(n-k));
}


/**
 *   Aplica em um polinomio o teorema de lagrange retornando os intervalos
 *   das raizes positivas e negativas do polinomio
 * 
 *   @param polinomio - array com os coeficientes do polinomio
 *   @param ordem - ordem do polinomio
 *   @param intervalo_positivo - array onde ira ser guardado o intervalo das raizes positivas
 *   @param intervalo_negativo - array onde ira ser guardado o intervalo das raizes negativas
 */
void aplicar_teorema_de_langrange(double *polinomio, int ordem, double *intervalo_positivo, double *intervalo_negativo) {
    double l, l1, l2, l3;
    
    l = calcular_limite(polinomio, ordem);

    // Inverte coeficientes do polinomio para encontrar p1
    inverter_array(polinomio, ordem+1);
    l1 = calcular_limite(polinomio, ordem);

    // Desinverte os coeficentes para retornar ao polinomio original e 
    // inverte os sinais para encontrar p2
    inverter_array(polinomio, ordem+1);
    trocar_sinais_dos_coeficientes_An_com_n_impar(polinomio, ordem);
    l2 = calcular_limite(polinomio, ordem);

    // Inverte os coefiecientes para encontra p3
    inverter_array(polinomio, ordem+1);
    l3 = calcular_limite(polinomio, ordem);

    // Devolvendo o polinomio ao estado inicial
    inverter_array(polinomio, ordem+1);
    trocar_sinais_dos_coeficientes_An_com_n_impar(polinomio, ordem);
    
    intervalo_positivo[0] = 1.0/l1;
    intervalo_positivo[1] = l;
    intervalo_negativo[0] = -l2;
    intervalo_negativo[1] = -(1.0/l3);
}


/**
 *   Aplica o metodo da bissecao em um polinomio
 *   dado um intervalo e é retornado uma raiz aproximada
 * 
 *   @param polinomio - array com os coeficientes do polinomio
 *   @param ordem - ordem do polinomio
 *   @param intervalo - intervalo para calculo do metodo
 *   @return raiz aproximada do polinomio contida no intervalo
 */
double aplicar_metodo_da_bissecao(double *polinomio, int ordem, double *intervalo) {
    double a = intervalo[0], b = intervalo[1];
    double m, erro, f_a, f_m;

    for (int i = 0; i < 1000; i++) {
        m = (a+b) / 2;
        // Retorna m se o erro é menor que 10^⁻8
        if ((m - a) < 0.00000001)
            return m;

        f_a = 0;
        f_m = 0;
        // Calcula p(a) e p(m)
        for (int xi = ordem; xi >= 0; xi--) {
            f_a += polinomio[ordem - xi] * pow(a, xi);
            f_m += polinomio[ordem - xi] * pow(m, xi);
        }
        // Substitui m em a caso f(a)xf(m) > 0
        if (f_a * f_m > 0)
            a = m;
        // Substitui m em b caso f(a)xf(m) < 0
        else if (f_a * f_m < 0)
            b = m;
        // Caso f(m) = 0 m é raiz, logo é retornado
        else
            return m;
    }
    // Ao passar 1000 iterações é retornado m sendo este uma raiz aproximada
    return m;
}


/******************************************************************
 *     	                    UTILITARIOS                           *
 ******************************************************************/

/**
 *	Aloca matriz na memoria
 *
 *	@param linhas - numero de linhas da matriz
 *	@param colunas - numero de colunas da matriz
 *	@return retorna a matriz caso consiga alocar, caso contrário retorna NULL
 */
double **aloca_matriz(long unsigned int linhas, long unsigned int colunas)
{
	double **matriz;
	
	matriz = malloc(sizeof(double *) * linhas);
	if (matriz == NULL)
		return NULL;
	
	for (long unsigned int i = 0; i < linhas; i++) {
		matriz[i] = malloc(sizeof(double) * colunas);
		if (matriz[i] == NULL) {
			for(long unsigned int j=0; j<i; j++)
				free(matriz[j]);
			free(matriz);
			return NULL;
		}
	}

	return matriz;
}


/**
 *	Le arquivo e aloca seus valores em uma matriz
 *
 *	@param nome_arquivo - Nome do arquivo a partir da origem da aplicacao
 *	@param numero_de_linhas - numero de linhas da matriz
 *	@return matriz com o conteudo lido, se ocorrer erro ao ler o arquivo retorna NULL
 */
double **le_arquivo(char *nome_arquivo, int *numero_de_linhas)
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
	matriz = aloca_matriz(*numero_de_linhas, *numero_de_linhas+1);
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



/**
 *	Imprime matriz no console
 *
 *	matriz - matriz a ser mostrada no console
 *	linhas - numero de linhas da matriz
 *	colunas - numero de linhas da colunas
 */
void mostra_matriz(double **matriz, int linhas, int colunas)
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
 *	                             MENU                             *
 ******************************************************************/

void menu(void)
{
	char raw_input[2];
	int opcao_menu;

	double numero;

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

		opcao_menu = toupper(raw_input[0]);

		switch (opcao_menu){
			case 'C':
				printf("Digite um numero para ser convertido: ");
				scanf("%lf", &numero);
				printf("\nBin: %s", converter(numero, 2));
				printf("\nOctal: %s", converter(numero, 8));
				printf("\nHex: %s", converter(numero, 16));
				printf("\n");
				break;

			case 'S':
				printf("Digite o nome de um arquivo com o sistema linear: ");
				scanf("%s", nome_do_arquivo);
				matriz = le_arquivo(nome_do_arquivo, &numero_de_linhas);
				if (matriz != NULL) {
					metodo_de_jordan(matriz, numero_de_linhas, ordem_das_raizes);
					mostra_matriz(matriz, numero_de_linhas, numero_de_linhas+1);
					int tipo = solucionar_matriz_jordan(matriz, numero_de_linhas, resultado);
					printf("\n");
					if (tipo == 2) {
						printf("Sistema Linear Incompativel\n");
					}
					else {
						printf("Sistema Linear %sDeterminado\n", tipo == 1 ? "IN":"");
						for (int i = 0; i < numero_de_linhas; i++)
							printf("  x%d = %lf\n", i, resultado[ ordem_das_raizes[i] ]);
					}
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

	} while (opcao_menu != 'F');
}
