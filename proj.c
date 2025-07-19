#include <stdio.h> // Nossa biblioteca padrâo
#include <stdlib.h> // Biblioteca para utilização do system (cls) para limpar a tela para melhor vizualização no terminal.
#include <ctype.h> // Manipulação de caratcteres.
#include <stdbool.h>
#include <string.h> // Biblioteca para manipulação de strings

#define TAM 8
#define NOME_ARQUIVO "damas_save.txt" // define logo de cara o nome do nosso arquivo para save e carregamento

//cores
#define RESET "\033[0m"
#define vermelho "\x1b[31m"
#define verde "\x1b[32m"
#define amarelo "\x1b[33m"
#define azul "\x1b[34m"
#define magenta "\x1b[35m"
#define ciano "\x1b[36m"
#define branco "\x1b[37m"

                                                 /* Interface do jogo */

//Procedimento que inicializa o tabuleiro com as "casas vazio", insere as peças pretas e brancas usando a logica matricial começando com
//  as linhas e depois com as colunas utilizando a logica de ímpar ou par para as peças só ficarem nos espaços "marrons".

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
    //pretas = O
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 1)
                tabuleiro[i][j] = 'O';
        }
    }
    //brancas = o
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 1)
                tabuleiro[i][j] = 'o';
        }
    }
}

                                                /* Procedimento que imprime o tabuleiro */

void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("      A   B   C   D   E   F   G   H\n");
    for (int i = 0; i < TAM; i++) {
        printf("    +---+---+---+---+---+---+---+---+\n");
        printf("  %d |", i + 1);
        for (int j = 0; j < TAM; j++) {
        char peca = tabuleiro[i][j];
           if (peca == 'O') {
   			 printf(vermelho " O " RESET);
			} else if (peca == 'o') {
   				printf(branco " o " RESET);
			} else if (peca == '@') {
    			printf(vermelho " @ " RESET); // Dama preta
			} else if (peca == '0') {
    			printf(branco " 0 " RESET);   // Dama branca
			} else {
    			printf("   ");
			}
            printf("|");
        }
        printf("\n");
    }
    printf("    +---+---+---+---+---+---+---+---+\n");
}

                                                     /* Printa o Menu do jogo */

void menu() {
    printf(ciano "\n\n\t==================\n" RESET);
    printf(magenta "\t  JOGO DE DAMAS" RESET);
    printf(ciano "\n\t==================\n" RESET);
    printf("\n\t 1 - Novo Jogo");
    printf("\n\t 2 - Carregar Jogo");
    printf("\n\t 0 - Sair do Jogo");
    printf(ciano "\n\n\t===================\n" RESET);
    printf("\n\t Insira uma opcao: ");
}

                            /*Função que seleciona entre peças pretas ou brancas como também quem ira iniciar*/

int selecionaJogador() {
    int escolha;
    do {
        printf(ciano "\n\n\t==================\n" RESET);
        printf(ciano "\tEscolha suas pecas" RESET);
        printf(ciano "\n\t==================\n" RESET);
        printf("\n\t 1 - Brancas(o)");
        printf("\n\t 2 - Pretas(O)");
        printf(ciano "\n\n\t==================\n" RESET);
        printf("\n\t Insira uma opcao: ");
        scanf("%d", &escolha);
        if (escolha == 1 || escolha == 2) {
            return escolha;
        }
    } while (1);
}

                                                /*Procedimento que limpa a tela de execução*/
//Lê e identifica o sistema operacional para que seja versatil dentre os SO

void clean() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

                                        /*Procedimento o qual exibe o status do jogo*/
//indica qual jogador da vez e diz quantas peças cada jogador ainda tem.

void status(char tabuleiro[TAM][TAM], int jogadorAtual) {
    int pBrancas = 0;
    int pPretas = 0;
    printf(amarelo "\n\n\t==================\n" RESET);
    printf(azul "\t  STATUS DO JOGO\t" RESET);
    printf(amarelo "\n\t==================\n" RESET);
    printf("\nVez do jogador: " verde "%d " RESET "-> ", jogadorAtual);
    if (jogadorAtual == 1) {
        printf("Brancas: " branco "o" RESET);
    } else {
        printf("Pretas: " vermelho "O" RESET);
    }
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char peca = tabuleiro[i][j];
            if (peca == 'o' || peca == '0') {
                pBrancas++;
            }
            if (peca == 'O' || peca == '@') {
                pPretas++;
            }
        }
    }
    printf("\nPecas Brancas: %d", pBrancas);
    printf("\nPecas Pretas: %d\n", pPretas);
    printf(amarelo "\n\t==================\n" RESET);
}

                                        /*Função que converte coordenadas matriciais para coordenadas de melhor compreensão*/

