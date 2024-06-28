#include "psoperacion.h"
#include "argumentos.h"

PseudoOp initPseudoOp(PseudoIns psi, Argumento arg) {
    PseudoOp pso = malloc(sizeof(struct __pseudo_operacion));
    pso->psi = psi;
    pso->arg = arg;
    return pso;
}

void efectuarPseudoOp(ConsPrograma prog, PseudoOp pso, char label[]) {
    pso->psi->efecto(prog, pso, label);
    freeArgumento(pso->arg);
    free(pso);
}