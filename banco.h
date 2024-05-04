#ifndef BANCO_H
#define BANCO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef struct {
    char nome[50];
    char cpf[12];
    char tipo_conta[10];
    float saldo;
    float limite_negativo;
    float taxa_debito;
    char senha[20];
    char *extrato;
} Cliente;

typedef struct {
    char tipo[20];
    float valor;
    time_t timestamp;
} Transacao;

void salvarDados();
void carregarDados();
void novoCliente();
void apagaCliente();
void listarClientes();
void debito();
void deposito();
void extrato();
void transferencia();

#endif /* BANCO_H */
