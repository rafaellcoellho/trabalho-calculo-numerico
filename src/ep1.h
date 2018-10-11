#ifndef _H_EP1
#define _H_EP1

char *convert(double number, int base);
void menu(void);
void gaussianJordanElimination(double **m, int n, int *x);
double **allocateMatrix(int lines, int coluns);
void solveJordanMatrix(double **m, int n, double *result);

#endif