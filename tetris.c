#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// Estrutura que representa uma peça de Tetris
typedef struct {
    char nome[10];
    int id;
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Tetris;

// Inicializa a fila circular
void inicializarTetris(Tetris *t) {
    t->inicio = 0;
    t->fim = 0;
    t->total = 0;
}

// Verifica se a fila está cheia
int tetrisCheio(Tetris *t) {
    return t->total == MAX;
}

// Verifica se a fila está vazia
int tetrisVazio(Tetris *t) {
    return t->total == 0;
}

// Gera automaticamente uma nova peça (com nome e id)
Peca gerarPeca(int id) {
    Peca p;
    char tipos[7][3] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(p.nome, tipos[id % 7]);
    p.id = id;
    return p;
}

// Insere uma nova peça no final da fila (enqueue)
void inserir(Tetris *t, Peca p) {
    if (tetrisCheio(t)) {
        printf("\n⚠️  Máximo de peças. Não é possível inserir.\n");
        return;
    }
    t->itens[t->fim] = p;
    t->fim = (t->fim + 1) % MAX;
    t->total++;
}

// Remove a peça da frente da fila (dequeue)
void remover(Tetris *t, Peca *p) {
    if (tetrisVazio(t)) {
        printf("\n⚠️  Sem peças. Não é possível remover.\n");
        return;
    }

    *p = t->itens[t->inicio];
    t->inicio = (t->inicio + 1) % MAX;
    t->total--;
}

// Exibe todas as peças da fila atual
void mostrarTetris(Tetris *t) {
    printf("\n🎮 Fila de Peças: ");
    if (tetrisVazio(t)) {
        printf("(vazia)\n");
        return;
    }

    for (int i = 0, idx = t->inicio; i < t->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", t->itens[idx].nome, t->itens[idx].id);
    }
    printf("\n");
}

// Menu principal
int main() {
    Tetris t;
    inicializarTetris(&t);

    int contador = 0; // para gerar IDs únicos
    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < MAX; i++) {
        inserir(&t, gerarPeca(contador++));
    }

    int opcao;
    Peca p;

    do {
        printf("\n=== MENU TETRIS ===\n");
        printf("1. Visualizar fila atual\n");
        printf("2. Jogar (remover peça da frente)\n");
        printf("3. Inserir nova peça automaticamente\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarTetris(&t);
                break;

            case 2:
                remover(&t, &p);
                printf("🧱 Peça removida: [%s, %d]\n", p.nome, p.id);
                break;

            case 3:
                inserir(&t, gerarPeca(contador++));
                printf("✅ Nova peça inserida!\n");
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

