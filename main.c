#ifdef _WIN32
#include <windows.h>
SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
#endif
#include <stdio.h>
#include "include/menu.h"
#include "include/util.h"

char titulo[98] = "SISTEMA ALGEBRA LINEAR";

int main(){
    limparTela();
    escreveTitulo(titulo, ""); 
    escreverMenu1();
    menuInicial();
    return 0;
}