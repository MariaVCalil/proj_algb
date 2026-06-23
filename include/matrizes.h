#ifndef MATRIZES_H
#define MATRIZES_H

typedef struct {
    int linhas;
    int colunas;
    double matriz[10][10];
    char sistema[50][50];
} Matriz;

void lerMatriz(Matriz *m);
void imprimirMatriz(Matriz *m);

#endif