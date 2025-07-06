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
#define preto "\x1b[30m"
#define vermelho "\x1b[31m"
#define verde "\x1b[32m"
#define amarelo "\x1b[33m"
#define azul "\x1b[34m"
#define magenta "\x1b[35m"
#define ciano "\x1b[36m"
#define branco "\x1b[37m"
