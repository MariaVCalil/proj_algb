#include <stdio.h>
#include <string.h>
#include "include/autovalores.h"
#include "include/transformacoes.h"
#include "include/matrizes.h"
#include "include/sistemas.h"
#include "include/menu.h"
#include "include/util.h"

double raizQuadrada(double valor){      // Raiz quadrada por aproximações sucessivas (Newton)
    if(valor <= 0) return 0;
    double x = valor;
    for(int i=0;i<50;i++){
        x = (x + valor / x) / 2;
    }
    return x;
}

void autovetor(Matriz *matriz, double lambda, double *vx, double *vy){
    // Resolve (A - λI)v = 0 usando as linhas de (A - λI)
    double a = matriz->matriz[0][0] - lambda;
    double b = matriz->matriz[0][1];
    double c = matriz->matriz[1][0];
    double d = matriz->matriz[1][1] - lambda;

    if(!ehZero(a) || !ehZero(b)){       // 1ª linha: a*x + b*y = 0  ->  (b, -a)
        *vx = b;
        *vy = -a;
    } else {        // 1ª linha nula: usa a 2ª linha c*x + d*y = 0  ->  (d, -c)
        *vx = d;
        *vy = -c;
    }
    if(ehZero(*vx) && ehZero(*vy)){     // Caso raro (matriz escalar): qualquer vetor serve
        *vx = 1;
        *vy = 0;
    }

    double normal = !ehZero(*vx) ? *vx : *vy;   // Normaliza o 1º componente não-nulo para 1
    *vx = *vx / normal;
    *vy = *vy / normal;
    if(ehZero(*vx)) *vx = 0;        // Evita imprimir "-0.00"
    if(ehZero(*vy)) *vy = 0;
}

void calcularAutovalores(Transformacao *t){
    if(t->qtdEntrada != 2){     // A questão 4 é R²->R² (matriz 2x2)
        printf("\tImplementado para operadores de R² (2x2), como pede a questão 4.\n");
        printf("\tPara R³ seria necessário resolver um polinômio de grau 3.\n");
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

    printf("\tPolinômio característico: λ² - (%.2lf)λ + (%.2lf)\n", traco, determinante);
    printf("\tΔ = %.2lf\n\n", delta);

    if(delta < -1e-9){      // Raízes complexas: não há autovalores reais
        printf("\tNão existem autovalores reais (autovalores complexos).\n");
        return;
    }

    double raiz = raizQuadrada(delta);
    double lambda1 = (traco + raiz) / 2;
    double lambda2 = (traco - raiz) / 2;

    double vx, vy;
    if(ehZero(delta)){      // Autovalor único (raiz dupla)
        autovetor(matriz, lambda1, &vx, &vy);
        printf("\tAutovalor: λ = %.2lf (multiplicidade 2)\n", lambda1);
        printf("\tAutovetor associado: (%.2lf, %.2lf)\n", vx, vy);
    } else {
        autovetor(matriz, lambda1, &vx, &vy);
        printf("\tλ1 = %.2lf  ->  autovetor (%.2lf, %.2lf)\n", lambda1, vx, vy);
        autovetor(matriz, lambda2, &vx, &vy);
        printf("\tλ2 = %.2lf  ->  autovetor (%.2lf, %.2lf)\n", lambda2, vx, vy);
    }
}

void lerAutovalores(){
    Transformacao t;
    printf("\tO operador está em qual espaço? (2 para R², 3 para R³)\n  -> ");
    scanf("%d", &t.qtdEntrada);
    t.qtdSaida = t.qtdEntrada;      // Operador: domínio = contradomínio
    limparTela();
    getchar();
    escreveTitulo(tituloPrinc, " - AUTOVALORES E AUTOVETORES");
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
    escreveTitulo(tituloPrinc, " - AUTOVALORES E AUTOVETORES");
    printf("\tMatriz do operador:\n");
    imprimirMatriz(&t.matriz);
    escreverLinha(divisa);
    printf("\n");
    calcularAutovalores(&t);
}
