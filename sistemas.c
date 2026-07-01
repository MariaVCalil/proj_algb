#include <stdio.h>
#include <string.h>
#include "include/sistemas.h"
#include "include/matrizes.h"
#include "include/menu.h"
#include "include/util.h"
#include "include/arquivos.h"

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
}