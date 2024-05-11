#include <stdio.h>    // Inclusão da biblioteca padrão de entrada e saída
#include "banco.h"    // Inclusão do arquivo de cabeçalho local

int main() {
    carregarDados();    // Chamada da função para carregar os dados dos clientes

    int opcao;    // Declaração de uma variável para armazenar a opção do usuário
    do {
        printf("\nMenu de Opções:\n");    // Impressão do menu de opções
        printf("1. Novo cliente\n");    // Opção para adicionar um novo cliente
        printf("2. Apagar cliente\n");    // Opção para apagar um cliente existente
        printf("3. Listar clientes\n");    // Opção para listar todos os clientes cadastrados
        printf("4. Débito\n");    // Opção para realizar um débito na conta de um cliente
        printf("5. Depósito\n");    // Opção para realizar um depósito na conta de um cliente
        printf("6. Extrato\n");    // Opção para imprimir o extrato de um cliente
        printf("7. Transferência\n");    // Opção para realizar uma transferência entre contas
        printf("8. Sair\n");    // Opção para sair do programa
        printf("Escolha uma opção: ");    // Solicitação para que o usuário escolha uma opção
        scanf("%d", &opcao);    // Leitura da opção escolhida pelo usuário

        switch (opcao) {    // Estrutura de controle switch para tratar a opção escolhida pelo usuário
            case 1:
                novoCliente();    // Chamada da função para adicionar um novo cliente
                break;
            case 2:
                apagaCliente();    // Chamada da função para apagar um cliente existente
                break;
            case 3:
                listarClientes();    // Chamada da função para listar todos os clientes cadastrados
                break;
            case 4:
                debito();    // Chamada da função para realizar um débito na conta de um cliente
                break;
            case 5:
                deposito();    // Chamada da função para realizar um depósito na conta de um cliente
                break;
            case 6:
                extrato();    // Chamada da função para imprimir o extrato de um cliente
                break;
            case 7:
                transferencia();    // Chamada da função para realizar uma transferência entre contas
                break;
            case 8:
                printf("Saindo...\n");    // Mensagem informando que o programa está sendo encerrado
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");    // Mensagem de erro para opção inválida
                break;
        }
    } while (opcao != 8);    // Repetição do loop até que o usuário escolha a opção de sair

    return 0;    // Retorno 0 indicando que o programa foi executado com sucesso
}
