#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/menu.h"

#define larguraLinha 98

int opcao = 0;
char tituloMenuAtual[larguraLinha] = "SISTEMA ALGEBRA LINEAR";

void limparTela(){          // Função para limpar a tela
    system("clear"); 
}

void escreverLinha(int tam, int tipoBorda){      // Função para escrever a linha horizontal usada nas bordas do menu
    if(tipoBorda == topo) printf("\u2554");      // ╔
    if(tipoBorda == base) printf("\u255A");      // ╗
    if(tipoBorda == div) printf("\u2558");       // ╘
    for (int i=0; i < tam; i++){
        printf("\u2550");      // ═                    
    }
    if(tipoBorda == topo) printf("\u2557\n");    // ╚
    if(tipoBorda == base) printf("\u255D\n");    // ╝
    if(tipoBorda == div) printf("\u255B\n");     // ╛
}

void centralizador(int centro){         // Função para centralizar o texto do título
    for (int i = 0; i < centro; i++){
        printf(" ");
    }
}

void titulo(char titulo[]){     // Printa o título
    int centro = (larguraLinha - strlen(titulo)) / 2;
    escreverLinha(larguraLinha, topo);
    printf("\u2551");       // ║ (borda)
    centralizador(centro);
    printf("%s", titulo);
    if(strlen(titulo)%2 != 0) {     // Corrige com espaço extra caso título seja de tamanho ímpar
        centro++;
    }
    centralizador(centro);
    printf("\u2551\n");     // ║ (borda)
    escreverLinha(larguraLinha, base);
}

void escreverMenu1(){
    strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR");
    titulo(tituloMenuAtual);
    printf("   [1] Resolver um sistema linear\n");
    printf("   [2] Verificar transformação linear\n");
    printf("   [3] Determinar bases\n");
    printf("   [4] Calcular autovalores e autovetores\n");
    printf("   [5] Diagonalizar uma matriz\n");
    printf("   [6] Arquivos\n");
    printf("   [7] Sair\n");
    escreverLinha(larguraLinha, div);
}

void menuInicial(){
    do {
        if(opcao < 8) limparTela();
        escreverMenu1();
        scanf("%d", &opcao);
        switch((opcao)){
            case 1:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - RESOLUCAO DE SISTEMA LINEAR");
                titulo(tituloMenuAtual);
                menuSistemas();
                break;
            case 2:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - VERIFICACAO DE TRANSFORMACAO LINEAR");
                titulo(tituloMenuAtual);
                // Chamar função para verificar transformação linear
                break;
            case 3:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - DETERMINACAO DE BASES");
                titulo(tituloMenuAtual);
                // Chamar função para determinar bases
                break;
            case 4:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - AUTOVALORES E AUTOVETORES");
                titulo(tituloMenuAtual);
                // Chamar função para calcular autovalores e autovetores
                break;
            case 5:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - DIAGONALIZACAO");
                titulo(tituloMenuAtual);
                // Chamar função para diagonalizar uma matriz
                break;
            case 6:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - GERENCIAMENTO DE ARQUIVOS");
                titulo(tituloMenuAtual);
                // Chamar função para arquivos
                break;
            case 7:
                limparTela();
                printf("Até logo...\n");
                break;
            default:
                limparTela();
                printf("Opção inválida! Por favor, escolha uma opção entre 1 e 7.\n\n");
        }
    } while(opcao != 7);
}

void menuSistemas(){
    //do{
        printf("[1] Escrever sistema linear\n");
        printf("[2] Ler sistema linear de arquivo\n");
        scanf("%d", &opcao);
        switch((opcao)){
            case 1:
                limparTela();
                strcpy(tituloMenuAtual, "SISTEMA ALGEBRA LINEAR - RESOLUCAO DE SISTEMA LINEAR - ESCRITA DE SISTEMA");
                titulo(tituloMenuAtual);
                lerSistema();
                break;
        } 
    //} while(opcao != );
}