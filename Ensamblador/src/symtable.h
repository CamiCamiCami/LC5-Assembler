#include "utils.h"


SymTable initSymTable(int largo);

SymTable insertSymTable(SymTable tabla, char* etiqueta, Seccion s, int offset);

SymTable removeSymTable(SymTable tabla, char* etiqueta);

int searchSymTable(SymTable tabla, char* etiqueta);

void freeSymTable(SymTable tabla);



