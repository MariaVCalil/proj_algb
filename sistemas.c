#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/sistemas.h"
#include "include/matrizes.h"
#include "include/menu.h"
#include "include/util.h"
#include "include/arquivos.h"

void parseExpressao(char *expressao, char variaveis[], int qtdVar, double linha[], double *constante){
    int sinal = 1;
    int lado = 1;       // 1 = antes do '=', -1 = depois do '='
    int j = 0;
    while(expressao[j] != '\0'){
        if(expressao[j] == '+'){
            sinal = 1;
            j++;
        } else if(expressao[j] == '-'){
            sinal = -1;
            j++;
        } else if(expressao[j] == '='){
            lado = -1;
            sinal = 1;
            j++;
        } else {
            double numero = 1;      // Coeficiente do termo (1 quando não vem número escrito)
            if((expressao[j] >= '0' && expressao[j] <= '9') || expressao[j] == '.'){
                numero = atof(&expressao[j]);
                while((expressao[j] >= '0' && expressao[j] <= '9') || expressao[j] == '.'){
                    j++;
                }
                if(expressao[j] == '/'){        // Coeficiente em fração (ex.: 5/2)
                    j++;
                    numero = numero / atof(&expressao[j]);
                    while((expressao[j] >= '0' && expressao[j] <= '9') || expressao[j] == '.'){
                        j++;
                    }
                }
            }
            if(expressao[j] >= 'a' && expressao[j] <= 'z'){      // Termo com variável
                int coluna = 0;
                while(variaveis[coluna] != expressao[j]){
                    coluna++;
                }
                linha[coluna] += lado * sinal * numero;
                j++;
            } else {        // Termo constante: vai para o termo independente, trocando de lado
                *constante -= lado * sinal * numero;
            }
        }
    }
}

void parseSistema(Sistema *sistema){        // Extrai a matriz aumentada das strings do sistema
    Matriz *matriz = &sistema->matriz;
    matriz->linhas = sistema->qtdLinhas;
    matriz->colunas = sistema->qtdIcog + 1;     // Colunas = incógnitas + termo independente

    char variaveis[10];
    for(int i=0;i<sistema->qtdIcog;i++){        // Define a ordem das variáveis: x, y, z...
        variaveis[i] = 'x' + i;
    }

    for(int i=0;i<sistema->qtdLinhas;i++){
        for(int j=0;j<matriz->colunas;j++){     // Zera a linha antes de preencher
            matriz->matriz[i][j] = 0;
        }
        double constante = 0;
        parseExpressao(sistema->equacoes[i], variaveis, sistema->qtdIcog, matriz->matriz[i], &constante);
        matriz->matriz[i][sistema->qtdIcog] = constante;    // Termo independente na última coluna
    }
}

void imprimirSistema(Sistema *sistema){
    Matriz *matriz = &sistema->matriz;
    for(int i=0;i<matriz->linhas;i++){
        printf("\t|\t");
        for(int j=0;j<sistema->qtdIcog;j++){ // percorre as colunas das icognitas
            printf("%+.2lf%c\t", matriz->matriz[i][j], 'x' + j);
        }
        printf("=  %.2lf\n", matriz->matriz[i][sistema->qtdIcog]); // percorre após o =
    }
}

int ehZero(double valor){       // Verifica se o valor é praticamente zero (tolerância)
    return valor < 1e-9 && valor > -1e-9;
}

void trocarLinhas(Matriz *matriz, int a, int b){        // Troca duas linhas de lugar
    for(int j=0;j<matriz->colunas;j++){
        double tmp = matriz->matriz[a][j];
        matriz->matriz[a][j] = matriz->matriz[b][j];
        matriz->matriz[b][j] = tmp;
    }
}

void escalonar(Matriz *matriz){     // Escalona a matriz aumentada (eliminação de Gauss)
    int linha = 0;      // Linha onde o próximo pivô será colocado
    for(int col=0;col<matriz->colunas-1 && linha<matriz->linhas;col++){
        int pivo = -1;
        for(int i=linha;i<matriz->linhas;i++){      // Procura um pivô não-nulo na coluna
            if(!ehZero(matriz->matriz[i][col])){
                pivo = i;
                break;
            }
        }
        if(pivo == -1) continue;        // Coluna sem pivô: variável livre

        trocarLinhas(matriz, linha, pivo);      // Leva o pivô para a linha atual
        for(int i=linha+1;i<matriz->linhas;i++){        // Zera os valores abaixo do pivô
            double fator = matriz->matriz[i][col] / matriz->matriz[linha][col];
            for(int j=col;j<matriz->colunas;j++){
                matriz->matriz[i][j] -= fator * matriz->matriz[linha][j];
            }
        }
        linha++;
    }
}

