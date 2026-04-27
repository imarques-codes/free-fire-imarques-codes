#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ==============================
// STRUCTS
// ==============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==============================
// VARIAVEIS
// ==============================
Item mochila[MAX_ITENS];
int totalItens = 0;

No* lista = NULL;

int compSeq = 0;
int compBin = 0;

// ==============================
// ======== VETOR ==============
// ==============================

int buscarItem(char nome[]) {
    compSeq = 0;

    for (int i = 0; i < totalItens; i++) {
        compSeq++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void listarItens() {
    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n===== INVENTARIO =====\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n--- Adicionar item ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    listarItens();
}

void removerItem() {
    char nome[30];

    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    int pos = buscarItem(nome);

    if (pos == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("\nItem removido!\n");
    listarItens();
}

// Ordenação (Bubble Sort)
void ordenarVetor() {
    Item temp;

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("\nItens ordenados por nome!\n");
}

// Busca binária
int buscaBinaria(char nome[]) {
    int inicio = 0, fim = totalItens - 1;
    compBin = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBin++;

        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ==============================
// ===== LISTA ENCADEADA ========
// ==============================

void inserirLista() {
    No* novo = (No*) malloc(sizeof(No));

    printf("\n--- Adicionar item ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = lista;
    lista = novo;
}

void listarLista() {
    No* aux = lista;

    if (aux == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n===== INVENTARIO =====\n");

    while (aux != NULL) {
        printf("%s | %s | %d\n",
               aux->dados.nome,
               aux->dados.tipo,
               aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void removerLista() {
    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = lista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {

            if (anterior == NULL)
                lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("\nItem removido!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem nao encontrado!\n");
}

void buscarLista() {
    char nome[30];
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nome);

    No* aux = lista;
    compSeq = 0;

    while (aux != NULL) {
        compSeq++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("\nEncontrado (%d comparacoes)\n", compSeq);
            return;
        }
        aux = aux->proximo;
    }

    printf("\nNao encontrado (%d comparacoes)\n", compSeq);
}

// ==============================
// MENU PRINCIPAL
// ==============================

int main() {
    int estrutura, opcao;
    char nome[30];

    do {
        printf("\n=========================\n");
        printf("   MOCHILA DE SOBREVIVENCIA\n");
        printf("=========================\n");
        printf("1 - Usar Vetor\n");
        printf("2 - Usar Lista Encadeada\n");
        printf("0 - Sair\n");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\n--- VETOR ---\n");
                printf("1 - Adicionar item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item (Sequencial)\n");
                printf("5 - Ordenar itens\n");
                printf("6 - Buscar item (Binaria)\n");
                printf("0 - Voltar\n");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItem(); break;
                    case 2: removerItem(); break;
                    case 3: listarItens(); break;
                    case 4:
                        printf("Nome: "); scanf(" %[^\n]", nome);
                        int pos = buscarItem(nome);
                        printf("Comparacoes: %d\n", compSeq);
                        if (pos != -1) printf("Encontrado\n");
                        break;
                    case 5: ordenarVetor(); break;
                    case 6:
                        printf("Nome: "); scanf(" %[^\n]", nome);
                        pos = buscaBinaria(nome);
                        printf("Comparacoes: %d\n", compBin);
                        if (pos != -1) printf("Encontrado\n");
                        break;
                }

            } while (opcao != 0);
        }

        else if (estrutura == 2) {
            do {
                printf("\n--- LISTA ENCADEADA ---\n");
                printf("1 - Adicionar item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item\n");
                printf("0 - Voltar\n");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirLista(); break;
                    case 2: removerLista(); break;
                    case 3: listarLista(); break;
                    case 4: buscarLista(); break;
                }

            } while (opcao != 0);
        }

    } while (estrutura != 0);

    return 0;
}
