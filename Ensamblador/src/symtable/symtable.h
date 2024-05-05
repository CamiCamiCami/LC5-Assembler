#include <stdlib.h>
#include "symlist.h"

struct __symtable{
    SymList* array;
    int largo;
};

SymTable initSymTable(int largo);

SymTable insertSymTable(SymTable tabla, char* llave, addr dato);

SymTable removeSymTable(SymTable tabla, char* llave);

addr searchSymTable(SymTable tabla, char* llave);

void freeSymTable(SymTable tabla);



