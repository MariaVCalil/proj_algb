#include "matrizes.h"
#ifndef SISTEMAS_H
#define SISTEMAS_H

    typedef struct {
        char equacoes[10][100];
        int qtdLinhas;
        int qtdIcog;
        Matriz matriz;
    } Sistema;
    
    void lerSistema();

#endif