#ifndef CLIENTES_H
#define CLIENTES_H

#define TAM 5

typedef struct {
    int idCliente;
    char nome[100];
    char cpf[20];
    char telefone[20];
    char endereco[150];
} Cliente;

typedef struct {
    int idEntregador;
    char nome[100];
    char cpf[20];
    char placaVeiculo[20];
    char telefone[20];
} Entregador;

typedef struct {
    int codigoEntrega;
    int idCliente;
    int idEntregador;
    char descricaoProduto[100];
    char enderecoDestino[150];
    char dataEntrega[20];
    char status[30];
} Entrega;

typedef struct {
    Cliente clientes[TAM];
    Entregador entregadores[TAM];
    Entrega entregas[TAM];

    int qtdClientes;
    int qtdEntregadores;
    int qtdEntregas;
} Sistema;

void limparBuffer();
void lerString(char *msg, char *destino, int tamanho);

int buscarClientePorId(Sistema *s, int id);
int buscarClientePorCPF(Sistema *s, char cpf[]);

int clientePossuiEntrega(Sistema *s, int idCliente);

void cadastrarCliente(Sistema *s);
void listarClientes(Sistema *s);
void consultarCliente(Sistema *s);
void alterarCliente(Sistema *s);
void removerCliente(Sistema *s);

void menuClientes(Sistema *s);

#endif
