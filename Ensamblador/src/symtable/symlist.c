#include "symlist.h"
#include "symbol.h"

#define LLAVE(t) getLabel(t->symbol)
#define DATO(t) getAddress(t->symbol)

/* Funciones de libreria */

SymList initSymList(){
    return NULL;
}

bool emptySymList(SymList map){
    return map == NULL;
}

SymList insertSymList(SymList map, char* llave, int dato){
    if (emptySymList(map)){
        Symbol sym = initSymbol(llave, dato);
        SymList nodo = malloc(sizeof(struct __symbol_list));
        nodo->sig = initSymList();
        nodo->symbol = sym;
        return nodo;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        return map;
    } else {
        map->sig = insertSymList(map->sig, llave, dato);
        return map;
    }
}

SymList removeSymList(SymList map, char* llave){
    if (emptySymList(map)){
        return map;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        freeSymbol(map->symbol);
        SymList nodo = map->sig;
        free(map);
        return nodo;
    } else {
        map->sig = removeSymList(map->sig, llave);
        return map;
    }
}

int searchSymList(SymList map, char* llave){
    if (emptySymList(map)){
        return -1;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        return DATO(map);
    } else {
        return searchSymList(map->sig, llave);
    }
}

void freeSymList(SymList map){
    if (emptySymList(map)){
        return;
    }
    freeSymList(map->sig);
    freeSymbol(map->symbol);
    free(map);
}
