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
    void parseSistema(Sistema *sistema);
    void parseExpressao(char *expressao, char variaveis[], int qtdVar, double linha[], double *constante);
    void imprimirSistema(Sistema *sistema);
    void resolverSistema(Sistema *sistema);
    void escalonar(Matriz *matriz);
    int posto(Matriz *matriz, int qtdColunas);
    int ehZero(double valor);

#endif