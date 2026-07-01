#include "include/util.h"

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void escreveLinhaArq(FILE *arq){
    for(int i=0;i<larguraLinha;i++){
        fprintf(arq, "\u2558");
        for (int i=0; i < larguraLinha; i++){
            fprintf(arq, "\u2550");                        // ═                    
        }
        fprintf(arq, "\u255B\n");
    }
}

void limpaEspacos(char str[][100], int N){
    for (int i = 0; i < N; i++){
        int j = 0;
        for (int k = 0; str[i][k] != '\0'; k++){
            if (str[i][k] != ' '){
                str[i][j] = str[i][k];
                j++;
            }
        }
        str[i][j] = '\0';
    }
}