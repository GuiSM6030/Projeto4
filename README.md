# Quem Poupa Tem
O novo banco QuemPoupaTem vai iniciar a sua operação em breve, mas não tem um sistema bancário estabelecido. Para desenvolver o sistema que controla os clientes, o banco decidiu contratar você.

## Requisitos
O banco trabalha com dois tipos de conta:

_Comum:_
Cobra taxa de 5% a cada débito realizado
Permite um saldo negativo de até (R$ 1.000,00)

_Plus:_
Cobra taxa de 3% a cada débito realizado
Permite um saldo negativo de até (R$ 5.000,00)
O sistema criado por você deve funcionar em loop infinito até que se deseje sair;
Um menu de opções deve ser sempre apresentado ao operador, contendo as seguintes operações:
1. Novo cliente
2. Apaga cliente
3. Listar clientes
4. Débito
5. Depósito
6. Extrato
7. Transferência Entre Contas
0. Sair

Cada opção deve ser implementada como uma função;
O seu programa deve conseguir armazenar até 1000 clientes e as informações das últimas 100 operações (depósito, saque, transferência) realizada pelo cliente

**IMPORTANTE:** Não se esqueça de que o banco não pode perder as informações se o programa terminar, fechar, parar de funcionar, ou o computador desligar. Todos os dados devem ser salvos de maneira permanente utilizando arquivos binários.

## Como Compilar e Executar
Para compilar o programa, execute os seguintes comandos no terminal:

gcc -w *.c && ./a.out
