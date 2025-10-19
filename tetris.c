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

// Variáveis globais
int proximoId = 1;
Peca ultimaPecaJogada;
int temUltimaPeca = 0;

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

// 🔄 Nível Mestre: Funções Avançadas

// Função para trocar a peça da frente da fila com o topo da pilha
int trocarFrentePilha(FilaCircular *fila, PilhaLinear *pilha) {
    if (filaVazia(fila)) {
        printf("\n❌ Erro: Fila está vazia!\n");
        return 0;
    }
    if (pilhaVazia(pilha)) {
        printf("\n❌ Erro: Pilha está vazia!\n");
        return 0;
    }
    
    // Pegar a peça da frente da fila e do topo da pilha
    Peca pecaFila = fila->pecas[fila->frente];
    Peca pecaPilha = pilha->pecas[pilha->topo];
    
    // Trocar
    fila->pecas[fila->frente] = pecaPilha;
    pilha->pecas[pilha->topo] = pecaFila;
    
    printf("\n🔄 Troca realizada!\n");
    printf("   Fila recebeu: [%c-%02d]\n", pecaPilha.tipo, pecaPilha.id);
    printf("   Pilha recebeu: [%c-%02d]\n", pecaFila.tipo, pecaFila.id);
    
    return 1;
}

// Função para inverter completamente a fila com a pilha
int inverterFilaPilha(FilaCircular *fila, PilhaLinear *pilha) {
    // Verificar se há elementos suficientes
    if (filaVazia(fila) && pilhaVazia(pilha)) {
        printf("\n❌ Erro: Ambas as estruturas estão vazias!\n");
        return 0;
    }
    
    // Arrays temporários para armazenar os elementos
    Peca tempFila[CAPACIDADE_FILA];
    int tamanhoFila = fila->tamanho;
    
    Peca tempPilha[CAPACIDADE_PILHA];
    int tamanhoPilha = pilha->topo + 1;
    
    // Copiar elementos da fila para array temporário
    for (int i = 0; i < tamanhoFila; i++) {
        int indice = (fila->frente + i) % CAPACIDADE_FILA;
        tempFila[i] = fila->pecas[indice];
    }
    
    // Copiar elementos da pilha para array temporário
    for (int i = 0; i <= pilha->topo; i++) {
        tempPilha[i] = pilha->pecas[i];
    }
    
    // Limpar fila e pilha
    inicializarFila(fila);
    inicializarPilha(pilha);
    
    // Colocar elementos da pilha na fila
    for (int i = 0; i < tamanhoPilha; i++) {
        enqueue(fila, tempPilha[i]);
    }
    
    // Colocar elementos da fila na pilha
    for (int i = 0; i < tamanhoFila; i++) {
        push(pilha, tempFila[i]);
    }
    
    printf("\n🔄 Inversão completa realizada!\n");
    printf("   Fila agora tem %d peças (vindas da pilha)\n", tamanhoPilha);
    printf("   Pilha agora tem %d peças (vindas da fila)\n", tamanhoFila);
    
    return 1;
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    FilaCircular fila;
    PilhaLinear pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    // Preencher a fila com 5 peças iniciais
    printf("🎮 TETRIS STACK - Nível Mestre 🎮\n");
    printf("══════════════════════════════════════\n");
    printf("Inicializando fila com 5 peças...\n");
    
    for (int i = 0; i < CAPACIDADE_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(&fila, novaPeca);
    }
    
    int opcao;
    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);
        
        printf("\n╔═══════════════════════════════════════╗\n");
        printf("║          MENU PRINCIPAL               ║\n");
        printf("╠═══════════════════════════════════════╣\n");
        printf("║ 1 - Jogar peça (remover)             ║\n");
        printf("║ 2 - Reservar peça (fila → pilha)     ║\n");
        printf("║ 3 - Usar peça reservada (pilha)      ║\n");
        printf("║ 4 - Trocar frente da fila com topo   ║\n");
        printf("║ 5 - Desfazer última jogada           ║\n");
        printf("║ 6 - Inverter fila com pilha          ║\n");
        printf("║ 0 - Sair                              ║\n");
        printf("╚═══════════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca pecaJogada = dequeue(&fila);
                    
                    // Salvar para desfazer
                    ultimaPecaJogada = pecaJogada;
                    temUltimaPeca = 1;
                    
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
            
            case 4:
                trocarFrentePilha(&fila, &pilha);
                break;
            
            case 5:
                if (!temUltimaPeca) {
                    printf("\n❌ Erro: Nenhuma jogada para desfazer!\n");
                } else {
                    // Verificar se há espaço na fila
                    if (filaCheia(&fila)) {
                        printf("\n❌ Erro: Fila está cheia! Não é possível desfazer.\n");
                    } else {
                        // Remove a última peça gerada (do final da fila)
                        // Para isso, precisamos decrementar o tamanho
                        fila.tras = (fila.tras - 1 + CAPACIDADE_FILA) % CAPACIDADE_FILA;
                        fila.tamanho--;
                        
                        // Adiciona a peça jogada de volta na frente
                        fila.frente = (fila.frente - 1 + CAPACIDADE_FILA) % CAPACIDADE_FILA;
                        fila.pecas[fila.frente] = ultimaPecaJogada;
                        fila.tamanho++;
                        
                        printf("\n⏪ Desfazer: Peça [%c-%02d] retornou à frente da fila!\n", 
                               ultimaPecaJogada.tipo, ultimaPecaJogada.id);
                        
                        temUltimaPeca = 0;
                    }
                }
                break;
            
            case 6:
                inverterFilaPilha(&fila, &pilha);
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

    return 0;
}

