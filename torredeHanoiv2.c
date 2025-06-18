// Função que resolve a Torre de Hanói e mostra os passos numerados

#include <stdio.h>
#include <windows.h>
#include <unistd.h>// Se estiver usando linux, MacOs etc... 
// tirar o referenciador para comentario // da linha 21 e apagar ou comentar o Sleep(2000);

void move(int n, char comeco, char aux, char fim, int *contador_passos) {
    
     
    if (n >= 1 && n <= 8) {
      
        move(n - 1, comeco, fim, aux, contador_passos);

        (*contador_passos)++;  // Incrementa o passo antes de imprimir
        printf("Passo %d: mover o disco -> %d que esta na torre -> %c para a torre -> %c\n\n",
               *contador_passos, n, comeco, fim);
        
               Sleep(500);
               //sleep(0.5);

        move(n - 1, aux, comeco, fim, contador_passos);
    }
}

int main() {
    int n;
    int contador_passos = 0;

    do {
        printf("Escreva o numero de discos (1 a 8): ");
        scanf("%d", &n);

        if (n < 1 || n > 8) {
            printf("Numero invalido. Tente novamente.\n");
        }
    } while (n < 1 || n > 8);


    move(n, 'A', 'B', 'C', &contador_passos);

    printf("Total de movimentos: %d\n", contador_passos);

    return 0;
}
