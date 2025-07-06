#include <stdio.h> // Nossa biblioteca padão
#include <stdlib> // Biblioteca para utilização do system (cls) para limpar a tela para melhor visualização no terminal.
#include <string.h> // Utilizaremos para manipular strings.
#include <ctype.h> // Manipulação de Caracteres.
#include <windows.h> // Para melhor controle do console.
#include <conio.h> // Manipulação de cores para melhor visualização.

//Constantes que serão utilizadas ao longo do código

#define TAMANHO 8 // tamanho da matriz (tabuleiro)
//peças
#define VAZIO ' '
#define BRANCA 'b'
#define PRETA 'p'
#define dama_bra 'B'
#define dama_prt 'P'

#define jogador_bra 1
#define jogador_prt 2

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
    //pretas = p
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i + j) % 2 == 1)
                tabuleiro[i][j] = 'O';
            }}
    //brancas = b
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

void clean(){
	
system("cls");}

int main() {
	
	char tabuleiro[TAM][TAM];
	int opcao;
	
	do{
	
	menu();
	
	scanf("%d",&opcao);
	
	switch(opcao){
		
		case 1: 
		clean();
		inicializarTabuleiro(tabuleiro);
		imprimirTabuleiro(tabuleiro);
		
		break;
		
		case 2:
		break;
		
			
		default:
		break;
		
		
}}while(opcao!=0);
	
	
    
    return 0;
}
