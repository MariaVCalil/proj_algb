#include <stdio.h>
#include "include/matrizes.h"

void lerMatriz(Matriz *m){
    scanf("%d", &m->linhas);
    scanf("%d", &m->colunas);

    for(int i=0; i < m->linhas; i++){
        for(int j=0; j < m->colunas; j++){
            scanf("%lf", &m->matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimirMatriz(Matriz *m){
    for(int i=0; i < m->linhas; i++){
        printf("\t|  ");
        for(int j=0; j < m->colunas; j++){
            printf("%8.2lf", m->matriz[i][j]);    
        }
        printf("\n");
    }
}