// meio que traduz as coodenadas da matriz para uma linguagem de maior entendimento como:
//(a6b5) lê como: casa na "coluna (a) na linha (6) para casa da coluna (b) na linha (5)" 

bool converterCoordenadas(char col, int linha, int *x, int *y) {
    *x = linha - 1;
    *y = toupper(col) - 'A';
    if (*x < 0 || *x >= TAM || *y < 0 || *y >= TAM) {
        return false;
    }
    return true;
}

                                        /*Funções que dão os movimentos diagonais de ambas as peças*/

//limita as peças de se moverem na horizontal ou vertical permitindo somente movimentos diagonais. 

bool validarMovimento(char tabuleiro[TAM][TAM], int xOrigem, int yOrigem, int xDestino, int yDestino, int jogador, int *captura) {
    if (xOrigem < 0 || xDestino < 0 || xDestino >= TAM || yDestino < 0 || yDestino >= TAM)
        return false;
    if (tabuleiro[xDestino][yDestino] != ' ')
        return false;
    char peca = tabuleiro[xOrigem][yOrigem];
    if ((jogador == 1 && (peca != 'o' && peca != '0')) || (jogador == 2 && (peca != 'O' && peca != '@')))
        return false;
    
    int dx = abs(xDestino - xOrigem);
    int dy = abs(yDestino - yOrigem);
    
    // Movimento para peças normais
    if (peca == 'o' || peca == 'O') {
        if (dx == 1 && dy == 1) {
            *captura = 0;
            if ((peca == 'o' && xDestino > xOrigem) || (peca == 'O' && xDestino < xOrigem)) return false;
            return true;
        }
        if (dx == 2 && dy == 2) {
            int xMeio = (xOrigem + xDestino) / 2;
            int yMeio = (yOrigem + yDestino) / 2;
            char pecaDoMeio = tabuleiro[xMeio][yMeio];
            char pecaAdversaria = (jogador == 1) ? 'O' : 'o';
            char damaAdversaria = (jogador == 1) ? '@' : '0';
            if (pecaDoMeio == pecaAdversaria || pecaDoMeio == damaAdversaria) {
                *captura = 1;
                return true;
            }
        }
        return false;
    }
    // Movimento para damas
    else {
        if (dx != dy) return false; // Dama deve mover na diagonal
        
        int passos = dx;
        int dirX = (xDestino > xOrigem) ? 1 : -1;
        int dirY = (yDestino > yOrigem) ? 1 : -1;
        int pecasNoCaminho = 0;
        int x = xOrigem + dirX;
        int y = yOrigem + dirY;
        
        // Verifica o caminho
        for (int i = 1; i < passos; i++) {
            if (tabuleiro[x][y] != ' ') {
                pecasNoCaminho++;
                if (pecasNoCaminho > 1) return false; // Só pode pular uma peça
                
                char pecaNoCaminho = tabuleiro[x][y];
                char pecaAdversaria = (jogador == 1) ? 'O' : 'o';
                char damaAdversaria = (jogador == 1) ? '@' : '0';
                
                if (pecaNoCaminho != pecaAdversaria && pecaNoCaminho != damaAdversaria)
                    return false; // Só pode pular peça adversária
            }
            x += dirX;
            y += dirY;
        }
        
        *captura = pecasNoCaminho;
        return true;
    }
}

                                 /*Função que verifica se é possivel a captura */
// se houver possivel captura ela retorna 1  


