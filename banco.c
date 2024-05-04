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