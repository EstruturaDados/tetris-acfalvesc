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

#define MAX 5  // tamanho da fila
#define MAXP 3 // capacidade da pilha

// Estrutura que representa uma peça de Tetris
typedef struct
{
    char nome[10];
    int id;
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct
{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura que representa a pilha de peças reservadas
typedef struct
{
    Peca itens[MAXP];
    int topo;
} Pilha;

// --- Funções da Fila Circular ---
void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

Peca gerarPeca(int id)
{
    Peca p;
    char tipos[7][3] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(p.nome, tipos[id % 7]);
    p.id = id;
    return p;
}

void inserirFila(Fila *f, Peca p)
{
    if (filaCheia(f))
        return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void removerFila(Fila *f, Peca *p)
{
    if (filaVazia(f))
        return;
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f)
{
    printf("\n🎮 Fila de Peças: ");
    if (filaVazia(f))
    {
        printf("(vazia)\n");
        return;
    }

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%s,%d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// --- Funções da Pilha ---
void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAXP - 1;
}

void push(Pilha *p, Peca x)
{
    if (pilhaCheia(p))
    {
        printf("\n⚠️  Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->itens[++(p->topo)] = x;
    printf("📦 Peça [%s,%d] reservada no topo da pilha!\n", x.nome, x.id);
}

void pop(Pilha *p, Peca *x)
{
    if (pilhaVazia(p))
    {
        printf("\n⚠️  Pilha vazia! Nenhuma peça reservada para usar.\n");
        return;
    }
    *x = p->itens[(p->topo)--];
    printf("🧱 Peça usada (removida da pilha): [%s,%d]\n", x->nome, x->id);
}

void peek(Pilha *p)
{
    if (pilhaVazia(p))
    {
        printf("\nPilha de reservadas: (vazia)\n");
        return;
    }
    printf("\n🔝 Topo da pilha: [%s,%d]\n", p->itens[p->topo].nome, p->itens[p->topo].id);
}

void mostrarPilha(Pilha *p)
{
    printf("📦 Pilha de Reservadas: ");
    if (pilhaVazia(p))
    {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%s,%d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}

// --- NOVAS FUNÇÕES ---
// Trocar a peça da frente da fila com o topo da pilha
void trocarPecaAtual(Fila *f, Pilha *p)
{
    if (filaVazia(f) || pilhaVazia(p))
    {
        printf("\n⚠️  Não é possível trocar! Fila ou pilha vazia.\n");
        return;
    }

    int idxFrente = f->inicio;
    Peca temp = f->itens[idxFrente];
    f->itens[idxFrente] = p->itens[p->topo];
    p->itens[p->topo] = temp;

    printf("🔄 Peça da frente da fila trocada com o topo da pilha!\n");
}

// Troca múltipla: 3 primeiras da fila ↔ 3 do topo da pilha
void trocaMultipla(Fila *f, Pilha *p)
{
    if (f->total < 3 || p->topo < 2)
    {
        printf("\n⚠️  É necessário ter pelo menos 3 peças na fila e na pilha!\n");
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        int idxFila = (f->inicio + i) % MAX;
        int idxPilha = p->topo - i;

        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = temp;
    }

    printf("🔁 Troca múltipla realizada entre as 3 primeiras peças da fila e as 3 do topo da pilha!\n");
}

// --- Programa Principal ---
int main()
{
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contador = 0;
    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX; i++)
    {
        inserirFila(&fila, gerarPeca(contador++));
    }

    int opcao;
    Peca p;

    do
    {
        printf("\n=== MENU TETRIS ===\n");
        printf("1. Visualizar estado atual\n");
        printf("2. Jogar (remover peça da frente da fila)\n");
        printf("3. Reservar peça (mover da fila para pilha)\n");
        printf("4. Usar peça reservada (retirar do topo da pilha)\n");
        printf("5. Trocar peça atual (frente ↔ topo)\n");
        printf("6. Troca múltipla (3 peças)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            mostrarFila(&fila);
            mostrarPilha(&pilha);
            peek(&pilha);
            break;

        case 2:
            if (!filaVazia(&fila))
            {
                removerFila(&fila, &p);
                printf("🧱 Peça jogada: [%s,%d]\n", p.nome, p.id);
                inserirFila(&fila, gerarPeca(contador++));
                printf("✅ Nova peça gerada e adicionada ao final da fila!\n");
            }
            else
                printf("⚠️  Fila vazia!\n");
            break;

        case 3:
            if (!filaVazia(&fila))
            {
                removerFila(&fila, &p);
                push(&pilha, p);
                inserirFila(&fila, gerarPeca(contador++));
            }
            else
                printf("⚠️  Fila vazia, nada a reservar!\n");
            break;

        case 4:
            pop(&pilha, &p);
            if (!pilhaCheia(&pilha))
            {
                inserirFila(&fila, gerarPeca(contador++));
                printf("✅ Nova peça gerada e adicionada ao final da fila!\n");
            }
            break;

        case 5:
            trocarPecaAtual(&fila, &pilha);
            break;

        case 6:
            trocaMultipla(&fila, &pilha);
            break;

        case 0:
            printf("\nEncerrando o jogo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
