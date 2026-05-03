
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ==============================
// STRUCT
// ==============================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ==============================
// VARIÁVEIS
// ==============================
Componente componentes[MAX];
int total = 0;

int comparacoes = 0;

// ==============================
// CADASTRO
// ==============================
void adicionarComponente() {
    if (total >= MAX) {
        printf("\nLimite atingido!\n");
        return;
    }

    printf("\n--- Adicionar item ---\n");

    printf("Nome: ");
    scanf(" %[^\n]", componentes[total].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", componentes[total].tipo);

    printf("Prioridade (1-10): ");
    scanf("%d", &componentes[total].prioridade);

    total++;
}

// ==============================
// LISTAR
// ==============================
void listarComponentes() {
    if (total == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }

    printf("\n===== COMPONENTES =====\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Prioridade");

    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d\n",
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade);
    }
}

// ==============================
// BUBBLE SORT (NOME)
// ==============================
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    Componente temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// ==============================
// INSERTION SORT (TIPO)
// ==============================
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// ==============================
// SELECTION SORT (PRIORIDADE)
// ==============================
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    Componente temp;

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }

        temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

// ==============================
// BUSCA BINÁRIA (POR NOME)
// ==============================
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(v[meio].nome, nome);

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
// MEDIR TEMPO
// ==============================
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio, fim;

    inicio = clock();
    algoritmo(v, n);
    fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);
}

// ==============================
// MAIN
// ==============================
int main() {
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n=========================\n");
        printf(" MOCHILA DE SOBREVIVENCIA\n");
        printf("=========================\n");
        printf("1 - Adicionar itens\n");
        printf("2 - Listar itens\n");
        printf("3 - Ordenar por Nome (Bubble)\n");
        printf("4 - Ordenar por Tipo (Insertion)\n");
        printf("5 - Ordenar por Prioridade (Selection)\n");
        printf("6 - Buscar item (Binaria - nome)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarComponente();
                break;

            case 2:
                listarComponentes();
                break;

            case 3:
                medirTempo(bubbleSortNome, componentes, total);
                listarComponentes();
                break;

            case 4:
                medirTempo(insertionSortTipo, componentes, total);
                listarComponentes();
                break;

            case 5:
                medirTempo(selectionSortPrioridade, componentes, total);
                listarComponentes();
                break;

            case 6:
                printf("Nome do componente-chave: ");
                scanf(" %[^\n]", nomeBusca);

                int pos = buscaBinariaPorNome(componentes, total, nomeBusca);

                if (pos != -1)
                    printf("Componente encontrado!\n");
                else
                    printf("Componente nao encontrado!\n");

                break;
        }

    } while (opcao != 0);

    return 0;
}
