#include <stdio.h>
#include <stdlib.h>
#include "include/menu.h"

int opcao;

void limparTela(){
    system("clear"); 
}

void escreverMenu1(){
    printf("=========================== SISTEMA ALGEBRA LINEAR ===========================\n");
    printf("1. Resolver um sistema linear\n");
    printf("2. Verificar transformação linear\n");
    printf("3. Determinar bases\n");
    printf("4. Calcular autovalores e autovetores\n");
    printf("5. Diagonalizar uma matriz\n");
    printf("6. Arquivos\n");
    printf("7. Sair\n\n");
}

void menuInicial(){
    limparTela();
    escreverMenu1();
    scanf("%d", &opcao);
    switch((opcao)){
        case 1:
            printf("Resolvendo sistema linear...\n");
            // Chamar função para resolver sistema linear
            break;
        case 2:
            printf("Verificando transformação linear...\n");
            // Chamar função para verificar transformação linear
            break;
        case 3:
            printf("Determinando bases...\n");
            // Chamar função para determinar bases
            break;
        case 4:
            printf("Calculando autovalores e autovetores...\n");
            // Chamar função para calcular autovalores e autovetores
            break;
        case 5:
            printf("Diagonalizando matriz...\n");
            // Chamar função para diagonalizar uma matriz
            break;
        case 6:
            printf("Gerenciando arquivos...\n");
            // Chamar função para arquivos
            break;
        case 7:
            printf("Até logo...\n");
            break;
        default:
            printf("Opção inválida! Por favor, escolha uma opção entre 1 e 7.\n");
    }
}