#ifndef _H_EP1
#define _H_EP1

char *converter(double numero_decimal, int base_destino);
void metodo_de_jordan(double **m, int ordem_matriz_coeficientes, int *ordem_das_raizes);
int solucionar_matriz_jordan(double **m, int ordem_matriz_coeficientes, double *raizes);

double **alocaMatriz(long unsigned int lines, long unsigned int coluns);

void menu(void);

#endif