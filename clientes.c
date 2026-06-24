#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

void limparBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *msg, char *destino, int tamanho) {
    printf("%s", msg);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

int buscarClientePorId(Sistema *s, int id) {
    int i;

    for(i = 0; i < s->qtdClientes; i++) {
        if(s->clientes[i].idCliente == id) {
            return i;
        }
    }

    return -1;
}

int buscarClientePorCPF(Sistema *s, char cpf[]) {
    int i;

    for(i = 0; i < s->qtdClientes; i++) {
        if(strcmp(s->clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }

    return -1;
}

int clientePossuiEntrega(Sistema *s, int idCliente) {
    int i;

    for(i = 0; i < s->qtdEntregas; i++) {
        if(s->entregas[i].idCliente == idCliente) {
            return 1;
        }
    }

    return 0;
}

void cadastrarCliente(Sistema *s) {

    Cliente c;

    if(s->qtdClientes >= TAM) {
        printf("\nLimite de clientes atingido.\n");
        return;
    }

    printf("\n--- Cadastro de Cliente ---\n");

    printf("ID do cliente: ");
    scanf("%d", &c.idCliente);

    limparBuffer();

    if(buscarClientePorId(s, c.idCliente) != -1) {
        printf("Erro: ja existe cliente com esse ID.\n");
        return;
    }

    lerString("Nome: ", c.nome, sizeof(c.nome));
    lerString("CPF: ", c.cpf, sizeof(c.cpf));

    if(buscarClientePorCPF(s, c.cpf) != -1) {
        printf("Erro: ja existe cliente com esse CPF.\n");
        return;
    }

    lerString("Telefone: ", c.telefone, sizeof(c.telefone));
    lerString("Endereco: ", c.endereco, sizeof(c.endereco));

    s->clientes[s->qtdClientes] = c;
    s->qtdClientes++;

    printf("Cliente cadastrado com sucesso.\n");
}

void listarClientes(Sistema *s) {

    int i;

    printf("\n--- Lista de Clientes ---\n");

    if(s->qtdClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for(i = 0; i < s->qtdClientes; i++) {

        printf("\nCliente %d\n", i + 1);
        printf("ID: %d\n", s->clientes[i].idCliente);
        printf("Nome: %s\n", s->clientes[i].nome);
        printf("CPF: %s\n", s->clientes[i].cpf);
        printf("Telefone: %s\n", s->clientes[i].telefone);
        printf("Endereco: %s\n", s->clientes[i].endereco);
    }
}

void consultarCliente(Sistema *s) {

    char cpf[20];
    int pos;

    printf("\n--- Consulta de Cliente ---\n");

    limparBuffer();

    lerString("Digite o CPF do cliente: ", cpf, sizeof(cpf));

    pos = buscarClientePorCPF(s, cpf);

    if(pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("\nID: %d\n", s->clientes[pos].idCliente);
    printf("Nome: %s\n", s->clientes[pos].nome);
    printf("CPF: %s\n", s->clientes[pos].cpf);
    printf("Telefone: %s\n", s->clientes[pos].telefone);
    printf("Endereco: %s\n", s->clientes[pos].endereco);
}

void alterarCliente(Sistema *s) {

    char cpf[20];
    char novoCPF[20];

    int pos;

    printf("\n--- Alteracao de Cliente ---\n");

    limparBuffer();

    lerString("Digite o CPF do cliente: ", cpf, sizeof(cpf));

    pos = buscarClientePorCPF(s, cpf);

    if(pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    lerString("Novo nome: ",
              s->clientes[pos].nome,
              sizeof(s->clientes[pos].nome));

    lerString("Novo CPF: ", novoCPF, sizeof(novoCPF));

    if(strcmp(novoCPF, s->clientes[pos].cpf) != 0 &&
       buscarClientePorCPF(s, novoCPF) != -1) {

        printf("Erro: ja existe outro cliente com esse CPF.\n");
        return;
    }

    strcpy(s->clientes[pos].cpf, novoCPF);

    lerString("Novo telefone: ",
              s->clientes[pos].telefone,
              sizeof(s->clientes[pos].telefone));

    lerString("Novo endereco: ",
              s->clientes[pos].endereco,
              sizeof(s->clientes[pos].endereco));

    printf("Cliente alterado com sucesso.\n");
}

void removerCliente(Sistema *s) {

    char cpf[20];

    int pos;
    int i;

    printf("\n--- Remocao de Cliente ---\n");

    limparBuffer();

    lerString("Digite o CPF do cliente: ", cpf, sizeof(cpf));

    pos = buscarClientePorCPF(s, cpf);

    if(pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    if(clientePossuiEntrega(s, s->clientes[pos].idCliente)) {
        printf("Erro: cliente vinculado a uma entrega.\n");
        return;
    }

    for(i = pos; i < s->qtdClientes - 1; i++) {
        s->clientes[i] = s->clientes[i + 1];
    }

    s->qtdClientes--;

    printf("Cliente removido com sucesso.\n");
}

void menuClientes(Sistema *s) {

    int op;

    do {

        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Consultar cliente\n");
        printf("3. Alterar cliente\n");
        printf("4. Remover cliente\n");
        printf("5. Listar clientes\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);

        switch(op) {

            case 1:
                cadastrarCliente(s);
                break;

            case 2:
                consultarCliente(s);
                break;

            case 3:
                alterarCliente(s);
                break;

            case 4:
                removerCliente(s);
                break;

            case 5:
                listarClientes(s);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(op != 0);
}
