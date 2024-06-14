#include "utils.h"


bin traducirADD(Operacion op, SymTable tabla, addr pos);
bin traducirSUB(Operacion op, SymTable tabla, addr pos);
bin traducirAND(Operacion op, SymTable tabla, addr pos);
bin traducirOR(Operacion op, SymTable tabla, addr pos);
bin traducirADDI(Operacion op, SymTable tabla, addr pos);
bin traducirBRp(Operacion op, SymTable tabla, addr pos);
bin traducirBRz(Operacion op, SymTable tabla, addr pos);
bin traducirBRn(Operacion op, SymTable tabla, addr pos);
bin traducirJR(Operacion op, SymTable tabla, addr pos);
bin traducirJALR(Operacion op, SymTable tabla, addr pos);
bin traducirTRAP(Operacion op, SymTable tabla, addr pos);
bin traducirRETI(Operacion op, SymTable tabla, addr pos);
bin traducirNOT(Operacion op, SymTable tabla, addr pos);
bin traducirJAL(Operacion op, SymTable tabla, addr pos);
bin traducirLD(Operacion op, SymTable tabla, addr pos);
bin traducirST(Operacion op, SymTable tabla, addr pos);
bin traducirLDR(Operacion op, SymTable tabla, addr pos);
bin traducirSTR(Operacion op, SymTable tabla, addr pos);
bin traducirLUI(Operacion op, SymTable tabla, addr pos);
bin traducirLORI(Operacion op, SymTable tabla, addr pos);
bin traducirCLS(Operacion op, SymTable tabla, addr pos);
bin traducirSET(Operacion op, SymTable tabla, addr pos);
bin traducirSLT(Operacion op, SymTable tabla, addr pos);
bin traducirRET(Operacion op, SymTable tabla, addr pos);
