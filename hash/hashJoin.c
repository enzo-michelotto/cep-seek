#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

typedef struct _No {
    Endereco endereco;
    struct _No *prox;
} No;

#define HASH_SIZE 744977

unsigned int hash(char *cep) {
    unsigned long long hash_value = 0;
    for (int i = 0; i < 8; i++) {
        hash_value = hash_value * 33 + cep[i];
    }
    return hash_value % HASH_SIZE; 
}

void inserir_no_hash(No **hash_table, Endereco *e) {
    unsigned int hash_value = hash(e->cep);
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para um novo nó.\n");
        exit(1);
    }
    memcpy(&novo_no->endereco, e, sizeof(Endereco));
    novo_no->prox = hash_table[hash_value];
    hash_table[hash_value] = novo_no;
}

No* buscar_no_hash(No **hash_table, char *cep) {
    unsigned int hash_value = hash(cep);
    No *atual = hash_table[hash_value];
    while (atual != NULL) {
        if (strncmp(atual->endereco.cep, cep, 8) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int main() {
    FILE *arquivo1, *arquivo2, *saida;
    Endereco e;

    No **hash_table = (No **)malloc(HASH_SIZE * sizeof(No *));
    if (hash_table == NULL) {
        printf("Erro ao alocar memória para a tabela de hash.\n");
        return 1;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL;
    }

    arquivo1 = fopen("saida_a.dat", "rb");
    if (arquivo1 == NULL) {
        printf("Erro ao abrir o arquivo1.\n");
        free(hash_table);
        return 1;
    }

    while (fread(&e, sizeof(Endereco), 1, arquivo1)) {
        inserir_no_hash(hash_table, &e);
    }

    fclose(arquivo1);

    arquivo2 = fopen("saida_b.dat", "rb");
    if (arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo2.\n");
        free(hash_table);
        return 1;
    }

    saida = fopen("intersecao.dat", "wb");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(arquivo2);
        free(hash_table);
        return 1;
    }

    while (fread(&e, sizeof(Endereco), 1, arquivo2)) {
        if (buscar_no_hash(hash_table, e.cep) != NULL) {
            fwrite(&e, sizeof(Endereco), 1, saida);
        }
    }

    fclose(arquivo2);
    fclose(saida);

    for (int i = 0; i < HASH_SIZE; i++) {
        No *atual = hash_table[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(hash_table);

    printf("Interseção concluída. Arquivo 'intersecao.dat' gerado.\n");

    return 0;
}
