#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 1000

typedef struct Node {
    char nome[50];
    char telefone[15];
    struct Node* next;
} Node;

Node* hash_table[TAM];  // VETOR DE LISTA ENCADEADA

unsigned int hash_function(const char* nome) { // FUNÇÃO DE HASH - FORÇA POSITIVOS
    unsigned int hash = 0;
    while (*nome) {
        hash += *nome;
        nome++;
    }
    return hash % TAM;
}

Node* cria_node(const char* nome, const char* telefone) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro na alocacao.\n");
        exit(1);
    }
    strcpy(new_node->nome, nome); //(dest,origem)
    strcpy(new_node->telefone, telefone);
    new_node->next = NULL;
    return new_node;
}

void add_contato(const char* nome, const char* telefone) {
    unsigned int index = hash_function(nome);
    Node* new_node = cria_node(nome, telefone);
    if (!hash_table[index]) {
        hash_table[index] = new_node;
    } else {
        Node* atual = hash_table[index];
        while (atual->next) {
            if (strcmp(atual->nome, nome) == 0) {
                //se nomes iguais, atualiza telefone
                strcpy(atual->nome, telefone);
                free(new_node);
                return;
            }
            atual = atual->next;
        }
        atual->next = new_node;
    }
    printf("Contado adicionado.\n");
}

void buscaContato(const char* nome) {
    unsigned int index = hash_function(nome);
    Node* atual = hash_table[index];
    clock_t start = clock();
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t end = clock();
            printf("Telefone de %s: %s (tempo: %.4f ms)\n", nome, atual->telefone, 
                   ((double)(end - start) / CLOCKS_PER_SEC) * 1000); // formula para calcular o tempo
            return;
        }
        atual = atual->next;
    }
    printf("Contato não encontrado.\n");
}

void removeContato(const char* nome) {
    unsigned int index = hash_function(nome);
    Node* atual = hash_table[index];
    Node* anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->next = atual->next;
            } else {
                hash_table[index] = atual->next;
            }
            free(atual);
            printf("Contato removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    printf("Contact not found.\n");
}

void mostraContato() {
    for (int i = 0; i < TAM; i++) {
        Node* atual = hash_table[i];
        if (atual) {
            printf("Index %d:\n", i);
            while (atual) {
                printf("  Nome: %s, Telefone: %s\n", atual->nome, atual->nome);
                atual = atual->next;
            }
        }
    }
}

int main() {
    int op;
    char nome[50], telefone[15];

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adiciona Contato\n");
        printf("2 - Busca contato por nome\n");
        printf("3 - Remove contato\n");
        printf("4 - Lista contatos\n");
        printf("0 - Sair\n");
        printf("Entre com das opcoes: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Entre com o nome: ");
                scanf("%s", nome);
                printf("Enter phone: ");
                scanf("%s", telefone);
                add_contato(nome, telefone);
                break;
            case 2:
                printf("Entre com o nome: ");
                scanf("%s", nome);
                buscaContato(nome);
                break;
            case 3:
                printf("Entre com o nome: ");
                scanf("%s", nome);
                removeContato(nome);
                break;
            case 4:
                mostraContato();
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida!!.\n");
        }
    }
    return 0;
}