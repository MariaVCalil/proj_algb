#ifndef MENU_H
#define MENU_H

typedef enum {
    topo,
    base,
    divisa,
} tipoBorda;

void limparTela();
void invalida(int n1, int n2);
void encerramento();
void naoImplementado();

void escreveTitulo(char tituloAt[], char subTitulo[]);
void escreverLinha(int tipoBorda);

void menuInicial();
void menuSistemas();


#endif