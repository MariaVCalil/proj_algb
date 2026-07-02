#include <stdio.h>
#include "include/bases.h"
#include "include/matrizes.h"
#include "include/sistemas.h"
#include "include/menu.h"
#include "include/util.h"

void verificarBase(Conjunto *c){
    Matriz *matriz = &c->matriz;

    // Acrescenta uma coluna de zeros só para reaproveitar o escalonamento
    matriz->colunas = c->dimEspaco + 1;
    for(int i=0;i<matriz->linhas;i++){
        matriz->matriz[i][c->dimEspaco] = 0;
    }
    escalonar(matriz);
    matriz->colunas = c->dimEspaco;     // Volta a exibir apenas as coordenadas

    printf("\tMatriz escalonada (cada vetor é uma linha):\n");
    imprimirMatriz(matriz);
    escreverLinha(divisa);
    printf("\n");

    int postoConj = posto(matriz, c->dimEspaco);        // Nº de vetores linearmente independentes

    printf("\tVetores linearmente independentes (posto): %d\n", postoConj);
    printf("\tDimensão de R%d: %d\n\n", c->dimEspaco, c->dimEspaco);

    // É base quando há exatamente 'dimEspaco' vetores e todos são L.I.
    if(c->qtdVetores == c->dimEspaco && postoConj == c->dimEspaco){
        printf("\tÉ base de R%d.\n", c->dimEspaco);
    } else {
        printf("\tNão é base de R%d.\n", c->dimEspaco);
        if(postoConj == c->dimEspaco){      // Geram o espaço, mas há vetores a mais (L.D.)
            printf("\tUm subconjunto de %d vetores L.I. já é uma base de R%d.\n", c->dimEspaco, c->dimEspaco);
        } else {        // Não geram o espaço inteiro
            printf("\tOs vetores geram um subespaço de dimensão %d.\n", postoConj);
            printf("\tFaltam %d vetor(es) L.I. para completar uma base de R%d.\n", c->dimEspaco - postoConj, c->dimEspaco);
        }
    }
}

void lerBase(){
    Conjunto c;
    printf("\tO conjunto está em qual espaço? (2 para R², 3 para R³)\n  -> ");
    scanf("%d", &c.dimEspaco);
    printf("\tQuantos vetores tem o conjunto?\n  -> ");
    scanf("%d", &c.qtdVetores);
    limparTela();
    escreveTitulo(tituloPrinc, " - DETERMINACAO DE BASES");

    Matriz *matriz = &c.matriz;
    matriz->linhas = c.qtdVetores;
    matriz->colunas = c.dimEspaco;
    printf("\tDigite cada vetor com %d coordenadas (separadas por espaço):\n", c.dimEspaco);
    escreverLinha(divisa);
    for(int i=0;i<c.qtdVetores;i++){
        printf("\tVetor %d:  ", i + 1);
        for(int j=0;j<c.dimEspaco;j++){
            scanf("%lf", &matriz->matriz[i][j]);
        }
    }

    limparTela();
    escreveTitulo(tituloPrinc, " - DETERMINACAO DE BASES");
    printf("\tVetores do conjunto (um por linha):\n");
    imprimirMatriz(matriz);
    escreverLinha(divisa);
    printf("\n");
    verificarBase(&c);
}