int posto(Matriz *matriz, int qtdColunas){      // Conta as linhas não-nulas nas primeiras colunas
    int total = 0;
    for(int i=0;i<matriz->linhas;i++){
        int naoNula = 0;
        for(int j=0;j<qtdColunas;j++){
            if(!ehZero(matriz->matriz[i][j])){
                naoNula = 1;
            }
        }
        if(naoNula) total++;
    }
    return total;
}

void resolverSistema(Sistema *sistema){
    Matriz *matriz = &sistema->matriz;
    escalonar(matriz);

    printf("\tMatriz escalonada:\n");
    imprimirMatriz(matriz);
    escreverLinha(divisa);
    printf("\n");

    int postoA = posto(matriz, sistema->qtdIcog);           // Posto da matriz dos coeficientes
    int postoAmpliada = posto(matriz, matriz->colunas);     // Posto da matriz aumentada

    if(postoA < postoAmpliada){         // Sobra uma linha do tipo "0 = valor"
        printf("\tSistema Impossível (SI): não possui solução.\n");
    } else if(postoA == sistema->qtdIcog){      // Um pivô para cada incógnita
        double solucao[10];
        for(int i=sistema->qtdIcog-1;i>=0;i--){     // Retro-substituição
            double soma = matriz->matriz[i][sistema->qtdIcog];      // Termo independente
            for(int j=i+1;j<sistema->qtdIcog;j++){
                soma -= matriz->matriz[i][j] * solucao[j];
            }
            solucao[i] = soma / matriz->matriz[i][i];
        }
        printf("\tSistema Possível e Determinado (SPD): solução única.\n\n");
        for(int i=0;i<sistema->qtdIcog;i++){
            printf("\t%c = %.2lf\n", 'x' + i, solucao[i]);
        }
    } else {        // postoA < qtdIcog
        printf("\tSistema Possível e Indeterminado (SPI): infinitas soluções.\n");
        printf("\t%d variável(is) livre(s). Solução geral:\n\n", sistema->qtdIcog - postoA);

        int ehPivo[10] = {0};       // Marca quais variáveis têm pivô
        for(int i=0;i<matriz->linhas;i++){
            for(int j=0;j<sistema->qtdIcog;j++){        // Primeiro não-nulo da linha = pivô
                if(!ehZero(matriz->matriz[i][j])){
                    ehPivo[j] = 1;
                    // Isola a variável do pivô em função das demais
                    printf("\t%c = %.2lf", 'x' + j, matriz->matriz[i][sistema->qtdIcog] / matriz->matriz[i][j]);
                    for(int k=j+1;k<sistema->qtdIcog;k++){
                        double coef = matriz->matriz[i][k] / matriz->matriz[i][j];
                        if(!ehZero(coef)){      // O termo passa para o outro lado, trocando de sinal
                            printf(" %c %.2lf%c", coef > 0 ? '-' : '+', coef > 0 ? coef : -coef, 'x' + k);
                        }
                    }
                    printf("\n");
                    break;
                }
            }
        }
        for(int j=0;j<sistema->qtdIcog;j++){        // As variáveis sem pivô são livres
            if(!ehPivo[j]){
                printf("\t%c = livre\n", 'x' + j);
            }
        }
    }
}

void lerSistema(){
    Sistema sistema;
    printf("\tQuantas linhas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdLinhas);
    printf("\tQuantas icógnitas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdIcog);
    limparTela();
    getchar();
    escreveTitulo(tituloPrinc, " - LEITURA DE SISTEMA");
    printf("\tEscreva um sistema com %d equações e %d icógnitas:\n", sistema.qtdLinhas, sistema.qtdIcog);
    escreverLinha(divisa);
    for(int i=0;i<sistema.qtdLinhas;i++){
        printf("\t|  ");
        fgets(sistema.equacoes[i], sizeof(sistema.equacoes[i]), stdin);
        sistema.equacoes[i][strcspn(sistema.equacoes[i], "\n")] = '\0';
    }
    limpaEspacos(sistema.equacoes, sistema.qtdLinhas);
    gravaSistema(&sistema);

    parseSistema(&sistema); 
    limparTela();
    escreveTitulo(tituloPrinc, " - LEITURA DE SISTEMA");
    imprimirSistema(&sistema);
    printf("\tSistema gravado no arquivo 'sistemas.txt'.\n\n");
    printf("\tMatriz aumentada do sistema escrito:\n");
    imprimirMatriz(&sistema.matriz);
    escreverLinha(divisa);
    menuSistemas2(&sistema);
}