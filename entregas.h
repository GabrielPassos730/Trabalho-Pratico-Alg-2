#ifndef ENTREGAS_H
#define ENTREGAS_H

#include "clientes.h"
#include "entregadores.h"

int buscarEntregaPorCodigo(Sistema *s, int codigo);

void cadastrarEntrega(Sistema *s);
void listarEntregas(Sistema *s);

void menuEntregas(Sistema *s);

#endif
