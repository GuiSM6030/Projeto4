#ifndef BANCO_H
#define BANCO_H

#include <stdio.h>    // Inclusão da biblioteca padrão de entrada e saída
#include <stdlib.h>   // Inclusão da biblioteca padrão de funções utilitárias
#include <string.h>   // Inclusão da biblioteca padrão de manipulação de strings
#include <time.h>     // Inclusão da biblioteca padrão para manipulação de tempo

// Definição de macros para o número máximo de clientes e operações
#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

// Definição da estrutura para representar um cliente
typedef struct {
    char nome[50];             // Nome do cliente
    char cpf[12];              // CPF do cliente
    char tipo_conta[10];       // Tipo de conta do cliente
    float saldo;               // Saldo do cliente
    float limite_negativo;     // Limite negativo permitido para a conta
    float taxa_debito;         // Taxa de débito
    char senha[20];            // Senha do cliente
    char *extrato;             // Ponteiro para o extrato do cliente
} Cliente;

// Definição da estrutura para representar uma transação
typedef struct {
    char tipo[20];             // Tipo da transação (ex: saque, depósito, etc.)
    float valor;               // Valor da transação
    time_t timestamp;          // Armazena a data e hora da transação
} Transacao;

// Protótipos das funções
void salvarDados();            // Função para salvar os dados do banco
void carregarDados();          // Função para carregar os dados do banco
void novoCliente();            // Função para adicionar um novo cliente
void apagaCliente();           // Função para remover um cliente
void listarClientes();         // Função para listar todos os clientes
void debito();                 // Função para realizar um débito na conta de um cliente
void deposito();               // Função para realizar um depósito na conta de um cliente
void extrato();                // Função para imprimir o extrato de um cliente
void transferencia();          // Função para realizar uma transferência entre contas

#endif /* BANCO_H */
