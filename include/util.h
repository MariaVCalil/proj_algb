#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define larguraLinha 98

#ifndef UTIL_H
#define UTIL_H

void limparTela();
void limpaEspacos(char str[][100], int N);
void escreverLinhaArq(FILE *arq);

#endif