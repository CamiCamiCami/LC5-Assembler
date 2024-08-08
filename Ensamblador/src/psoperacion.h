#ifndef LCCCC_PSEUDOPERACION
#define LCCCC_PSEUDOPERACION

#include "utils.h"
#include "argumentos.h"

PseudoOp initPseudoOp(PseudoIns psi, Argumento arg);

void efectuarPseudoOp(ConsPrograma prog, PseudoOp pso, char label[]);

#endif