#ifndef _H_EP1
#define _H_EP1

char *converte(double numero_decimal, int base_destino);
void metodo_de_jordan(double **m, int ordem_matriz_coeficientes, int *ordem_das_raizes);
int soluciona_matriz_diagonal(double **m, int ordem_matriz_coeficientes, double *raizes);

void teorema_de_lagrange(double *polinomio, int ordem, double *intervalo_positivo, double *intervalo_negativo);
int teorema_de_bolzano(double *polinomio, int grau, double *intervalo);
double metodo_da_bissecao(double *polinomio, int ordem, double *intervalo);

double **aloca_matriz(long unsigned int lines, long unsigned int coluns);

void menu(void);

#endif