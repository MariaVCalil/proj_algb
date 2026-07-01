#include "include/arquivos.h"
#include "include/sistemas.h"
#include "include/util.h"

void gravaSistema(Sistema *sistema){
    FILE *arq = fopen("sistemas.txt", "a");

    fprintf(arq, "%d equações, %d icógnitas. \n", sistema->qtdLinhas, sistema->qtdIcog);
    for(int i = 0; i < sistema->qtdLinhas; i++){
        fprintf(arq, "%s\n", sistema->equacoes[i]);
    }
    fprintf(arq, "\n");
    escreverLinhaArq(arq);
    fclose(arq);
}