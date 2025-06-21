
Nome do Projeto: DamasMaster C
1. Objetivo Principal
Desenvolver um jogo de damas para dois jogadores, totalmente funcional, implementado na linguagem C. O projeto focará na aplicação de conceitos fundamentais da programação como o uso de ponteiros para manipulação de dados, recursividade para lógicas complexas de captura e a utilização de arquivos para salvar e carregar o progresso do jogo. A interface do jogo será construída no console, utilizando a biblioteca gconio para uma melhor experiência visual.

2. Funcionalidades Planejadas
O jogo contará com as seguintes características:

Tabuleiro Visual e Interativo:

Um tabuleiro de 8x8 será desenhado no console.
A biblioteca gconio será utilizada para dar cor às casas do tabuleiro, diferenciar as peças dos dois jogadores (ex: peças brancas e pretas) e destacar a peça selecionada ou movimentos possíveis.
O jogador irá interagir com o jogo informando as coordenadas da peça que deseja mover e para onde deseja movê-la.
Lógica de Jogo Completa:

Movimentação de Peças: Implementação da movimentação diagonal simples para as peças comuns.
Captura de Peças: Uma peça pode "comer" a peça adversária saltando sobre ela para uma casa vazia. A captura será obrigatória, conforme as regras do jogo.
Captura Múltipla (Recursiva): Se, após uma captura, a mesma peça tiver a oportunidade de capturar outra peça adversária, ela deverá fazê-lo no mesmo turno. Esta lógica será implementada de forma recursiva.
Promoção a "Dama" (Rei): Quando uma peça alcança a extremidade oposta do tabuleiro, ela é promovida a "Dama", ganhando a habilidade de se mover para frente e para trás nas diagonais.
Validação de Jogadas: O sistema irá verificar se cada movimento solicitado pelo jogador é válido de acordo com as regras do jogo.
Gerenciamento do Estado do Jogo:

Uso de Ponteiros: O tabuleiro e suas peças serão representados por uma matriz. A manipulação do estado do tabuleiro, como mover e remover peças, será realizada eficientemente através do uso de ponteiros.
Detecção de Fim de Jogo: O jogo terminará quando um dos jogadores ficar sem peças ou sem movimentos possíveis. O programa deverá anunciar o vencedor.
Persistência de Dados (Arquivos):

Salvar Jogo: A qualquer momento, os jogadores poderão escolher salvar o estado atual da partida. As posições de todas as peças e a vez do jogador serão gravadas em um arquivo.
Carregar Jogo: Será possível carregar uma partida salva anteriormente para continuar de onde parou.



