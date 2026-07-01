#include "include/util.h"

void limparTela(){
    system("cls");
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