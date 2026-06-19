#include <stdio.h>
#include <strings.h>
#include "include/sistemas.h"
#include "include/matrizes.h"

void lerSistema(){
    Sistema sistema;
    printf("    Quantas linhas tem o sistema?\n -> ");
    scanf("%d", &sistema.qtdLinhas);
    printf("    Quantas icógnitas tem o sistema?\n  -> ");
    scanf("%d", &sistema.qtdIcog);
    for(int i=0;i<sistema.qtdLinhas;i++){
        for (int j=0;j<=sistema.qtdIcog;j++){
            scanf("%[^ ]s", &sistema.*matriz.valores)
        }
    }
}   