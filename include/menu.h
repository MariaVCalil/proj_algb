#ifndef MENU_H
#define MENU_H

typedef enum {
    topo,
    base,
    div,
} tipoBorda;

void menuInicial();
void escreverMenu1();
void menuSistemas();

void centralizador(int centro);

void limparTela();
void escreverLinha(int tam, int direcaoLinha);
void titulo(char titulo[]);

#endif