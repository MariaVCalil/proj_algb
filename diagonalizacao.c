#include <stdio.h>
#include <string.h>
#include "include/diagonalizacao.h"
#include "include/transformacoes.h"
#include "include/autovalores.h"
#include "include/sistemas.h"
#include "include/matrizes.h"
#include "include/menu.h"
#include "include/util.h"

void imprimirDiagonal(double lambda1, double lambda2){      // Monta e mostra a matriz diagonal D
    Matriz d;
    d.linhas = 2;
    d.colunas = 2;
    d.matriz[0][0] = lambda1;   d.matriz[0][1] = 0;
    d.matriz[1][0] = 0;         d.matriz[1][1] = lambda2;
    printf("\tMatriz diagonal D:\n");
    imprimirMatriz(&d);
}

void diagonalizarOperador(Transformacao *t){
    if(t->qtdEntrada != 2){     // A questão 5 usa os operadores da questão 4 (R²->R²)
        printf("\tImplementado para operadores de R² (2x2), como pede a questão 5.\n");
        return;
    }

    Matriz *matriz = &t->matriz;
    double a = matriz->matriz[0][0];
    double b = matriz->matriz[0][1];
    double c = matriz->matriz[1][0];
    double d = matriz->matriz[1][1];

    double traco = a + d;
    double determinante = a * d - b * c;
    double delta = traco * traco - 4 * determinante;    // Discriminante de λ² - (traço)λ + det = 0

    if(delta < -1e-9){      // Autovalores complexos
        printf("\tAutovalores complexos: não é diagonalizável em R.\n");
        return;
    }

    if(ehZero(delta)){      // Autovalor real repetido
        double lambda = traco / 2;
        // Só é diagonalizável se A já for λI (isto é, A - λI = 0)
        if(ehZero(b) && ehZero(c) && ehZero(a - lambda) && ehZero(d - lambda)){
            printf("\tAutovalor repetido com A = λI: é diagonalizável.\n\n");
            imprimirDiagonal(lambda, lambda);
        } else {
            printf("\tAutovalor repetido com um só autovetor: não é diagonalizável.\n");
        }
        return;
    }

    // delta > 0: dois autovalores reais distintos -> é diagonalizável
    double raiz = raizQuadrada(delta);
    double lambda1 = (traco + raiz) / 2;
    double lambda2 = (traco - raiz) / 2;
    printf("\tDois autovalores reais distintos: é diagonalizável.\n\n");
    imprimirDiagonal(lambda1, lambda2);
}

void lerDiagonalizacao(){
    Transformacao t;
    printf("\tO operador está em qual espaço? (2 para R², 3 para R³)\n  -> ");
    scanf("%d", &t.qtdEntrada);
    t.qtdSaida = t.qtdEntrada;      // Operador: domínio = contradomínio
    limparTela();
    getchar();
    escreveTitulo(tituloPrinc, " - DIAGONALIZACAO");
    printf("\tEscreva as %d componentes do operador em função de x, y...:\n", t.qtdSaida);
    escreverLinha(divisa);
    for(int i=0;i<t.qtdSaida;i++){
        printf("\t|  ");
        fgets(t.componentes[i], sizeof(t.componentes[i]), stdin);
        t.componentes[i][strcspn(t.componentes[i], "\n")] = '\0';
    }
    limpaEspacos(t.componentes, t.qtdSaida);

    parseTransformacao(&t);
    limparTela();
    escreveTitulo(tituloPrinc, " - DIAGONALIZACAO");
    printf("\tMatriz do operador:\n");
    imprimirMatriz(&t.matriz);
    escreverLinha(divisa);
    printf("\n");
    diagonalizarOperador(&t);
}
