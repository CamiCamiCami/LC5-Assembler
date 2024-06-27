#include "utils.h"

Operacion initOperacion(Instruccion ins, Argumento args[], int argc);

bin traducirOperacion(Operacion op, SymTable tabla, addr pos);

void freeOperacion(Operacion op);
