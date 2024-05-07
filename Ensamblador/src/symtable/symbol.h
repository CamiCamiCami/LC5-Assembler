#include "../utils.h"

Symbol initSymbol(char* label, addr address);

char* getLabel(Symbol sym);

Symbol setLabel(Symbol sym, char* label);

addr getAddress(Symbol sym);

Symbol setAddress(Symbol sym, addr address);

void freeSymbol(Symbol sym);
