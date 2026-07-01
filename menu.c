#include <stdio.h>
#include <string.h>
#include "include/menu.h"
#include "include/sistemas.h"
#include "include/util.h"

int opcao = 0;
char tituloPrinc[larguraLinha] = "SISTEMA ALGEBRA LINEAR";

void centralizador(int centro);

void escreverMenu1(){   
    printf("\t[1] Resolver um sistema linear\n");
    printf("\t[2] Verificar transformação linear\n");
    printf("\t[3] Determinar bases\n");
    printf("\t[4] Calcular autovalores e autovetores\n");
    printf("\t[5] Diagonalizar uma matriz\n");
    printf("\t[6] Arquivos\n");
    printf("\t[7] Sair\n");
    escreverLinha(divisa);
}
void menuInicial(){
    do {
        printf("  -> ");
        scanf("%d", &opcao);
        limparTela();
        switch(opcao){
            case 1:
                escreveTitulo(tituloPrinc, " - RESOLUCAO DE SISTEMA LINEAR");
                menuSistemas();
                break;
            case 2:
                escreveTitulo(tituloPrinc, " - VERIFICACAO DE TRANSFORMACAO LINEAR");
                naoImplementado();
                break;
            case 3:
                escreveTitulo(tituloPrinc, " - DETERMINACAO DE BASES");
                naoImplementado();
                break;
            case 4:
                escreveTitulo(tituloPrinc, " - AUTOVALORES E AUTOVETORES");
                naoImplementado();
                break;
            case 5:
                escreveTitulo(tituloPrinc, " - DIAGONALIZACAO");
                naoImplementado();
                break;
            case 6:
                escreveTitulo(tituloPrinc, " - GERENCIAMENTO DE ARQUIVOS");
                naoImplementado();
                break;
            case 7:
                encerramento();
                break;
            default:
                limparTela();
                escreveTitulo(tituloPrinc, "");
                invalida(1, 7);
                escreverMenu1();
                break;
        }
    } while(opcao != 7);
}

void menuSistemas(){
    do {
        printf("\t[1] Escrever sistema linear\n");
        printf("\t[2] Ler sistema linear de arquivo\n");
        printf("\t[3] Voltar\n");
        escreverLinha(divisa);
        printf("  -> ");
        scanf("%d", &opcao);
        limparTela();
        switch((opcao)){
            case 1:
                limparTela();
                escreveTitulo(tituloPrinc, "LEITURA DE SISTEMA");
                lerSistema();
                break;
            case 2:
                limparTela();
                escreveTitulo(tituloPrinc, "LEITURA DE SISTEMA DE ARQUIVO");
                naoImplementado();
                break;
            case 3:
                escreverMenu1();
                break;
            default:
                limparTela();  
                escreveTitulo(tituloPrinc, "LEITURA DE SISTEMA");
                invalida(1, 3);
                break;
        }
    } while(opcao != 3);
}

void naoImplementado(){
    printf("\tFuncionalidade não implementada! Tente outra opção:\n\n");
    printf("\t[1] Tentar novamente\n");
    printf("\t[2] Encerrar\n");
    escreverLinha(divisa);
    printf("  -> ");
    scanf("%d", &opcao);
    limparTela();
    switch(opcao){
        case 1:
            menuInicial();
            break;
        case 2:
            encerramento();
            break;
        default:
            invalida(1, 2);
            break;
    }
}
void encerramento(){
    printf("Até logo!\n");
}
void invalida(int n1, int n2){
    printf("\tOpção inválida! Por favor, escolha uma opção entre %d e %d:\n\n", n1, n2);
}

void escreverLinha(int tipoBorda){      // Função para escrever as bordas do menu
    if(tipoBorda == topo) printf("\u2554");      // ╔
    if(tipoBorda == base) printf("\u255A");      // ╗
    if(tipoBorda == divisa) printf("\u2558");    // ╘
    for (int i=0; i < larguraLinha; i++){
        printf("\u2550");                        // ═                    
    }
    if(tipoBorda == topo) printf("\u2557\n");    // ╚
    if(tipoBorda == base) printf("\u255D\n");    // ╝
    if(tipoBorda == divisa) printf("\u255B\n");  // ╛
}
void escreveTitulo(char tituloAt[], char subTitulo[]){     // Printa o título
    strcat(tituloAt, subTitulo);
    int centro = (larguraLinha - strlen(tituloAt)) / 2;
    escreverLinha(topo);
    printf("\u2551");       // ║ (borda)
    centralizador(centro);
    printf("%s", tituloAt);
    if(strlen(tituloAt)%2 != 0) {     // Corrige com espaço extra caso título seja de tamanho ímpar
        centro++;
    }
    centralizador(centro);
    printf("\u2551\n");     // ║ (borda)
    escreverLinha(base);
    strcpy(tituloAt, "SISTEMA ALGEBRA LINEAR");      // Reseta o título
}

void centralizador(int centro){         // Função para centralizar o texto do título
    for (int i = 0; i < centro; i++){
        printf(" ");
    }
}