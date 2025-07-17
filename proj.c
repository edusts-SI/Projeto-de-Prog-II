#include <stdio.h> // Nossa biblioteca padrâo
#include <stdlib.h> // Biblioteca para utilização do system (cls) para limpar a tela para melhor vizualização no terminal.
#include <ctype.h> // Manipulação de caratcteres.
#include <stdbool.h>

#define TAM 8

//cores
#define RESET "\033[0m"
#define preto "\x1b[30m"
#define vermelho "\x1b[31m"
#define verde "\x1b[32m"
#define amarelo "\x1b[33m"
#define azul "\x1b[34m"
#define magenta "\x1b[35m"
#define ciano "\x1b[36m"
#define branco "\x1b[37m"

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = ' ';
        } }
    //pretas = O
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 1)
                tabuleiro[i][j] = 'O';
            }}
    //brancas = o
        for (int i = 5; i < 8; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 1)
                tabuleiro[i][j] = 'o'; }}}

void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("    A   B   C   D   E   F   G   H\n");
    for (int i = 0; i < TAM; i++) {
        printf("  +---+---+---+---+---+---+---+---+\n");
        printf("%d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf("| ");
            char peca = tabuleiro[i][j];
            if (peca == 'O') {
                printf(vermelho "O" RESET);
            } else if (peca == 'o') {
            
                printf(branco "o" RESET);
            } else {
                printf(" ");
            }
            printf(" ");
        }
        printf("|\n");
    }
    printf("  +---+---+---+---+---+---+---+---+\n");
}

void menu(){
    printf(ciano"\n\n\t==================\n"RESET);
    printf(magenta"\t   JOGO DE DAMAS"RESET);
    printf(ciano"\n\t==================\n"RESET);

    printf("\n\t 1 - Novo Jogo");
    printf("\n\t 2 - Carregar Jogo");
    printf("\n\t 0 - Sair do Jogo");

    printf(ciano"\n\n\t===================\n"RESET);
    printf("\n\t Insira uma opcao: ");
}

int selecionaJogador(){
    int escolha;
    do{
        printf(ciano"\n\n\t==================\n"RESET);
        printf(ciano"\tEscolha suas pecas"RESET);
        printf(ciano"\n\t==================\n"RESET);

        printf("\n\t 1 - Brancas(o)");
        printf("\n\t 2 - Pretas(O)");
        printf(ciano"\n\n\t==================\n"RESET);
        printf("\n\t Insira uma opcao: ");
        scanf("%d",&escolha);

        if (escolha==1 || escolha==2){
            return escolha;
        }

    }
        while(1);
}

void clean(){
    system("cls");
}

--
void status(char tabuleiro[TAM][TAM], int jogadorAtual){
    int pBrancas = 0;
    int pPretas = 0;
    
    printf(amarelo"\n\n\t==================\n"RESET);
    printf(azul"\t  STATUS DO JOGO\t"RESET);
    printf(amarelo"\n\t==================\n"RESET);
    
    printf("\nVez do jogador: %d ", jogadorAtual);
    
    if (jogadorAtual == 1) {
        printf("Branca: o");
    }
    else {
        printf("Preta: O");
    }
    
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char peca = tabuleiro[i][j];
            
            if (peca == 'o') {
                pBrancas += 1;
            }
            if (peca == 'O') {
                pPretas += 1;
            }
        }
    }        
    printf("\nPecas Brancas: %d", pBrancas);
    printf("\nPecas pretas: %d\n", pPretas);
    
    printf(amarelo"\n\t==================\n"RESET);
}

