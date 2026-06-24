#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entregas.h"

int buscarEntregaPorCodigo(Sistema *s, int codigo) {

    int i;

    for(i = 0; i < s->qtdEntregas; i++) {

        if(s->entregas[i].codigoEntrega == codigo) {
            return i;
        }
    }

    return -1;
}

void cadastrarEntrega(Sistema *s) {

    Entrega e;

    if(s->qtdEntregas >= TAM) {
        printf("\nLimite de entregas atingido.\n");
        return;
    }

    printf("\n--- Cadastro de Entrega ---\n");

    printf("Codigo da entrega: ");
    scanf("%d", &e.codigoEntrega);

    limparBuffer();

    if(buscarEntregaPorCodigo(s, e.codigoEntrega) != -1) {
        printf("Erro: ja existe entrega com esse codigo.\n");
        return;
    }

    printf("ID do cliente: ");
    scanf("%d", &e.idCliente);

    limparBuffer();

    if(buscarClientePorId(s, e.idCliente) == -1) {
        printf("Erro: cliente nao cadastrado.\n");
        return;
    }

    printf("ID do entregador: ");
    scanf("%d", &e.idEntregador);

    limparBuffer();

    if(buscarEntregadorPorId(s, e.idEntregador) == -1) {
        printf("Erro: entregador nao cadastrado.\n");
        return;
    }

    lerString("Descricao do produto: ",
              e.descricaoProduto,
              sizeof(e.descricaoProduto));

    lerString("Endereco de destino: ",
              e.enderecoDestino,
              sizeof(e.enderecoDestino));

    lerString("Data da entrega: ",
              e.dataEntrega,
              sizeof(e.dataEntrega));

    lerString("Status: ",
              e.status,
              sizeof(e.status));

    s->entregas[s->qtdEntregas] = e;
    s->qtdEntregas++;

    printf("Entrega cadastrada com sucesso.\n");
}

void listarEntregas(Sistema *s) {

    int i;
    int posCliente;
    int posEntregador;

    printf("\n--- Lista de Entregas ---\n");

    if(s->qtdEntregas == 0) {
        printf("Nenhuma entrega cadastrada.\n");
        return;
    }

    for(i = 0; i < s->qtdEntregas; i++) {

        posCliente =
            buscarClientePorId(
                s,
                s->entregas[i].idCliente);

        posEntregador =
            buscarEntregadorPorId(
                s,
                s->entregas[i].idEntregador);

        printf("\nEntrega %d\n", i + 1);

        printf("Codigo: %d\n",
               s->entregas[i].codigoEntrega);

        printf("Descricao do produto: %s\n",
               s->entregas[i].descricaoProduto);

        printf("Endereco de destino: %s\n",
               s->entregas[i].enderecoDestino);

        printf("Data: %s\n",
               s->entregas[i].dataEntrega);

        printf("Status: %s\n",
               s->entregas[i].status);

        if(posCliente != -1) {

            printf("Cliente: %s | CPF: %s\n",
                   s->clientes[posCliente].nome,
                   s->clientes[posCliente].cpf);
        }

        if(posEntregador != -1) {

            printf("Entregador: %s | Placa: %s\n",
                   s->entregadores[posEntregador].nome,
                   s->entregadores[posEntregador].placaVeiculo);
        }
    }
}

void menuEntregas(Sistema *s) {

    int op;

    do {

        printf("\n--- MENU ENTREGAS ---\n");
        printf("1. Cadastrar entrega\n");
        printf("2. Listar entregas\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);

        switch(op) {

            case 1:
                cadastrarEntrega(s);
                break;

            case 2:
                listarEntregas(s);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(op != 0);
}
