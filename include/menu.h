#ifndef MENU_H
#define MENU_H
#include "util.h"

extern char tituloPrinc[larguraLinha];

typedef enum {
    topo,
    base,
    divisa,
} tipoBorda;

void invalida(char n1, char n2);
void encerramento();
void naoImplementado();

void escreveTitulo(char tituloAt[], char subTitulo[]);
void escreverLinha(int tipoBorda);

void menuInicial();
void escreverMenu1();
void menuSistemas();

#endif