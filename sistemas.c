#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/sistemas.h"
#include "include/matrizes.h"
#include "include/menu.h"
#include "include/util.h"
#include "include/arquivos.h"

char *lerNomeVar(char *p, char *buf);
int indiceVar(char nomes[][8], int nVar, char *nome);
int parseLado(char *ini, char *fim, char nomes[][8], int nVar, double coef[], double *cte, int mult, int eqNum);

int parseSistema(Sistema *s){       // Interpreta as equações em texto e monta a matriz aumentada
    char nomes[10][8];
    int nVar = 0;

    for(int i=0;i<s->qtdLinhas;i++){        // Coleta os nomes de variáveis distintos
        char *p = s->equacoes[i];
        while(*p){
            if(isalpha((unsigned char)*p)){
                char nome[8];
                p = lerNomeVar(p, nome);
                if(indiceVar(nomes, nVar, nome) < 0){       // Nome ainda não visto
                    if(nVar >= 10 || nVar >= s->qtdIcog){
                        printf("\tErro: encontrei mais variáveis do que as %d incógnitas informadas.\n", s->qtdIcog);
                        return 0;
                    }
                    strcpy(nomes[nVar++], nome);
                }
            } else {
                p++;
            }
        }
    }
    if(nVar == 0){
        printf("\tErro: nenhuma variável encontrada nas equações.\n");
        return 0;
    }

    for(int a=0;a<nVar-1;a++){       // Ordena os nomes -> ordem canônica (x, y, z)
        for(int b=a+1;b<nVar;b++){
            if(strcmp(nomes[a], nomes[b]) > 0){
                char tmp[8];
                strcpy(tmp, nomes[a]);
                strcpy(nomes[a], nomes[b]);
                strcpy(nomes[b], tmp);
            }
        }
    }

    Matriz *m = &s->matriz;
    m->linhas = s->qtdLinhas;
    m->colunas = s->qtdIcog + 1;        // Colunas = incógnitas + termo independente
    for(int i=0;i<m->linhas;i++){       // Zera a matriz
        for(int j=0;j<m->colunas;j++){
            m->matriz[i][j] = 0.0;
        }
    }
    for(int v=0;v<nVar;v++){        // Guarda os nomes para a saída futura
        strcpy(m->sistema[v], nomes[v]);
    }

    for(int i=0;i<s->qtdLinhas;i++){        // Monta os coeficientes de cada equação
        char *eq = s->equacoes[i];
        char *ig = strchr(eq, '=');
        if(!ig){
            printf("\tErro na equação %d: falta o sinal '='.\n", i + 1);
            return 0;
        }
        double coef[10] = {0};
        double cte = 0.0;       // Constantes: lado esquerdo (+), lado direito (-)
        if(!parseLado(eq, ig, nomes, nVar, coef, &cte, 1, i)) return 0;
        if(!parseLado(ig + 1, eq + strlen(eq), nomes, nVar, coef, &cte, -1, i)) return 0;
        for(int c=0;c<s->qtdIcog;c++){
            m->matriz[i][c] = coef[c];
        }
        m->matriz[i][s->qtdIcog] = -cte;        // A·x = -cte
    }
    return 1;
}

void lerSistema(){
    Sistema sistema;
    printf("\tQuantas linhas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdLinhas);
    printf("\tQuantas icógnitas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdIcog);
    limparTela();
    getchar();
    escreveTitulo(tituloPrinc, "- LEITURA DE SISTEMA");
    printf("\tEscreva um sistema com %d equações e %d icógnitas:\n", sistema.qtdLinhas, sistema.qtdIcog);
    escreverLinha(divisa);
    for(int i=0;i<sistema.qtdLinhas;i++){
        printf("\t|  ");
        fgets(sistema.equacoes[i], sizeof(sistema.equacoes[i]), stdin);
        sistema.equacoes[i][strcspn(sistema.equacoes[i], "\n")] = '\0';
    }
    gravaSistema(&sistema);
    limpaEspacos(sistema.equacoes, sistema.qtdLinhas);
    gravaSistema(&sistema);

    if(parseSistema(&sistema)){     // Monta e mostra a matriz aumentada
        printf("\n\tMatriz aumentada (variáveis em ordem canônica):\n");
        escreverLinha(divisa);
        imprimirMatriz(&sistema.matriz);
        escreverLinha(divisa);
    } else {
        printf("\n\tNão foi possível interpretar o sistema.\n");
    }
}

char *lerNomeVar(char *p, char *buf){       // Lê um nome de variável (letra seguida de dígitos)
    int n = 0;
    buf[n++] = *p++;
    while(isdigit((unsigned char)*p) && n < 7){
        buf[n++] = *p++;
    }
    buf[n] = '\0';
    return p;
}

int indiceVar(char nomes[][8], int nVar, char *nome){       // Índice do nome no vetor, ou -1
    for(int v=0;v<nVar;v++){
        if(strcmp(nomes[v], nome) == 0) return v;
    }
    return -1;
}

int parseLado(char *ini, char *fim, char nomes[][8], int nVar, double coef[], double *cte, int mult, int eqNum){        // Processa um lado da equação
    char *p = ini;
    while(p < fim){
        int sinal = 1;
        if(*p == '+') p++;
        else if(*p == '-'){ sinal = -1; p++; }
        if(p >= fim) break;

        char *end;
        double valor = strtod(p, &end);
        int temNumero = (end != p);     // Havia coeficiente numérico?
        double c = 1.0;
        if(temNumero){ c = valor; p = end; }

        if(p < fim && isalpha((unsigned char)*p)){      // Termo com variável
            char nome[8];
            p = lerNomeVar(p, nome);
            int idx = indiceVar(nomes, nVar, nome);
            if(idx < 0){
                printf("\tErro na equação %d: variável '%s' não reconhecida.\n", eqNum + 1, nome);
                return 0;
            }
            coef[idx] += mult * sinal * c;
        } else if(temNumero){       // Termo constante
            *cte += mult * sinal * c;
        } else {
            printf("\tErro na equação %d: caractere inesperado '%c'.\n", eqNum + 1, *p);
            return 0;
        }
    }
    return 1;
}