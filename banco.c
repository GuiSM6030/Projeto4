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

void listarClientes() {
    printf("Lista de Clientes:\n");
    int i;
    for (i = 0; i < num_clientes; i++) {
        printf("Nome: %s\nCPF: %s\nTipo de Conta: %s\nSaldo: R$ %.2f\n\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].tipo_conta, clientes[i].saldo);
    }
}


void debito() {
    char cpf[12], senha[20];
    float valor;
    printf("CPF: ");
    scanf(" %s", cpf);
    printf("Senha: ");
    scanf(" %s", senha);
    printf("Valor a ser debitado: ");
    scanf("%f", &valor);

    int i;
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            if (clientes[i].saldo - valor >= clientes[i].limite_negativo) {
                clientes[i].saldo -= valor;
                registrarTransacao(&clientes[i], "Débito", valor);
                printf("Débito realizado com sucesso!\n");
                salvarDados();
                return;
            } else {
                printf("Saldo insuficiente para realizar o débito.\n");
                return;
            }
        }
    }

    printf("CPF ou senha incorretos.\n");
}

void deposito() {
    char cpf[12];
    float valor;
    printf("CPF: ");
    scanf(" %s", cpf);
    printf("Valor a ser depositado: ");
    scanf("%f", &valor);

    int i;
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clientes[i].saldo += valor;
            registrarTransacao(&clientes[i], "Depósito", valor);
            printf("Depósito realizado com sucesso!\n");
            salvarDados();
            return;
        }
    }

    printf("CPF não encontrado.\n");
}

void extrato() {
    char cpf[12], senha[20];
    printf("CPF: ");
    scanf(" %s", cpf);
    printf("Senha: ");
    scanf(" %s", senha);

    int i;
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            printf("Extrato do cliente:\n");
            printf("Nome: %s\nCPF: %s\nTipo de Conta: %s\nSaldo: R$ %.2f\n",
                   clientes[i].nome, clientes[i].cpf, clientes[i].tipo_conta, clientes[i].saldo);
            printf("Transações: \n%s\n", clientes[i].extrato);
            return;
        }
    }

    printf("CPF ou senha incorretos.\n");
}

void transferencia() {
    char cpf_origem[12], senha_origem[20], cpf_destino[12];
    float valor;
    printf("CPF (Origem): ");
    scanf(" %s", cpf_origem);
    printf("Senha (Origem): ");
    scanf(" %s", senha_origem);
    printf("CPF (Destino): ");
    scanf(" %s", cpf_destino);
    printf("Valor a ser transferido: ");
    scanf("%f", &valor);

    int i, origem_idx = -1, destino_idx = -1;
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha_origem) == 0) {
            origem_idx = i;
        } else if (strcmp(clientes[i].cpf, cpf_destino) == 0) {
            destino_idx = i;
        }
    }

    if (origem_idx != -1 && destino_idx != -1) {
        if (clientes[origem_idx].saldo - valor >= clientes[origem_idx].limite_negativo) {
            clientes[origem_idx].saldo -= valor;
            clientes[destino_idx].saldo += valor;
            registrarTransacao(&clientes[origem_idx], "Transferência para CPF: %s", valor);
            registrarTransacao(&clientes[destino_idx], "Transferência de CPF: %s", valor);
            printf("Transferência realizada com sucesso!\n");
            salvarDados();
            return;
        } else {
            printf("Saldo insuficiente para realizar a transferência.\n");
            return;
        }
    }

    printf("CPF (Origem) ou CPF (Destino) não encontrado.\n");
}