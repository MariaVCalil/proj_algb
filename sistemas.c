#include <stdio.h>
#include <string.h>
#include "include/sistemas.h"
#include "include/matrizes.h"

void lerSistema(){
    Sistema sistema;
    printf("    Quantas linhas tem o sistema?\n -> ");
    scanf("%d", &sistema.qtdLinhas);
    printf("    Quantas icógnitas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdIcog);
    for(int i=0;i<sistema.qtdLinhas;i++){
        scanf("%s[^\n]", sistema.equacoes[i]);
    }
}   