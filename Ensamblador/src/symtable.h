#ifndef LCCCC_SYMTABLE
#define LCCCC_SYMTABLE

#include "utils.h"


SymTable initSymTable(int largo);

void insertSymTable(SymTable tabla, char* etiqueta, FullAddr addr);

void removeSymTable(SymTable tabla, char* etiqueta);

FullAddr searchSymTable(SymTable tabla, char* etiqueta);

void freeSymTable(SymTable tabla);

#endif