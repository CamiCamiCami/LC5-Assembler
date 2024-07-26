#ifndef LCCCC_HELPERS
#define LCCCC_HELPERS

#include "utils.h"


bin traducirArimetica(Operacion op, SymTable tabla, addr pos);
bin traducirADDI(Operacion op, SymTable tabla, addr pos);
bin traducirBranch(Operacion op, SymTable table, addr pos);
bin traducirJUMP(Operacion op, SymTable table, addr pos);
bin traducirJR(Operacion op, SymTable tabla, addr pos);
bin traducirJALR(Operacion op, SymTable tabla, addr pos);
bin traducirTRAP(Operacion op, SymTable tabla, addr pos);
bin traducirRTI(Operacion op, SymTable tabla, addr pos);
bin traducirJAL(Operacion op, SymTable tabla, addr pos);
bin traducirLD(Operacion op, SymTable tabla, addr pos);
bin traducirST(Operacion op, SymTable tabla, addr pos);
bin traducirLDR(Operacion op, SymTable tabla, addr pos);
bin traducirSTR(Operacion op, SymTable tabla, addr pos);
bin traducirLUI(Operacion op, SymTable tabla, addr pos);
bin traducirLORI(Operacion op, SymTable tabla, addr pos);

void efectuarORIG(ConsPrograma prog, PseudoOp pso, char label[]);
void efectuarFILL(ConsPrograma prog, PseudoOp pso, char label[]);
void efectuarBLKW(ConsPrograma prog, PseudoOp pso, char label[]);
void efectuarSTRINGZ(ConsPrograma prog, PseudoOp pso, char label[]);
void efectuarEND(ConsPrograma prog, PseudoOp pso, char label[]);

Operacion* expandirADD(AliasOp aop, int *op_c);
Operacion* expandirMOV(AliasOp aop, int *op_c);

#endif