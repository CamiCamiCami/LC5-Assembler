#include "../utils.h"


SymTable initSymTable(int largo);

SymTable insertSymTable(SymTable tabla, char* llave, addr dato);

SymTable removeSymTable(SymTable tabla, char* llave);

addr searchSymTable(SymTable tabla, char* llave);

void freeSymTable(SymTable tabla);



