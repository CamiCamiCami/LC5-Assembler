#include "utils.h"


SymTable initSymTable(int largo);

SymTable insertSymTable(SymTable tabla, char* llave, int dato);

SymTable removeSymTable(SymTable tabla, char* llave);

int searchSymTable(SymTable tabla, char* llave);

void freeSymTable(SymTable tabla);



