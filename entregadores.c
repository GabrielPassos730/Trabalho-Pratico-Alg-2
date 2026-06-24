#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entregadores.h"

int buscarEntregadorPorId(Sistema *s, int id) {

    int i;

    for(i = 0; i < s->qtdEntregadores; i++) {

        if(s->entregadores[i].idEntregador == id) {
            return i;
        }
    }

    return -1;
}

int buscarEntregadorPorCPF(Sistema *s, char cpf[]) {

    int i;

    for(i = 0; i < s->qtdEntregadores; i++) {

        if(strcmp(s->entregadores[i].cpf, cpf) == 0) {
            return i;
        }
    }

    return -1;
}

int entregadorPossuiEntrega(Sistema *s, int idEntregador) {

    int i;

    for(i = 0; i < s->qtdEntregas; i++) {

        if(s->entregas[i].idEntregador == idEntregador) {
            return 1;
        }
    }

    return 0;
}

void cadastrarEntregador(Sistema *s) {

    Entregador e;

    if(s->qtdEntregadores >= TAM) {
        printf("\nLimite de entregadores atingido.\n");
        return;
    }

    printf("\n--- Cadastro de Entregador ---\n");

    printf("ID do entregador: ");
    scanf("%d", &e.idEntregador);

    limparBuffer();

    if(buscarEntregadorPorId(s, e.idEntregador) != -1) {
        printf("Erro: ja existe entregador com esse ID.\n");
        return;
    }

    lerString("Nome: ", e.nome, sizeof(e.nome));
    lerString("CPF: ", e.cpf, sizeof(e.cpf));

    if(buscarEntregadorPorCPF(s, e.cpf) != -1) {
        printf("Erro: ja existe entregador com esse CPF.\n");
        return;
    }

    lerString("Placa do veiculo: ",
              e.placaVeiculo,
              sizeof(e.placaVeiculo));

    lerString("Telefone: ",
              e.telefone,
              sizeof(e.telefone));

    s->entregadores[s->qtdEntregadores] = e;
    s->qtdEntregadores++;

    printf("Entregador cadastrado com sucesso.\n");
}

void listarEntregadores(Sistema *s) {

    int i;

    printf("\n--- Lista de Entregadores ---\n");

    if(s->qtdEntregadores == 0) {
        printf("Nenhum entregador cadastrado.\n");
        return;
    }

    for(i = 0; i < s->qtdEntregadores; i++) {

        printf("\nEntregador %d\n", i + 1);

        printf("ID: %d\n",
               s->entregadores[i].idEntregador);

        printf("Nome: %s\n",
               s->entregadores[i].nome);

        printf("CPF: %s\n",
               s->entregadores[i].cpf);

        printf("Placa: %s\n",
               s->entregadores[i].placaVeiculo);

        printf("Telefone: %s\n",
               s->entregadores[i].telefone);
    }
}

void consultarEntregador(Sistema *s) {

    char cpf[20];
    int pos;

    printf("\n--- Consulta de Entregador ---\n");

    limparBuffer();

    lerString("Digite o CPF do entregador: ",
              cpf,
              sizeof(cpf));

    pos = buscarEntregadorPorCPF(s, cpf);

    if(pos == -1) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    printf("\nID: %d\n",
           s->entregadores[pos].idEntregador);

    printf("Nome: %s\n",
           s->entregadores[pos].nome);

    printf("CPF: %s\n",
           s->entregadores[pos].cpf);

    printf("Placa: %s\n",
           s->entregadores[pos].placaVeiculo);

    printf("Telefone: %s\n",
           s->entregadores[pos].telefone);
}

void alterarEntregador(Sistema *s) {

    char cpf[20];
    char novoCPF[20];

    int pos;

    printf("\n--- Alteracao de Entregador ---\n");

    limparBuffer();

    lerString("Digite o CPF do entregador: ",
              cpf,
              sizeof(cpf));

    pos = buscarEntregadorPorCPF(s, cpf);

    if(pos == -1) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    lerString("Novo nome: ",
              s->entregadores[pos].nome,
              sizeof(s->entregadores[pos].nome));

    lerString("Novo CPF: ",
              novoCPF,
              sizeof(novoCPF));

    if(strcmp(novoCPF, s->entregadores[pos].cpf) != 0 &&
       buscarEntregadorPorCPF(s, novoCPF) != -1) {

        printf("Erro: ja existe outro entregador com esse CPF.\n");
        return;
    }

    strcpy(s->entregadores[pos].cpf, novoCPF);

    lerString("Nova placa do veiculo: ",
              s->entregadores[pos].placaVeiculo,
              sizeof(s->entregadores[pos].placaVeiculo));

    lerString("Novo telefone: ",
              s->entregadores[pos].telefone,
              sizeof(s->entregadores[pos].telefone));

    printf("Entregador alterado com sucesso.\n");
}

void removerEntregador(Sistema *s) {

    char cpf[20];

    int pos;
    int i;

    printf("\n--- Remocao de Entregador ---\n");

    limparBuffer();

    lerString("Digite o CPF do entregador: ",
              cpf,
              sizeof(cpf));

    pos = buscarEntregadorPorCPF(s, cpf);

    if(pos == -1) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    if(entregadorPossuiEntrega(
        s,
        s->entregadores[pos].idEntregador)) {

        printf("Erro: entregador vinculado a uma entrega.\n");
        return;
    }

    for(i = pos; i < s->qtdEntregadores - 1; i++) {

        s->entregadores[i] =
        s->entregadores[i + 1];
    }

    s->qtdEntregadores--;

    printf("Entregador removido com sucesso.\n");
}

void menuEntregadores(Sistema *s) {

    int op;

    do {

        printf("\n--- MENU ENTREGADORES ---\n");
        printf("1. Cadastrar entregador\n");
        printf("2. Consultar entregador\n");
        printf("3. Alterar entregador\n");
        printf("4. Remover entregador\n");
        printf("5. Listar entregadores\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);

        switch(op) {

            case 1:
                cadastrarEntregador(s);
                break;

            case 2:
                consultarEntregador(s);
                break;

            case 3:
                alterarEntregador(s);
                break;

            case 4:
                removerEntregador(s);
                break;

            case 5:
                listarEntregadores(s);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(op != 0);
}
