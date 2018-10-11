#ifndef _H_EP1
#define _H_EP1

char *convert(double number, int base);
void menu(void);
void gaussianJordanElimination(double **m, int n);
double **allocateMatrix(int lines, int coluns);

#endif