#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define CAPACIDADE_FILA 5

// 🧩 Nível Novato: Fila de Peças Futuras

// Struct Peca com tipo (char) e id (int)
typedef struct {
    char tipo;
    int id;
} Peca;

// Struct para a Fila Circular
typedef struct {
    Peca pecas[CAPACIDADE_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaCircular;

// Variável global para controlar o ID sequencial das peças
int proximoId = 1;

// Função para gerar uma peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca novaPeca;
    novaPeca.tipo = tipos[rand() % 7];
    novaPeca.id = proximoId++;
    return novaPeca;
}

// Função para inicializar a fila circular
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(FilaCircular *fila) {
    return fila->tamanho == 0;
}

// Função para verificar se a fila está cheia
int filaCheia(FilaCircular *fila) {
    return fila->tamanho == CAPACIDADE_FILA;
}

// Função para inserir uma peça na fila (enqueue)
int enqueue(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        return 0; // Fila cheia
    }
    fila->tras = (fila->tras + 1) % CAPACIDADE_FILA;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
    return 1;
}

// Função para remover uma peça da fila (dequeue)
Peca dequeue(FilaCircular *fila) {
    Peca pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % CAPACIDADE_FILA;
    fila->tamanho--;
    return pecaRemovida;
}

// Função para exibir a fila
void mostrarFila(FilaCircular *fila) {
    if (filaVazia(fila)) {
        printf("\n🎮 Fila de Peças: [VAZIA]\n");
        return;
    }
    
    printf("\n🎮 Fila de Peças (frente -> trás):\n");
    printf("┌");
    for (int i = 0; i < fila->tamanho; i++) {
        printf("─────────");
        if (i < fila->tamanho - 1) printf("┬");
    }
    printf("┐\n");
    
    printf("│");
    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->frente + i) % CAPACIDADE_FILA;
        printf("  [%c-%02d] ", fila->pecas[indice].tipo, fila->pecas[indice].id);
        printf("│");
    }
    printf("\n");
    
    printf("└");
    for (int i = 0; i < fila->tamanho; i++) {
        printf("─────────");
        if (i < fila->tamanho - 1) printf("┴");
    }
    printf("┘\n");
    printf("  Tamanho: %d/%d\n", fila->tamanho, CAPACIDADE_FILA);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    FilaCircular fila;
    inicializarFila(&fila);
    
    // Preencher a fila com 5 peças iniciais
    printf("🎮 TETRIS STACK - Nível Novato 🎮\n");
    printf("═══════════════════════════════════\n");
    printf("Inicializando fila com 5 peças...\n");
    
    for (int i = 0; i < CAPACIDADE_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(&fila, novaPeca);
    }
    
    int opcao;
    do {
        mostrarFila(&fila);
        
        printf("\n╔═══════════════════════════════╗\n");
        printf("║         MENU PRINCIPAL        ║\n");
        printf("╠═══════════════════════════════╣\n");
        printf("║ 1 - Jogar peça (remover)     ║\n");
        printf("║ 0 - Sair                      ║\n");
        printf("╚═══════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca pecaJogada = dequeue(&fila);
                    printf("\n✅ Peça jogada: [%c-%02d]\n", pecaJogada.tipo, pecaJogada.id);
                    
                    // Inserir nova peça automaticamente
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                    printf("➕ Nova peça adicionada: [%c-%02d]\n", novaPeca.tipo, novaPeca.id);
                } else {
                    printf("\n❌ Erro: Fila está vazia!\n");
                }
                break;
            case 0:
                printf("\n👋 Encerrando o jogo. Até logo!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Limpar buffer
            getchar(); // Esperar ENTER
            printf("\n");
        }
        
    } while (opcao != 0);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

