#include "include/arquivos.h"
#include "include/sistemas.h"
#include "include/util.h"

void gravaSistema(Sistema *sistema){
    FILE *arq = fopen("sistemas.txt", "a");

    fprintf(arq, "\n");
    fprintf(arq, "\t%d equações, %d icógnitas. \n", sistema->qtdLinhas, sistema->qtdIcog);
    for(int i = 0; i < sistema->qtdLinhas; i++){
        fprintf(arq, "\t|  ");
        fprintf(arq, "%s\n", sistema->equacoes[i]);
    }
    escreverLinhaArq(arq);
    fclose(arq);
}