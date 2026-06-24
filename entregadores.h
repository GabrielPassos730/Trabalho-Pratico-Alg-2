#ifndef ENTREGADORES_H
#define ENTREGADORES_H

#include "clientes.h"

int buscarEntregadorPorId(Sistema *s, int id);
int buscarEntregadorPorCPF(Sistema *s, char cpf[]);

int entregadorPossuiEntrega(Sistema *s, int idEntregador);

void cadastrarEntregador(Sistema *s);
void listarEntregadores(Sistema *s);
void consultarEntregador(Sistema *s);
void alterarEntregador(Sistema *s);
void removerEntregador(Sistema *s);

void menuEntregadores(Sistema *s);

#endif
