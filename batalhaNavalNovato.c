#include <stdio.h>



int main() {
     
    // DECLARAÇÃO DO TABULEIRO
    // Matriz 10x10 representando o oceano
    // 0 = água
    // 3 = navio
    int tabuleiro[10][10];

    // Inicializando o tabuleiro com água
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // NAVIOS (vetores unidimensionais)
    int navio1[3] = {3, 3, 3}; // Navio vertical
    int navio2[3] = {3, 3, 3}; // Navio horizontal

    int tamanhoNavio = 3;


    // Navio vertical começando na linha 1, coluna 2
    int linhaInicial1 = 1;
    int colunaInicial1 = 2;

    // Navio horizontal começando na linha 5, coluna 4
    int linhaInicial2 = 5;
    int colunaInicial2 = 4;


    // Verifica se navio vertical cabe no tabuleiro
    if (linhaInicial1 + tamanhoNavio > 10) {
        printf("ERRO: navio vertical sai do tabuleiro!\n");
        return 1;
    }

    // Verifica se navio horizontal cabe no tabuleiro
    if (colunaInicial2 + tamanhoNavio > 10) {
        printf("ERRO: navio horizontal sai do tabuleiro!\n");
        return 1;
    }

    

    // Verifica se navio vertical sobrepõe o horizontal
    for (int i = 0; i < tamanhoNavio; i++) {
        // Vertical ocupa (linhaInicial1 + i, colunaInicial1)
        if (linhaInicial2 == linhaInicial1 + i &&
            (colunaInicial2 <= colunaInicial1 &&
             colunaInicial1 < colunaInicial2 + tamanhoNavio)) {
            
            printf("ERRO: navios sobrepostos!\n");
            return 1;
        }
    }

    // POSICIONAR NAVIO VERTICAL

    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaInicial1 + i][colunaInicial1] = navio1[i];
    }

    // POSICIONAR NAVIO HORIZONTAL

    for (int i = 0; i < tamanhoNavio; i++) {
        tabuleiro[linhaInicial2][colunaInicial2 + i] = navio2[i];
    }

    // EXIBIR O TABULEIRO

    printf("\nTABULEIRO BATALHA NAVAL (0 = água, 3 = navio):\n\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nNavios posicionados com sucesso!\n");

    return 0;
}
