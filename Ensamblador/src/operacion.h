#ifndef LCCCC_OPERACION
#define LCCCC_OPERACION

#include "utils.h"

Operacion initOperacion(Instruccion ins, Argumento args[], int argc);

bin traducirOperacion(Operacion op, SymTable tabla, addr pos);

void freeOperacion(Operacion op);

#endif