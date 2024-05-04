#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

void salvarDados() {
    FILE *arquivo;
    arquivo = fopen("dados_clientes.bin", "wb");

    if (arquivo != NULL) {
        fwrite(clientes, sizeof(Cliente), num_clientes, arquivo);
        fclose(arquivo);
    }
}

void carregarDados() {
    FILE *arquivo;
    arquivo = fopen("dados_clientes.bin", "rb");

    if (arquivo != NULL) {
        fread(clientes, sizeof(Cliente), MAX_CLIENTES, arquivo);
        fclose(arquivo);
        num_clientes = 0;
        while (strcmp(clientes[num_clientes].cpf, "") != 0 && num_clientes < MAX_CLIENTES) {
            num_clientes++;
        }
    } else {
        printf("Erro ao abrir o arquivo de dados.\n");
    }
}

void novoCliente() {
    Cliente novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("CPF: ");
    scanf(" %s", novo.cpf);
    printf("Senha: ");
    scanf(" %s", novo.senha);
    printf("Tipo de conta (comum ou plus): ");
    scanf(" %s", novo.tipo_conta);
    printf("Valor inicial da conta: ");
    scanf("%f", &novo.saldo);

    if (strcmp(novo.tipo_conta, "comum") == 0) {
        novo.limite_negativo = -1000.0;
        novo.taxa_debito = 0.05;
    } else if (strcmp(novo.tipo_conta, "plus") == 0) {
        novo.limite_negativo = -5000.0;
        novo.taxa_debito = 0.03;
    } else {
        printf("Tipo de conta inválido!\n");
        return;
    }

    novo.extrato = malloc(sizeof(char) * 1000);
    novo.extrato[0] = '\0';

    clientes[num_clientes++] = novo;
    printf("Cliente cadastrado com sucesso!\n");
    salvarDados();
}

void apagaCliente() {
    char cpf[12];
    printf("CPF do cliente a ser apagado: ");
    scanf(" %s", cpf);

    int i;
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;
            printf("Cliente apagado com sucesso!\n");
            salvarDados();
            return;
        }
    }

    printf("Cliente não encontrado.\n");
}