int verificarCaptura(char tabuleiro[TAM][TAM], int jogadorAtual) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char peca = tabuleiro[i][j];

            // Verifica se a peça pertence ao jogador atual
            if ((jogadorAtual == 1 && (peca == 'o' || peca == '0')) ||
                (jogadorAtual == 2 && (peca == 'O' || peca == '@'))) {

                // Testa todas as 4 direções diagonais
                int dirX[] = {-1, -1, 1, 1};
                int dirY[] = {-1, 1, -1, 1};

                for (int k = 0; k < 4; k++) {
                    // Testa pulos de diferentes distâncias
                    for (int passos = 2; passos < TAM; passos++) {
                        int xDestino = i + passos * dirX[k];
                        int yDestino = j + passos * dirY[k];
                        int capturaPossivel = 0;

                        if (validarMovimento(tabuleiro, i, j, xDestino, yDestino, jogadorAtual, &capturaPossivel)) {
                            if (capturaPossivel) {
                                return 1; // Encontrou uma captura obrigatória!
                            }
                        }
                    }
                }
            }
        }
    }
    return 0; // Nenhuma captura encontrada
}

                                 /*Função que verifica em redor da peça se existe possivel captura*/

bool podeCapturarDe(char tabuleiro[TAM][TAM], int x, int y, int jogador) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM || tabuleiro[x][y] == ' ') {
        return false;
    }

    // Testa todas as 4 direções diagonais
    int dirX[] = {-1, -1, 1, 1};
    int dirY[] = {-1, 1, -1, 1};

    for (int k = 0; k < 4; k++) {
        // Testa pulos de diferentes distâncias
        for (int passos = 2; passos < TAM; passos++) {
            int xDestino = x + passos * dirX[k];
            int yDestino = y + passos * dirY[k];
            int capturaPossivel = 0;

            if (validarMovimento(tabuleiro, x, y, xDestino, yDestino, jogador, &capturaPossivel)) {
                if (capturaPossivel) {
                    return true; // Encontrou uma captura possível para esta peça!
                }
            }
        }
    }

    return false; // Nenhuma captura encontrada para esta peça.
}

                                 /*Procedimento que executa o salvamento do jogador atual em um arquivo */

// o procedimento abre o arquivo, verifica se a existencia do mesmo, logo em seguida ele percorre o tabuleiro por linha e coluna,
//  copiando cada caracterie ali presente e colando no arquivo. O 'fputc' fucionará como um enter pulando para a próxima linha no arquivo.


void salvarJogo(char tabuleiro[TAM][TAM], int jogadorAtual) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf(vermelho "ERRO: Nao foi possivel salvar o jogo!\n" RESET);
        return;
    }
    fprintf(arquivo, "%d\n", jogadorAtual);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            fputc(tabuleiro[i][j], arquivo);
        }
        fputc('\n', arquivo);
    }
    fclose(arquivo);
    printf(verde "\nJogo salvo com sucesso!\n" RESET);
    system("pause");
}

                                             /*Função que abre o arquivo e lê o mesmo*/

//abre o arquivo verifica se a jogo salvo, lê a primeira linha do arquivo, que contém apenas um número e armazena na variavel jogadorAtual.
// basicamente funciona como o inverso da função salvarJogo. 


bool carregarJogo(char tabuleiro[TAM][TAM], int *jogadorAtual) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf(vermelho "Nenhum jogo salvo encontrado.\n" RESET);
        system("pause");
        return false;
    }
    fscanf(arquivo, "%d", jogadorAtual);
    fgetc(arquivo);

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = fgetc(arquivo);
        }
        fgetc(arquivo);
    }
    fclose(arquivo);
    printf(verde "Jogo carregado com sucesso!\n" RESET);
    system("pause");
    return true;
}


                                /*Função Fim*/

// verifica qual jogador perdeu todas as peças assim determinando o vencedor e o fim do jogo

int fimDeJogo(char tabuleiro[TAM][TAM]) {
    int pBrancas = 0;
    int pPretas = 0;
    
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char peca = tabuleiro[i][j];
            if (peca == 'o' || peca == '0') {
                pBrancas++;
            }
            if (peca == 'O' || peca == '@') {
                pPretas++;
            }
        }
    }
    if (pPretas == 0) {
        return 1;
    }
    if (pBrancas == 0) {
        return 2;
    }    
    return 0;     
 }
    
                                 /*Procedimento onde contém o loop e irá estar chamando todas as outras funções e procedimentos e inicializa o jogo */

//é o motor que executa o jogo em um ciclo contínuo, cuidando de mostrar o tabuleiro, receber e validar jogadas, 
//aplicar todas as regras (incluindo as mais complexas como captura múltipla) e alternar os jogadores até que a partida seja salva.

