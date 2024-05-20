#include <stdio.h>    // Inclusão da biblioteca padrão de entrada e saída
#include <stdlib.h>   // Inclusão da biblioteca padrão de funções utilitárias
#include <string.h>   // Inclusão da biblioteca padrão de manipulação de strings
#include "banco.h"    // Inclusão do arquivo de cabeçalho local

Cliente clientes[MAX_CLIENTES];
int num_clientes;

void salvarDados() {
    FILE *arquivo;    // Declaração de um ponteiro para um arquivo
    arquivo = fopen("dados_clientes.bin", "wb");    // Abertura do arquivo binário para escrita em modo de substituição

    if (arquivo != NULL) {    // Verificação se o arquivo foi aberto com sucesso
        fwrite(clientes, sizeof(Cliente), num_clientes, arquivo);    // Escrita dos dados dos clientes no arquivo
        fclose(arquivo);    // Fechamento do arquivo
    }
}

void carregarDados() {
    FILE *arquivo;    // Declaração de um ponteiro para um arquivo
    arquivo = fopen("dados_clientes.bin", "rb");    // Abertura do arquivo binário para leitura em modo de substituição

    if (arquivo != NULL) {    // Verificação se o arquivo foi aberto com sucesso
        fread(clientes, sizeof(Cliente), MAX_CLIENTES, arquivo);    // Leitura dos dados dos clientes do arquivo
        fclose(arquivo);    // Fechamento do arquivo
        num_clientes = 0;    // Inicialização do contador de clientes
        // Loop para contar o número de clientes carregados
        while (strcmp(clientes[num_clientes].cpf, "") != 0 && num_clientes < MAX_CLIENTES) {
            num_clientes++;
        }
    } else {
        printf("Erro ao abrir o arquivo de dados.\n");    // Mensagem de erro caso o arquivo não possa ser aberto
    }
}

void novoCliente() {
    Cliente novo;    // Declaração de uma variável do tipo Cliente para armazenar os dados do novo cliente
    printf("Nome: ");    // Solicitação do nome do cliente
    scanf(" %[^\n]", novo.nome);    // Leitura do nome do cliente até a quebra de linha
    printf("CPF: ");    // Solicitação do CPF do cliente
    scanf(" %s", novo.cpf);    // Leitura do CPF do cliente
    printf("Senha: ");    // Solicitação da senha do cliente
    scanf(" %s", novo.senha);    // Leitura da senha do cliente
    printf("Tipo de conta (comum ou plus): ");    // Solicitação do tipo de conta do cliente
    scanf(" %s", novo.tipo_conta);    // Leitura do tipo de conta do cliente
    printf("Valor inicial da conta: ");    // Solicitação do valor inicial da conta do cliente
    scanf("%f", &novo.saldo);    // Leitura do valor inicial da conta do cliente

    // Verificação do tipo de conta e atribuição do limite negativo e taxa de débito correspondentes
    if (strcmp(novo.tipo_conta, "comum") == 0) {
        novo.limite_negativo = -1000.0;
        novo.taxa_debito = 0.05;
    } else if (strcmp(novo.tipo_conta, "plus") == 0) {
        novo.limite_negativo = -5000.0;
        novo.taxa_debito = 0.03;
    } else {
        printf("Tipo de conta inválido!\n");    // Mensagem de erro caso o tipo de conta seja inválido
        return;
    }

    // Alocação de memória para o extrato do cliente e inicialização do mesmo
    novo.extrato = malloc(sizeof(char) * 1000);
    novo.extrato[0] = '\0';

    // Adição do novo cliente ao array de clientes e incremento do contador de clientes
    clientes[num_clientes++] = novo;
    printf("Cliente cadastrado com sucesso!\n");    // Mensagem de sucesso
    salvarDados();    // Chamada da função para salvar os dados atualizados
}

