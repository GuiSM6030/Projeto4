#include <stdio.h>
#include "banco.h"

int main() {
    carregarDados();

    int opcao;
    do {
        printf("\nMenu de Opções:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novoCliente();
                break;
            case 2:
                apagaCliente();
                break;
            case 3:
                listarClientes();
                break;
            case 4:
                debito();
                break;
            case 5:
                deposito();
                break;
            case 6:
                extrato();
                break;
            case 7:
                transferencia();
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 8);

    return 0;
}