void jogarPartida(char tabuleiro[TAM][TAM], int jogadorAtual) {
    while (true) {
        clean();
        imprimirTabuleiro(tabuleiro);
        status(tabuleiro, jogadorAtual);
        int capturaObrigatoria = verificarCaptura(tabuleiro, jogadorAtual);
        if (capturaObrigatoria) {
            printf(amarelo "\n!!! CAPTURA OBRIGATORIA !!!\n" RESET);
        }
        printf("\nJogador -> " verde "%d " RESET "faca seu movimento (ex: C6B5 ou digite 'salvar'): ", jogadorAtual);
        char entrada[20];
        scanf("%s", entrada);
        if (strcmp(entrada, "salvar") == 0) {
            salvarJogo(tabuleiro, jogadorAtual);
            return;
        }
        char colOrigem, colDestino;
        int linhaOrigem, linhaDestino;
        if (sscanf(entrada, "%c%d%c%d", &colOrigem, &linhaOrigem, &colDestino, &linhaDestino) != 4) {
             printf(vermelho "Entrada invalida! Tente novamente.\n" RESET);
             system("pause");
             continue;
        }
        int xOrigem, yOrigem, xDestino, yDestino;
        if (!converterCoordenadas(colOrigem, linhaOrigem, &xOrigem, &yOrigem) || 
            !converterCoordenadas(colDestino, linhaDestino, &xDestino, &yDestino)) {
            printf(vermelho "Coordenadas invalidas! Tente novamente.\n" RESET);
            system("pause");
            continue;
        }
        int capturaRealizada = 0;
        if (validarMovimento(tabuleiro, xOrigem, yOrigem, xDestino, yDestino, jogadorAtual, &capturaRealizada)) {
            if (capturaObrigatoria && !capturaRealizada) {
                printf(vermelho "Movimento invalido. Voce deve realizar a captura!\n" RESET);
                system("pause");
                continue;
            }
            // Primeiro verifica qual é a peça que está sendo movida
            char pecaMovida = tabuleiro[xOrigem][yOrigem];
            // Move a peça para o destino
            tabuleiro[xDestino][yDestino] = pecaMovida;
            tabuleiro[xOrigem][yOrigem] = ' ';
            
            // Verifica promoção para dama
            if (pecaMovida == 'o' && xDestino == 0) {
                tabuleiro[xDestino][yDestino] = '0'; // Dama branca
            } else if (pecaMovida == 'O' && xDestino == 7) {
                tabuleiro[xDestino][yDestino] = '@'; // Dama preta
            }

            if (capturaRealizada) {
                int dirX = (xDestino > xOrigem) ? 1 : -1;
                int dirY = (yDestino > yOrigem) ? 1 : -1;
                int x = xOrigem + dirX;
                int y = yOrigem + dirY;
                
                while (x != xDestino && y != yDestino) {
                    if (tabuleiro[x][y] != ' ') {
                        tabuleiro[x][y] = ' '; // Remove a peça capturada
                        break;
                    }
                    x += dirX;
                    y += dirY;
                }
                
                if (podeCapturarDe(tabuleiro, xDestino, yDestino, jogadorAtual)) {
                    printf(verde "\nCAPTURA MULTIPLA! Continue jogando com a mesma peca.\n" RESET);
                    system("pause");
                    continue;
                }
            }

            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;

        } else {
            printf(vermelho "Movimento invalido. Tente novamente.\n" RESET);
            system("pause");
        }
        int jogadorVencedor = fimDeJogo(tabuleiro);
        
        if (jogadorVencedor != 0) {
            printf(verde"\nFIM DE JOGO! VENCEDOR: Jogador %d\n" RESET, jogadorVencedor);
            system("pause");
            break;
        }    
    }
}


                                /*Nossa Main*/

//que usa um switch case dentro de um do while para chamada de todo o jogo 

int main() {
    int opcao;
    char tabuleiro[TAM][TAM];
    int jogadorAtual;
    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            clean();
            inicializarTabuleiro(tabuleiro);
            jogadorAtual = selecionaJogador();
            jogarPartida(tabuleiro, jogadorAtual);
            break;
        case 2:
            clean();
            if (carregarJogo(tabuleiro, &jogadorAtual)) {
                jogarPartida(tabuleiro, jogadorAtual);
            }
            break;
        case 0:
            printf("Saindo do jogo. Ate a proxima!\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != 0);
    return 0;
}
