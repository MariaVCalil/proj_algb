#include "matrizes.h"
#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

    typedef struct {
        char componentes[10][100];
        int qtdEntrada;     // Dimensão do domínio (variáveis de entrada)
        int qtdSaida;       // Dimensão do contradomínio (componentes de saída)
        Matriz matriz;
    } Transformacao;

    void lerTransformacao();
    void parseTransformacao(Transformacao *t);
    void verificarTransformacao(Transformacao *t);

#endif
