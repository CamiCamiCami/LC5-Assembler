#include "../utils.h"

Symbol initSymbol(char* label, int address);

char* getLabel(Symbol sym);

Symbol setLabel(Symbol sym, char* label);

int getAddress(Symbol sym);

Symbol setAddress(Symbol sym, int address);

void freeSymbol(Symbol sym);
