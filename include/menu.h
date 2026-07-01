#ifndef MENU_H
#define MENU_H

#define larguraLinha 98

extern char tituloPrinc[larguraLinha];

typedef enum {
    topo,
    base,
    divisa,
} tipoBorda;

void invalida(int n1, int n2);
void encerramento();
void naoImplementado();

void escreveTitulo(char tituloAt[], char subTitulo[]);
void escreverLinha(int tipoBorda);

void menuInicial();
void escreverMenu1();
void menuSistemas();

#endif