bool converterCoordenadas(char col, int linha, int *x, int *y) {
    *x = linha - 1;
    *y = toupper(col) - 'A';

    if (*x < 0 || *x >= TAM || *y < 0 || *y >= TAM) {
        return false;
    }
    return true;
}
--
bool validarMovimento(char tabuleiro[TAM][TAM], int xOrigem, int yOrigem, int xDestino, int yDestino, int jogador, int *captura) {
    char peca = tabuleiro[xOrigem][yOrigem];
    
    if ((jogador == 1 && peca != 'o') || (jogador == 2 && peca != 'O'))
        return false;
        
    char pecaAdversario = peca;
    
    if (jogador == 1) {
        pecaAdversario = 'O';
    } else {
        pecaAdversario = 'o';
    }
        
    int xMeio = (xOrigem + xDestino) / 2;
    int yMeio = (yOrigem + yDestino) / 2;
    
    if (xDestino < 0 || xDestino >= TAM || yDestino < 0 || yDestino >= TAM) 
        return false;
    if (tabuleiro[xDestino][yDestino] != ' ')
        return false;
        
    if (abs(xDestino - xOrigem) == 1 && abs(yDestino - yOrigem) == 1) {
        if (captura) *captura = 0;
            if (peca == 'o' && xDestino < xOrigem)
                return true;
            if (peca == 'O' && xDestino > xOrigem)
                return true;
        return false;
    }
    if (abs(xDestino - xOrigem) == 2 && abs(yDestino - yOrigem) == 2) {
        char pMeio = tabuleiro[xMeio][yMeio];
        
        if (pecaAdversario != pMeio)
            return false;
        if (captura) *captura = 1;
            return true;
    }  
    return false;
}
--
int verificarCaptura(char tabuleiro[TAM][TAM], int jogadorAtual) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char peca = tabuleiro[i][j];
            if (peca == ' ') {
                continue;
            }
            if (!((jogadorAtual == 1 && (peca == 'o')) || (jogadorAtual == 2 && peca == 'O'))) {
                continue;
            } 
            int xDestino, yDestino;
            
            char dDiagonais[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
            
            for (int l = 0; l < 4; l++) {
                int lPassos = dDiagonais[l][0];
                int cPassos = dDiagonais[l][1];
                
                xDestino = i + 2 * lPassos;
                yDestino = j + 2 * cPassos;
                    
                int capturada = 0;
            
                if (validarMovimento(tabuleiro, i, j, xDestino, yDestino, jogadorAtual, &capturada) && capturada) {
                    return 1;
                }
                if (peca == 'O' || peca == 'o') {
                    break;
                }
                if (tabuleiro[xDestino][yDestino] != ' ') {
                    break;    
                }
                   
            }  
        }   
    } 
    return 0;
}    
--
void jogarPartida() {
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    int jogadorEscolhido = selecionaJogador();
    int jogadorAtual = jogadorEscolhido;

    while (true) {
        clean();
        imprimirTabuleiro(tabuleiro);
        status(tabuleiro, jogadorAtual);
        
        int pecaCapturar = verificarCaptura(tabuleiro, jogadorAtual);
        
        if (pecaCapturar) {
            printf("Captura obrigatoria");
        }
        
        printf("\nJogador %d (%s), faca seu movimento (ex: A3B4): ",
        jogadorAtual, jogadorAtual == 1 ? "brancas" : "pretas");

        char colOrigem, colDestino;
        int linhaOrigem, linhaDestino;
        int xOrigem, yOrigem, xDestino, yDestino;
              
        scanf(" %c%d %c%d", &colOrigem, &linhaOrigem, &colDestino, &linhaDestino);

        if (!converterCoordenadas(colOrigem, linhaOrigem, &xOrigem, &yOrigem)) {
            printf("Coordenada de origem inválida!\n");
                continue;
        }
        if (!converterCoordenadas(colDestino, linhaDestino, &xDestino, &yDestino)) {
            printf("Coordenada de destino inválida.\n");
                continue;
        }
        int xMeio = (xOrigem + xDestino) / 2;
        int yMeio = (yOrigem + yDestino) / 2;
        
        int captura = 0; 
        
        if (validarMovimento(tabuleiro, xOrigem, yOrigem, xDestino, yDestino, jogadorAtual, &captura)) {
              if (pecaCapturar && !captura) {
                  printf("Movimento inválido. Tente novamente.\n");
                  continue;
              }
              tabuleiro[xDestino][yDestino] = tabuleiro[xOrigem][yOrigem];
              tabuleiro[xOrigem][yOrigem] = ' ';

              if (captura == 1)
                   tabuleiro[xMeio][yMeio] = ' ';
                   
              jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        } else {
            printf("Movimento inválido. Tente novamente.\n");
        }
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                clean();
                jogarPartida();
                break;

            case 2:
                break;

            case 0:
                printf("Saindo do jogo\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while(opcao != 0);

    return 0;
}
