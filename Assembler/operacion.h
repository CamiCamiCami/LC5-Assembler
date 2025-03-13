#ifndef LCCCC_OPERACION
#define LCCCC_OPERACION

#include "utils.h"
#include "argumentos.h"

Operacion initOperacion(Instruction ins, Argumento args[]);

bin traducirOperacion(Operacion op, SymTable tabla, addr pos);

void freeOperacion(Operacion op);

#endif