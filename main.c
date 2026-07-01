#include <stdio.h>
#include <windows.h>
#include "include/menu.h"
#include "include/util.h"

char titulo[98] = "SISTEMA ALGEBRA LINEAR";

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    limparTela();
    escreveTitulo(titulo, ""); 
    escreverMenu1();
    menuInicial();
    
    return 0;
}