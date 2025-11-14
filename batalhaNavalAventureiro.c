#include <stdio.h>

int main() {
    // Tabuleiro 10x10
    int tabuleiro[10][10];

    // Inicializa tabuleiro com água (0)
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            tabuleiro[i][j] = 0;

    int tamanho = 3;

    // NAVIO 1: vertical
    int n1_l = 1, n1_c = 2;
    if (n1_l + tamanho > 10) { printf("ERRO: Navio 1 fora do tabuleiro!\n"); return 1; }
    // posiciona com verificação
    for (int i = 0; i < tamanho; i++) {
        int r = n1_l + i;
        int c = n1_c;
        if (tabuleiro[r][c] == 3) { printf("ERRO: Navio 1 sobreposto!\n"); return 1; }
        tabuleiro[r][c] = 3;
    }

    // NAVIO 2: horizontal 
    int n2_l = 5, n2_c = 4;
    if (n2_c + tamanho > 10) { printf("ERRO: Navio 2 fora do tabuleiro!\n"); return 1; }
    for (int i = 0; i < tamanho; i++) {
        int r = n2_l;
        int c = n2_c + i;
        if (tabuleiro[r][c] == 3) { printf("ERRO: Navio 2 sobreposto!\n"); return 1; }
        tabuleiro[r][c] = 3;
    }

    // NAVIO 3: diagonal 
    int n3_l = 0, n3_c = 3;
    if (n3_l + tamanho > 10 || n3_c + tamanho > 10) { printf("ERRO: Navio 3 fora do tabuleiro!\n"); return 1; }
    for (int i = 0; i < tamanho; i++) {
        int r = n3_l + i;
        int c = n3_c + i;
        if (tabuleiro[r][c] == 3) { printf("ERRO: Navio 3 sobreposto com outro!\n"); return 1; }
        tabuleiro[r][c] = 3;
    }

    // NAVIO 4: diagonal 
    int n4_l = 9, n4_c = 2;
    if (n4_l - (tamanho - 1) < 0 || n4_c + tamanho > 10) { printf("ERRO: Navio 4 fora do tabuleiro!\n"); return 1; }
    for (int i = 0; i < tamanho; i++) {
        int r = n4_l - i;
        int c = n4_c + i;
        if (tabuleiro[r][c] == 3) { printf("ERRO: Navio 4 sobreposto com outro!\n"); return 1; }
        tabuleiro[r][c] = 3;
    }

    // Exibe tabuleiro
    printf("\n   0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < 10; i++) {
        printf("%d  ", i);
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nNavios posicionados com sucesso!\n");
    return 0;
}