void apagaCliente() {
    char cpf[12];    // Declaração de uma variável para armazenar o CPF do cliente a ser apagado
    printf("CPF do cliente a ser apagado: ");    // Solicitação do CPF do cliente a ser apagado
    scanf(" %s", cpf);    // Leitura do CPF do cliente a ser apagado

    int i;    // Declaração de uma variável de controle para o loop
    // Loop para encontrar o cliente com o CPF informado e remover do array de clientes
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {    // Verifica se o CPF do cliente atual é igual ao informado
            // Loop para mover os clientes para "preencher o buraco" deixado pela remoção
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;    // Decremento do contador de clientes
            printf("Cliente apagado com sucesso!\n");    // Mensagem de sucesso
            salvarDados();    // Chamada da função para salvar os dados atualizados
            return;
        }
    }

    printf("Cliente não encontrado.\n");    // Mensagem de erro caso o cliente não seja encontrado
}

void listarClientes() {
    printf("Lista de Clientes:\n");    // Título da lista de clientes
    int i;    // Declaração de uma variável de controle para o loop
    // Loop para imprimir os dados de todos os clientes
    for (i = 0; i < num_clientes; i++) {
        printf("Nome: %s\nCPF: %s\nTipo de Conta: %s\nSaldo: R$ %.2f\n\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].tipo_conta, clientes[i].saldo);
    }
}

void debito() {
    char cpf[12], senha[20];    // Declaração de variáveis para armazenar o CPF e a senha do cliente
    float valor;    // Declaração de uma variável para armazenar o valor do débito
    printf("CPF: ");    // Solicitação do CPF do cliente
    scanf(" %s", cpf);    // Leitura do CPF do cliente
    printf("Senha: ");    // Solicitação da senha do cliente
    scanf(" %s", senha);    // Leitura da senha do cliente
    printf("Valor a ser debitado: ");    // Solicitação do valor a ser debitado
    scanf("%f", &valor);    // Leitura do valor a ser debitado

    int i;    // Declaração de uma variável de controle para o loop
    // Loop para encontrar o cliente com o CPF e a senha informados
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            // Verificação se o saldo do cliente é suficiente para realizar o débito
            if (clientes[i].saldo - valor >= clientes[i].limite_negativo) {
                clientes[i].saldo -= valor;    // Atualização do saldo do cliente
                registrarTransacao(&clientes[i], "Débito", valor);    // Registro da transação
                printf("Débito realizado com sucesso!\n");    // Mensagem de sucesso
                salvarDados();    // Chamada da função para salvar os dados atualizados
                return;
            } else {
                printf("Saldo insuficiente para realizar o débito.\n");    // Mensagem de erro caso o saldo seja insuficiente
                return;
            }
        }
    }

    printf("CPF ou senha incorretos.\n");    // Mensagem de erro caso o cliente não seja encontrado
}

void deposito() {
    char cpf[12];    // Declaração de uma variável para armazenar o CPF do cliente
    float valor;    // Declaração de uma variável para armazenar o valor do depósito
    printf("CPF: ");    // Solicitação do CPF do cliente
    scanf(" %s", cpf);    // Leitura do CPF do cliente
    printf("Valor a ser depositado: ");    // Solicitação do valor a ser depositado
    scanf("%f", &valor);    // Leitura do valor a ser depositado

    int i;    // Declaração de uma variável de controle para o loop
    // Loop para encontrar o cliente com o CPF informado
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clientes[i].saldo += valor;    // Atualização do saldo do cliente
            registrarTransacao(&clientes[i], "Depósito", valor);    // Registro da transação
            printf("Depósito realizado com sucesso!\n");    // Mensagem de sucesso
            salvarDados();    // Chamada da função para salvar os dados atualizados
            return;
        }
    }

    printf("CPF não encontrado.\n");    // Mensagem de erro caso o cliente não seja encontrado
}

void extrato() {
    char cpf[12], senha[20];    // Declaração de variáveis para armazenar o CPF e a senha do cliente
    printf("CPF: ");    // Solicitação do CPF do cliente
    scanf(" %s", cpf);    // Leitura do CPF do cliente
    printf("Senha: ");    // Solicitação da senha do cliente
    scanf(" %s", senha);    // Leitura da senha do cliente

    int i;    // Declaração de uma variável de controle para o loop
    // Loop para encontrar o cliente com o CPF e a senha informados
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            printf("Extrato do cliente:\n");    // Título do extrato do cliente
            printf("Nome: %s\nCPF: %s\nTipo de Conta: %s\nSaldo: R$ %.2f\n",
                   clientes[i].nome, clientes[i].cpf, clientes[i].tipo_conta, clientes[i].saldo);    // Dados do cliente
            printf("Transações: \n%s\n", clientes[i].extrato);    // Lista de transações do cliente
            return;
        }
    }

    printf("CPF ou senha incorretos.\n");    // Mensagem de erro caso o cliente não seja encontrado
}

