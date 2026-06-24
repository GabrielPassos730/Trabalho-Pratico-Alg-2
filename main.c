#include <stdio.h>
#include <stdlib.h>

#include "clientes.h"
#include "entregadores.h"
#include "entregas.h"

int main() {

    Sistema sistema;

    sistema.qtdClientes = 0;
    sistema.qtdEntregadores = 0;
    sistema.qtdEntregas = 0;

    int op;

    do {

        printf("\n====== SISTEMA DE ENTREGAS ======\n");
        printf("1. Gerenciar clientes\n");
        printf("2. Gerenciar entregadores\n");
        printf("3. Gerenciar entregas\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        scanf("%d", &op);

        switch(op) {

            case 1:
                menuClientes(&sistema);
                break;

            case 2:
                menuEntregadores(&sistema);
                break;

            case 3:
                menuEntregas(&sistema);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(op != 0);

    return 0;
}
