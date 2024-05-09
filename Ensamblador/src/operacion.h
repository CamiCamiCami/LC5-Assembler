#include "utils.h"

Operacion initOperacion(Token tkns[], int c_tkns);

bin traducirOperacion(Operacion op, SymTable tabla, addr pos);

void freeOperacion(Operacion op);
