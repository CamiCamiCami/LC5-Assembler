#include <stdbool.h>
#include "symbol.h"

struct __symbol_list {
    Symbol symbol;
    SymList sig;
};

SymList initSymList();

bool emptySymList(SymList lista);

SymList insertSymList(SymList lista, char* llave, addr dato);

SymList removeSymList(SymList lista, char* llave);

addr searchSymList(SymList lista, char* llave);

void freeSymList(SymList lista);