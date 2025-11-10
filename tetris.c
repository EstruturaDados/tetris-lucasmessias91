

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5

typedef struct {
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

int estaVazia(Fila *f) {
    return f->quantidade == 0;
}

int estaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L', 'S', 'Z', 'J'};
    Peca nova;
    nova.id = id;
    nova.tipo = tipos[rand() % 7];
    return nova;
}

void enfileirar(Fila *f, Peca p) {
    if (estaCheia(f)) {
        printf("⚠️ A fila está cheia! Não é possível inserir mais peças.\n");
        return;
    }
    f->fim = (f->fim + 1) % TAM_FILA;
    f->fila[f->fim] = p;
    f->quantidade++;
}

Peca desenfileirar(Fila *f) {
    Peca removida = {-1, '?'};
    if (estaVazia(f)) {
        printf("⚠️ A fila está vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

void mostrarFila(Fila *f) {
    printf("\n🎮 Fila atual de peças:\n");
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    int i, idx;
    for (i = 0; i < f->quantidade; i++) {
        idx = (f->inicio + i) % TAM_FILA;
        printf("Posição %d → Peça ID:%d | Tipo:%c\n", i + 1, f->fila[idx].id, f->fila[idx].tipo);
    }
}

int main() {
    Fila fila;
    int opcao;
    int contadorID = 1;
    Peca p;
    srand(time(NULL));

    inicializarFila(&fila);

    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorID++));
    }

    do {
        printf("\n====== 🎮 TETRIS STACK - NÍVEL NOVATO ======\n");
        printf("1. Jogar peça (remover da frente)\n");
        printf("2. Inserir nova peça\n");
        printf("3. Visualizar fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                p = desenfileirar(&fila);
                if (p.id != -1)
                    printf("👉 Peça jogada: ID:%d | Tipo:%c\n", p.id, p.tipo);
                break;
            case 2:
                if (!estaCheia(&fila)) {
                    enfileirar(&fila, gerarPeca(contadorID++));
                    printf("✅ Nova peça adicionada à fila!\n");
                } else {
                    printf("⚠️ Não é possível adicionar, a fila está cheia!\n");
                }
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 0:
                printf("👋 Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}