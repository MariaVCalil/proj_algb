#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/transformacoes.h"
#include "include/matrizes.h"
#include "include/sistemas.h"
#include "include/menu.h"
#include "include/util.h"

void parseTransformacao(Transformacao *t){      // Extrai a matriz da transformação das strings
    Matriz *matriz = &t->matriz;
    matriz->linhas = t->qtdSaida;       // Uma linha por componente de saída
    matriz->colunas = t->qtdEntrada;    // Uma coluna por variável de entrada

    char variaveis[10];
    for(int i=0;i<t->qtdEntrada;i++){       // Define a ordem das variáveis: x, y, z...
        variaveis[i] = 'x' + i;
    }

    for(int i=0;i<t->qtdSaida;i++){
        for(int j=0;j<matriz->colunas;j++){     // Zera a linha antes de preencher
            matriz->matriz[i][j] = 0;
        }

        char *componente = t->componentes[i];
        int sinal = 1;
        int j = 0;
        while(componente[j] != '\0'){
            if(componente[j] == '+'){
                sinal = 1;
                j++;
            } else if(componente[j] == '-'){
                sinal = -1;
                j++;
            } else {
                double numero = 1;      // Coeficiente do termo (1 quando não vem número escrito)
                if((componente[j] >= '0' && componente[j] <= '9') || componente[j] == '.'){
                    numero = atof(&componente[j]);
                    while((componente[j] >= '0' && componente[j] <= '9') || componente[j] == '.'){
                        j++;
                    }
                }
                if(componente[j] >= 'a' && componente[j] <= 'z'){      // Termo com variável
                    int coluna = 0;
                    while(variaveis[coluna] != componente[j]){
                        coluna++;
                    }
                    matriz->matriz[i][coluna] += sinal * numero;
                    j++;
                }
            }
        }
    }
}

void verificarTransformacao(Transformacao *t){
    Matriz *matriz = &t->matriz;

    // O núcleo é a solução de T(v) = 0, então montamos o sistema homogêneo [A | 0]
    matriz->colunas = t->qtdEntrada + 1;
    for(int i=0;i<matriz->linhas;i++){
        matriz->matriz[i][t->qtdEntrada] = 0;
    }
    escalonar(matriz);
    matriz->colunas = t->qtdEntrada;        // Volta a exibir apenas a matriz A

    printf("\tMatriz escalonada:\n");
    imprimirMatriz(matriz);
    escreverLinha(divisa);
    printf("\n");

    int dimImagem = posto(matriz, t->qtdEntrada);       // Posto = dimensão da imagem
    int dimNucleo = t->qtdEntrada - dimImagem;          // Teorema do núcleo e da imagem

    printf("\tDimensão do núcleo: %d\n", dimNucleo);
    printf("\tDimensão da imagem: %d\n\n", dimImagem);

    int injetora = (dimNucleo == 0);                // Núcleo trivial
    int sobrejetora = (dimImagem == t->qtdSaida);   // Imagem preenche o contradomínio

    if(injetora) printf("\tÉ injetora.\n");
    else printf("\tNão é injetora.\n");

    if(sobrejetora) printf("\tÉ sobrejetora.\n");
    else printf("\tNão é sobrejetora.\n");

    if(injetora && sobrejetora) printf("\tÉ bijetora.\n");
    else printf("\tNão é bijetora.\n");
}

void lerTransformacao(){
    Transformacao t;
    printf("\tQual a dimensão do domínio (nº de variáveis de entrada)?\n  -> ");
    scanf("%d", &t.qtdEntrada);
    printf("\tQual a dimensão do contradomínio (nº de componentes de saída)?\n  -> ");
    scanf("%d", &t.qtdSaida);
    limparTela();
    getchar();
    escreveTitulo(tituloPrinc, " - VERIFICACAO DE TRANSFORMACAO LINEAR");
    printf("\tEscreva as %d componentes de T em função de x, y, z...:\n", t.qtdSaida);
    escreverLinha(divisa);
    for(int i=0;i<t.qtdSaida;i++){
        printf("\t|  ");
        fgets(t.componentes[i], sizeof(t.componentes[i]), stdin);
        t.componentes[i][strcspn(t.componentes[i], "\n")] = '\0';
    }
    limpaEspacos(t.componentes, t.qtdSaida);

    parseTransformacao(&t);
    limparTela();
    escreveTitulo(tituloPrinc, " - VERIFICACAO DE TRANSFORMACAO LINEAR");
    printf("\tMatriz da transformação:\n");
    imprimirMatriz(&t.matriz);
    escreverLinha(divisa);
    printf("\n");
    verificarTransformacao(&t);
}
