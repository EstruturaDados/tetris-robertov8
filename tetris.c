#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define CAPACIDADE_FILA 5
#define CAPACIDADE_PILHA 3

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

// 🧠 Nível Aventureiro: Pilha de Reserva

// Struct para a Pilha Linear
typedef struct {
    Peca pecas[CAPACIDADE_PILHA];
    int topo;
} PilhaLinear;

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

// Função para inicializar a pilha
void inicializarPilha(PilhaLinear *pilha) {
    pilha->topo = -1;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(PilhaLinear *pilha) {
    return pilha->topo == -1;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(PilhaLinear *pilha) {
    return pilha->topo == CAPACIDADE_PILHA - 1;
}

// Função para inserir uma peça na pilha (push)
int push(PilhaLinear *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        return 0; // Pilha cheia
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
    return 1;
}

// Função para remover uma peça da pilha (pop)
Peca pop(PilhaLinear *pilha) {
    Peca pecaRemovida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return pecaRemovida;
}

// Função para exibir a pilha
void mostrarPilha(PilhaLinear *pilha) {
    if (pilhaVazia(pilha)) {
        printf("\n📚 Pilha de Reserva: [VAZIA]\n");
        return;
    }
    
    printf("\n📚 Pilha de Reserva (topo -> base):\n");
    printf("  ┌─────────┐\n");
    
    for (int i = pilha->topo; i >= 0; i--) {
        printf("  │ [%c-%02d] │", pilha->pecas[i].tipo, pilha->pecas[i].id);
        if (i == pilha->topo) printf(" ← TOPO");
        printf("\n");
        if (i > 0) printf("  ├─────────┤\n");
    }
    
    printf("  └─────────┘\n");
    printf("  Tamanho: %d/%d\n", pilha->topo + 1, CAPACIDADE_PILHA);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    FilaCircular fila;
    PilhaLinear pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    // Preencher a fila com 5 peças iniciais
    printf("🎮 TETRIS STACK - Nível Aventureiro 🎮\n");
    printf("═══════════════════════════════════════\n");
    printf("Inicializando fila com 5 peças...\n");
    
    for (int i = 0; i < CAPACIDADE_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(&fila, novaPeca);
    }
    
    int opcao;
    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);
        
        printf("\n╔═══════════════════════════════════╗\n");
        printf("║         MENU PRINCIPAL            ║\n");
        printf("╠═══════════════════════════════════╣\n");
        printf("║ 1 - Jogar peça (remover)         ║\n");
        printf("║ 2 - Reservar peça (fila → pilha) ║\n");
        printf("║ 3 - Usar peça reservada (pilha)  ║\n");
        printf("║ 0 - Sair                          ║\n");
        printf("╚═══════════════════════════════════╝\n");
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
                    printf("➕ Nova peça adicionada à fila: [%c-%02d]\n", novaPeca.tipo, novaPeca.id);
                } else {
                    printf("\n❌ Erro: Fila está vazia!\n");
                }
                break;
            
            case 2:
                if (filaVazia(&fila)) {
                    printf("\n❌ Erro: Fila está vazia! Não há peças para reservar.\n");
                } else if (pilhaCheia(&pilha)) {
                    printf("\n❌ Erro: Pilha de reserva está cheia!\n");
                } else {
                    // Remove da frente da fila
                    Peca pecaReservada = dequeue(&fila);
                    // Adiciona na pilha
                    push(&pilha, pecaReservada);
                    printf("\n📦 Peça reservada: [%c-%02d]\n", pecaReservada.tipo, pecaReservada.id);
                    
                    // Inserir nova peça na fila para manter sempre 5 peças
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                    printf("➕ Nova peça adicionada à fila: [%c-%02d]\n", novaPeca.tipo, novaPeca.id);
                }
                break;
            
            case 3:
                if (pilhaVazia(&pilha)) {
                    printf("\n❌ Erro: Pilha de reserva está vazia!\n");
                } else {
                    Peca pecaUsada = pop(&pilha);
                    printf("\n✅ Peça reservada usada: [%c-%02d]\n", pecaUsada.tipo, pecaUsada.id);
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

