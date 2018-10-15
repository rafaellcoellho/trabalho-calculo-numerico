#ifndef _H_EP1
#define _H_EP1

char *converter(double numero_decimal, int base_destino);
void metodo_de_jordan(double **m, int ordem_matriz_coeficientes, int *ordem_das_raizes);
int solucionar_matriz_jordan(double **m, int ordem_matriz_coeficientes, double *raizes);

void aplicar_teorema_de_langrange(double *polinomio, int ordem, double *intervalo_positivo, double *intervalo_negativo);
double aplicar_metodo_da_bissecao(double *polinomio, int ordem, double *intervalo);

double **aloca_matriz(long unsigned int lines, long unsigned int coluns);

void menu(void);

#endif