#include <stdio.h>
#include <stdlib.h>
#include "include/arquivos.h"
#include "include/sistemas.h"
#include "include/menu.h"

void gravaSistema(Sistema *sistema){
    FILE *arq = fopen("sistemas.txt", "a");

    fprintf(arq, "%d equações, %d icógnitas. \n", sistema->qtdLinhas, sistema->qtdIcog);
    for(int i = 0; i < sistema->qtdLinhas; i++){
        fprintf(arq, "%s\n", sistema->equacoes[i]);
    }
    fprintf(arq, "\n");
    fprintf(arq, "%s", escreverLinhaArq(arq));
    fclose(arq);
}