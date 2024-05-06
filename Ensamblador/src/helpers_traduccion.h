#include "utils.h"


bin traducirADD(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirSUB(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirAND(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirOR(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirADDI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirANDI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirORI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirBRp(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirBRz(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirBRn(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirJR(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirJALR(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirTRAP(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirRETI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirNOT(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirJAL(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirLD(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirST(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirLDR(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirSTR(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirLUI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirLORI(Operacion op, SymTable tabla, addr orig, addr pos);
bin traducirLJMP(Operacion op, SymTable tabla, addr orig, addr pos);
