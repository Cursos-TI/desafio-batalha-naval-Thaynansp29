#include <stdio.h>

int main() {
    
    //  Inicialização do tabuleiro
    
    int tabuleiro[10][10];
    int overlayHabilidade[10][10]; // marcas temporárias das habilidades (1 = afetado)

    // Inicializa tabuleiro com água (0) e overlay com 0
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
            overlayHabilidade[i][j] = 0;
        }
    }

    
    //Posicionamento de navios (exemplo)
    
    int tamanhoNavio = 3;

    // Navio 1: vertical em (1,2) -> (1,2),(2,2),(3,2)
    for (int k = 0; k < tamanhoNavio; k++) tabuleiro[1 + k][2] = 3;

    // Navio 2: horizontal em (5,4) -> (5,4),(5,5),(5,6)
    for (int k = 0; k < tamanhoNavio; k++) tabuleiro[5][4 + k] = 3;

    // Navio 3: diagonal  começando em (0,3) -> (0,3),(1,4),(2,5)
    for (int k = 0; k < tamanhoNavio; k++) tabuleiro[0 + k][3 + k] = 3;

    // Navio 4: diagonal  começando em (9,2) -> (9,2),(8,3),(7,4)
    for (int k = 0; k < tamanhoNavio; k++) tabuleiro[9 - k][2 + k] = 3;

    
    //Construção dinâmica das matrizes de habilidade (5x5)
    
    const int S = 5;                // tamanho das matrizes de habilidade 
    int centro = S / 2;             // índice central (2 para S=5)
    int cone[S][S];
    int cruz[S][S];
    int octaedro[S][S];

    // Inicializa todas com 0
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            cone[i][j] = 0;
            cruz[i][j] = 0;
            octaedro[i][j] = 0;
        }
    }

    // --- Matriz Cone (aponta para baixo)
    // para cada linha i, a largura do cone cresce até o centro:
    for (int i = 0; i < S; i++) {
        int spread = (i <= centro) ? i : centro;
        for (int j = 0; j < S; j++) {
            if (j >= (centro - spread) && j <= (centro + spread)) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    //  Matriz Cruz
    // marca a linha central e a coluna central
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (i == centro || j == centro) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    //  Matriz Octaedro 
    // lógica: usa distância de Manhattan para formar um losango:
    // marcar se abs(i-centro) + abs(j-centro) <= centro
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            int manhattan = (i > centro ? i - centro : centro - i) + (j > centro ? j - centro : centro - j);
            if (manhattan <= centro) octaedro[i][j] = 1;
            else octaedro[i][j] = 0;
        }
    }

    //  Pontos de origem (no tabuleiro) para cada habilidade

    int origemConeLinha = 2, origemConeColuna = 7;    // exemplo
    int origemCruzLinha = 7, origemCruzColuna = 1;    // exemplo
    int origemOctLinha  = 4, origemOctColuna  = 4;    // exemplo

    
    //  Função lógica de sobreposição: aplicar matriz de habilidade ao overlay
    //    Centra a matriz SxS na origem (origem corresponde ao centro da matriz)
    
    // Aplicar Cone
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (cone[i][j] == 1) {
                int r = origemConeLinha + (i - centro);
                int c = origemConeColuna + (j - centro);
                // valida limites do tabuleiro
                if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                    overlayHabilidade[r][c] = 1;
                }
            }
        }
    }

    // Aplicar Cruz
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (cruz[i][j] == 1) {
                int r = origemCruzLinha + (i - centro);
                int c = origemCruzColuna + (j - centro);
                if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                    overlayHabilidade[r][c] = 1;
                }
            }
        }
    }

    // Aplicar Octaedro
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (octaedro[i][j] == 1) {
                int r = origemOctLinha + (i - centro);
                int c = origemOctColuna + (j - centro);
                if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                    overlayHabilidade[r][c] = 1;
                }
            }
        }
    }

    
    // 6) Impressão do tabuleiro final:
    //    prioridade visual: se há navio (3) -> mostra 3
    //                        else se overlay==1 -> mostra 5
    //                        else mostra 0
    
    printf("\n====== TABULEIRO COM HABILIDADES (0=agua, 3=navio, 5=area) ======\n\n");
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < 10; i++) {
        printf("%d  ", i);
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == 3) {
                // navio tem prioridade visual
                printf("3 ");
            } else if (overlayHabilidade[i][j] == 1) {
                printf("5 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    
    //  imprimir as matrizes internas
    //    Mostra como foram construídas as 3 matrizes de habilidade (5x5)
    // -----------------------------
    printf("\nMatriz Cone (5x5):\n");
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\nMatriz Cruz (5x5):\n");
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\nMatriz Octaedro (5x5):\n");
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    printf("\nOrigem Cone: (%d,%d)\n", origemConeLinha, origemConeColuna);
    printf("Origem Cruz: (%d,%d)\n", origemCruzLinha, origemCruzColuna);
    printf("Origem Oct:  (%d,%d)\n", origemOctLinha, origemOctColuna);

    printf("\nFim da execução.\n");
    return 0;
}