#include "symbol.h"
#include <string.h>

Symbol initSymbol(char* label, addr address){
    Symbol sym = malloc(sizeof(struct __symbol));
    char* label_cpy = malloc(sizeof(char) * strlen(label));
    strcpy(label_cpy, label);
    sym->label = label_cpy;
    sym->address = address;
    return sym;
}

char* getLabel(Symbol sym){
    return sym->label;
}

Symbol setLabel(Symbol sym, char* label){
    free(sym->label);
    char* label_cpy = malloc(sizeof(char) * strlen(label));
    strcpy(label_cpy, label);
    sym->label = label_cpy;
    return sym;
}

addr getAddress(Symbol sym){
    return sym->address;
}

Symbol setAddress(Symbol sym, addr address){
    sym->address = address;
    return sym;
}

void freeSymbol(Symbol sym){
    free(sym->label);
    free(sym);
}