void transferencia() {
    char cpf_origem[12], senha_origem[20], cpf_destino[12];    // Declaração de variáveis para armazenar os CPFs e as senhas do cliente de origem e destino
    float valor;    // Declaração de uma variável para armazenar o valor da transferência
    printf("CPF (Origem): ");    // Solicitação do CPF do cliente de origem
    scanf(" %s", cpf_origem);    // Leitura do CPF do cliente de origem
    printf("Senha (Origem): ");    // Solicitação da senha do cliente de origem
    scanf(" %s", senha_origem);    // Leitura da senha do cliente de origem
    printf("CPF (Destino): ");    // Solicitação do CPF do cliente de destino
    scanf(" %s", cpf_destino);    // Leitura do CPF do cliente de destino
    printf("Valor a ser transferido: ");    // Solicitação do valor a ser transferido
    scanf("%f", &valor);    // Leitura do valor a ser transferido

    int i, origem_idx = -1, destino_idx = -1;    // Declaração de variáveis de controle para o loop e índices dos clientes de origem e destino
    // Loop para encontrar os clientes de origem e destino com os CPFs informados
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha_origem) == 0) {
            origem_idx = i;    // Atribuição do índice do cliente de origem
        } else if (strcmp(clientes[i].cpf, cpf_destino) == 0) {
            destino_idx = i;    // Atribuição do índice do cliente de destino
        }
    }

    // Verificação se os clientes de origem e destino foram encontrados
    if (origem_idx != -1 && destino_idx != -1) {
        // Verificação se o saldo do cliente de origem é suficiente para realizar a transferência
        if (clientes[origem_idx].saldo - valor >= clientes[origem_idx].limite_negativo) {
            clientes[origem_idx].saldo -= valor;    // Atualização do saldo do cliente de origem
            clientes[destino_idx].saldo += valor;    // Atualização do saldo do cliente de destino
            registrarTransacao(&clientes[origem_idx], "Transferência para CPF: %s", valor);    // Registro da transação para o cliente de origem
            registrarTransacao(&clientes[destino_idx], "Transferência de CPF: %s", valor);    // Registro da transação para o cliente de destino
            printf("Transferência realizada com sucesso!\n");    // Mensagem de sucesso
            salvarDados();    // Chamada da função para salvar os dados atualizados
            return;
        } else {
            printf("Saldo insuficiente para realizar a transferência.\n");    // Mensagem de erro caso o saldo seja insuficiente
            return;
        }
    }

    printf("CPF (Origem) ou CPF (Destino) não encontrado.\n");    // Mensagem de erro caso os clientes não sejam encontrados
}

void adicionarTransacaoAoExtrato(Cliente *cliente, Transacao *transacao) {
    cliente->extrato = realloc(cliente->extrato, strlen(cliente->extrato) + 100);    // Realocação de memória para o extrato do cliente

    char temp[100];    // Declaração de uma variável para armazenar uma string temporária
    strftime(temp, sizeof(temp), "%a %b %d %H:%M:%S %Y", localtime(&transacao->timestamp));    // Formatação da data e hora da transação
    sprintf(cliente->extrato + strlen(cliente->extrato), "%s - R$ %.2f - %s\n", transacao->tipo, transacao->valor, temp);    // Adição da transação ao extrato
}

void registrarTransacao(Cliente *cliente, char *tipo, float valor) {
    Transacao transacao;    // Declaração de uma variável do tipo Transacao para representar a transação
    strcpy(transacao.tipo, tipo);    // Cópia do tipo de transação para a estrutura de transação
    transacao.valor = valor;    // Atribuição do valor da transação para a estrutura de transação
    transacao.timestamp = time(NULL);    // Atribuição do timestamp atual para a estrutura de transação

    adicionarTransacaoAoExtrato(cliente, &transacao);    // Chamada da função para adicionar a transação ao extrato do cliente
}
