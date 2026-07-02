#include "matrizes.h"
#ifndef BASES_H
#define BASES_H

    typedef struct {
        int dimEspaco;      // 2 para R², 3 para R³
        int qtdVetores;
        Matriz matriz;      // Cada vetor ocupa uma linha
    } Conjunto;

    void lerBase();
    void verificarBase(Conjunto *c);

#endif
